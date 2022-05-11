/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition and implementation for dependency injection templates in SUP.
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef _SUP_ObjectManager_h_
#define _SUP_ObjectManager_h_

#include "IndexSequence.h"
#include "InstanceContainer.h"
#include "TypeMap.h"
#include "TypeStringList.h"

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace sup
{
namespace di
{
namespace internal
{
template <typename ServiceType, typename Deleter, typename... Deps>
using InstanceFactoryFunction = std::unique_ptr<ServiceType, Deleter>(*)(Deps*...);

using RegisteredFactoryFunction =
  std::function<void(const std::string&, const std::vector<std::string>&)>;

}  // namespace internal

class ObjectManager
{
public:
  ObjectManager();
  ~ObjectManager();

  void CreateInstance(const std::string& registered_typename, const std::string& instance_name,
                      const std::vector<std::string>& dependency_names);

  template <typename T> T* GetInstance(const std::string& instance_name);

  template <typename ServiceType, typename Deleter, typename... Deps>
  void RegisterFactoryFunction(const std::string& registered_typename,
                               internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...>
                                 factory_function);

  template <typename ServiceType>
  void RegisterInstance(std::unique_ptr<ServiceType>&& instance, const std::string& instance_name);

private:
  using ServiceMap = std::map<std::string, std::unique_ptr<internal::AbstractInstanceContainer>>;
  std::map<std::string, internal::RegisteredFactoryFunction> factory_functions;
  internal::TypeMap<ServiceMap> instance_map;

  template <typename ServiceType, typename Deleter, typename... Deps, std::size_t... I>
  std::unique_ptr<ServiceType, Deleter> CreateFromTypeStringList(
    internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...> factory_function,
    const internal::TypeStringList<Deps...>& type_string_list,
    internal::IndexSequence<I...> index_sequence);

  template <std::size_t I, typename... Deps>
  typename internal::TypeStringList<Deps...>::template IndexedType<I>*
    IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list);

  template <typename ServiceType>
  ServiceMap& GetServiceMap();
};

template <typename ServiceType, typename ConcreteType, typename... Deps>
std::unique_ptr<ServiceType> GenericInstanceFactoryFunction(Deps*... dependencies)
{
  return std::unique_ptr<ServiceType>(new ConcreteType(dependencies...));
}

ObjectManager& GlobalObjectManager();

template <typename T>
T* ObjectManager::GetInstance(const std::string& instance_name)
{
  auto service_map_it = instance_map.find<T>();
  if (service_map_it == instance_map.end())
  {
    throw std::runtime_error("ObjectManager::GetInstance: accessing unknow service type");
  }
  auto instance_it = service_map_it->second.find(instance_name);
  if (instance_it == service_map_it->second.end())
  {
    throw std::runtime_error("ObjectManager::GetInstance: accessing unknow instance");
  }
  return static_cast<T*>(instance_it->second->Get());
}

template <typename ServiceType, typename Deleter, typename... Deps>
void ObjectManager::RegisterFactoryFunction(
  const std::string& registered_typename,
  internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...> factory_function)
{
  if (factory_functions.find(registered_typename) != factory_functions.end())
  {
    throw std::runtime_error("ObjectManager::RegisterFactoryFunction: typename already registered");
  }
  factory_functions[registered_typename] =
    [this, factory_function](const std::string& instance_name, const std::vector<std::string>& dependency_names)
    {
      internal::TypeStringList<Deps...> type_string_list(dependency_names);
      typename internal::MakeIndexSequence<sizeof...(Deps)>::type index_sequence;
      auto p_instance = CreateFromTypeStringList(
        factory_function, type_string_list, index_sequence);
      RegisterInstance(std::move(p_instance), instance_name);
    };
}

template <typename ServiceType>
void ObjectManager::RegisterInstance(
  std::unique_ptr<ServiceType>&& instance, const std::string& instance_name)
{
  auto& service_map = GetServiceMap<ServiceType>();
  if (service_map.find(instance_name) != service_map.end())
  {
    throw std::runtime_error(
      "ObjectManager::RegisterFactoryFunction: instance name already registered");
  }
  service_map[instance_name] = internal::WrapIntoContainer(std::move(instance));
}

template<typename ServiceType, typename Deleter, typename... Deps, std::size_t... I>
std::unique_ptr<ServiceType, Deleter> ObjectManager::CreateFromTypeStringList(
  internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...> factory_function,
  const internal::TypeStringList<Deps...>& type_string_list,
  internal::IndexSequence<I...> index_sequence)
{
  return factory_function(IndexedArgument<I>(type_string_list)...);
}

template <std::size_t I, typename... Deps>
typename internal::TypeStringList<Deps...>::template IndexedType<I>*
  ObjectManager::IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list)
{
  return GetInstance<typename internal::TypeStringList<Deps...>::template IndexedType<I>>(
    type_string_list.IndexedString(I) );
}

template <typename ServiceType>
ObjectManager::ServiceMap& ObjectManager::GetServiceMap()
{
  auto it = instance_map.find<ServiceType>();
  if (it == instance_map.end())
  {
    instance_map.put<ServiceType>(ServiceMap{});
    it = instance_map.find<ServiceType>();
  }
  return it->second;
}

}  // namespace di

}  // namespace sup

#endif  // _SUP_ObjectManager_h_
