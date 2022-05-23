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

#include "DependencyTraits.h"
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
/**
 * @brief Alias template for a factory function to create an object with constructor dependencies.
 *
 * @details Each dependency in Deps needs to be either a (const) pointer (when ownership is not
 * transferred to the created object) or a std::unique_ptr<T>&& (for ownership transfer).
 */
template <typename ServiceType, typename Deleter, typename... Deps>
using InstanceFactoryFunction = std::unique_ptr<ServiceType, Deleter>(*)(Deps...);

/**
 * @brief Alias template for a global function with specified dependencies.
 *
 * @details Each dependency in Deps needs to be either a (const) pointer (when ownership is not
 * transferred to the created object) or a std::unique_ptr<T>&& (for ownership transfer).
 *
 * The boolean return value can be used by client software to handle a failure to execute the
 * function.
 */
template <typename... Deps>
using GlobalFunction = bool(*)(Deps...);
}  // namespace internal

/**
 * @brief Class that manages string-based instantiation of objects and calling of global functions.
 */
class ObjectManager
{
  using ServiceMap = std::map<std::string, std::unique_ptr<internal::AbstractInstanceContainer>>;
  using ServiceMapIterator = typename ServiceMap::iterator;
  using RegisteredFactoryFunction =
    std::function<void(const std::string&, const std::vector<std::string>&)>;
  using RegisteredGlobalFunction = std::function<bool(const std::vector<std::string>&)>;
public:
  /**
   * @brief Constructor.
   */
  ObjectManager();
  ~ObjectManager();

  /**
   * @brief Create an instance and store it under the given name.
   *
   * @param registered_typename Name under which the factory function was registered.
   * @param instance_name Name under which to store the created instance.
   * @param dependency_names List of instance names that need to be injected as dependencies.
   */
  void CreateInstance(const std::string& registered_typename, const std::string& instance_name,
                      const std::vector<std::string>& dependency_names);

  /**
   * @brief Call a global function on the named instances.
   *
   * @param registered_function_name Name under which the global function was registered.
   * @param dependency_names List of instance names that need to be injected as dependencies.
   */
  bool CallGlobalFunction(const std::string& registered_function_name,
                         const std::vector<std::string>& dependency_names);

  /**
   * @brief Retrieve instance of specific type and name from the underlying registry.
   *
   * @param instance_name Name under which the instance was registered.
   * @return Depending on the required transfer of ownership, a pointer or a unique_ptr to the found
   * instance.
   *
   * @note The template type parameter T must be one of:
   *   (const) T*: for retrieving a pointer to the instance whose lifetime is handled by the
   *               ObjectManager
   *   std::unique_ptr<T>&& : for transferring ownership out of ObjectManager
   */
  template <typename T>
  typename internal::DependencyTraits<T>::InjectionType
    GetInstance(const std::string& instance_name);

  /**
   * @brief Register a factory function that requires dependencies.
   *
   * @param registered_typename Name under which the factory function will be registered.
   * @param factory_function Factory function that creates a new instance and possibly requires
   * dependencies.
   * @return true on successful registration.
   */
  template <typename ServiceType, typename Deleter, typename... Deps>
  bool RegisterFactoryFunction(const std::string& registered_typename,
                               internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...>
                                 factory_function);

  /**
   * @brief Register an instance of an object directly.
   *
   * @param instance rvalue to unique_ptr to an object.
   * @param instance_name Name under which the instance will be registered.
   * @return true on successful registration.
   */
  template <typename ServiceType>
  bool RegisterInstance(std::unique_ptr<ServiceType>&& instance, const std::string& instance_name);

  /**
   * @brief Register a global function that requires dependencies.
   *
   * @param registered_function_name Name under which the global function will be registered.
   * @param global_function Global function to register.
   * @return true on successful registration.
   */
  template <typename... Deps>
  bool RegisterGlobalFunction(const std::string& registered_function_name,
                              internal::GlobalFunction<Deps...> global_function);

private:
  std::map<std::string, RegisteredFactoryFunction> factory_functions;
  std::map<std::string, RegisteredGlobalFunction> global_functions;
  internal::TypeMap<ServiceMap> instance_map;

  /**
   * @brief Helper method to inject retrieved instances into the factory function.
   */
  template <typename ServiceType, typename Deleter, typename... Deps, std::size_t... I>
  std::unique_ptr<ServiceType, Deleter> CreateFromTypeStringList(
    internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...> factory_function,
    const internal::TypeStringList<Deps...>& type_string_list,
    internal::IndexSequence<I...> index_sequence);

  /**
   * @brief Helper method to inject retrieved instances into the global function.
   */
  template <typename... Deps, std::size_t... I>
  bool CallFromTypeStringList(internal::GlobalFunction<Deps...> global_function,
                              const internal::TypeStringList<Deps...>& type_string_list,
                              internal::IndexSequence<I...> index_sequence);

  /**
   * @brief Helper method to retrieve an instance of the correct type, based on an index.
   */
  template <std::size_t I, typename... Deps>
  typename internal::DependencyTraits<typename internal::TypeStringList<Deps...>::template
                                        IndexedType<I>>::InjectionType
    IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list);

  /**
   * @brief Helper method to retrieve an instance when ownership needs to be passed.
   */
  template <typename T>
  typename internal::DependencyTraits<T>::InjectionType
    GetInstanceImpl(const std::string& instance_name, std::true_type transfer_ownership);

  /**
   * @brief Helper method to retrieve an instance when ownership is managed by the ObjectManager.
   */
  template <typename T>
  typename internal::DependencyTraits<T>::InjectionType
    GetInstanceImpl(const std::string& instance_name,
                    std::false_type do_not_transfer_ownership);

  /**
   * @brief Helper method to retrieve an iterator to a named and typed instance.
   */
  template <typename T>
  ServiceMapIterator FindInstance(const std::string& instance_name);

  /**
   * @brief Helper method to remove a named and typed instance.
   */
  template <typename T>
  void RemoveInstance(ServiceMapIterator it);

  /**
   * @brief Helper method to retrieve the service map for a given type.
   */
  template <typename ServiceType>
  ServiceMap& GetServiceMap();
};

/**
 * @brief Function template for a factory function with shared dependencies.
 *
 * @details The dependencies' lifetime will not be managed by the created object and needs to be
 * managed elsewhere (e.g. in an ObjectManager).
 */
template <typename ServiceType, typename ConcreteType, typename... Deps>
std::unique_ptr<ServiceType> GenericInstanceFactoryFunctionShared(Deps*... dependencies)
{
  return std::unique_ptr<ServiceType>(new ConcreteType(dependencies...));
}

/**
 * @brief Function template for a factory function with ownership transfer of dependencies.
 *
 * @details The dependencies' lifetime needs to be managed by the created object.
 */
template <typename ServiceType, typename ConcreteType, typename... Deps>
std::unique_ptr<ServiceType> GenericInstanceFactoryFunction(std::unique_ptr<Deps>&&... dependencies)
{
  return std::unique_ptr<ServiceType>(new ConcreteType(std::move(dependencies)...));
}

/**
 * @brief Retrieve global ObjectManager instance.
 */
ObjectManager& GlobalObjectManager();

template <typename T>
typename internal::DependencyTraits<T>::InjectionType
ObjectManager::GetInstance(const std::string& instance_name)
{
  return GetInstanceImpl<T>(instance_name,
    typename internal::DependencyTraits<T>::TransferOwnership{});
}

template <typename ServiceType, typename Deleter, typename... Deps>
bool ObjectManager::RegisterFactoryFunction(
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
  return true;
}

template <typename ServiceType>
bool ObjectManager::RegisterInstance(
  std::unique_ptr<ServiceType>&& instance, const std::string& instance_name)
{
  auto& service_map = GetServiceMap<ServiceType>();
  if (service_map.find(instance_name) != service_map.end())
  {
    throw std::runtime_error(
      "ObjectManager::RegisterFactoryFunction: instance name already registered");
  }
  service_map[instance_name] = internal::WrapIntoContainer(std::move(instance));
  return true;
}

template <typename... Deps>
bool ObjectManager::RegisterGlobalFunction(
  const std::string& registered_function_name,
  internal::GlobalFunction<Deps...> global_function)
{
  if (global_functions.find(registered_function_name) != global_functions.end())
  {
    throw std::runtime_error(
      "ObjectManager::RegisterGlobalFunction: function name already registered");
  }
  global_functions[registered_function_name] =
    [this, global_function](const std::vector<std::string>& dependency_names)
    {
      internal::TypeStringList<Deps...> type_string_list(dependency_names);
      typename internal::MakeIndexSequence<sizeof...(Deps)>::type index_sequence;
      return CallFromTypeStringList(global_function, type_string_list, index_sequence);
    };
  return true;
}

template<typename ServiceType, typename Deleter, typename... Deps, std::size_t... I>
std::unique_ptr<ServiceType, Deleter> ObjectManager::CreateFromTypeStringList(
  internal::InstanceFactoryFunction<ServiceType, Deleter, Deps...> factory_function,
  const internal::TypeStringList<Deps...>& type_string_list,
  internal::IndexSequence<I...> index_sequence)
{
  return factory_function(IndexedArgument<I>(type_string_list)...);
}

template<typename... Deps, std::size_t... I>
bool ObjectManager::CallFromTypeStringList(
  internal::GlobalFunction<Deps...> global_function,
  const internal::TypeStringList<Deps...>& type_string_list,
  internal::IndexSequence<I...> index_sequence)
{
  return global_function(IndexedArgument<I>(type_string_list)...);
}

template <std::size_t I, typename... Deps>
typename internal::DependencyTraits<typename internal::TypeStringList<Deps...>::template
                                      IndexedType<I>>::InjectionType
  ObjectManager::IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list)
{
  return GetInstance<typename internal::TypeStringList<Deps...>::template IndexedType<I>>(
    type_string_list.IndexedString(I) );
}

template <typename T>
typename internal::DependencyTraits<T>::InjectionType
  ObjectManager::GetInstanceImpl(const std::string& instance_name, std::true_type)
{
  auto instance_it = FindInstance<typename internal::DependencyTraits<T>::ValueType>(instance_name);
  typename internal::DependencyTraits<T>::InjectionType result(
    static_cast<typename internal::DependencyTraits<T>::ValueType*>(
      instance_it->second->Release()));
  RemoveInstance<typename internal::DependencyTraits<T>::ValueType>(instance_it);
  return std::move(result);
}

template <typename T>
typename internal::DependencyTraits<T>::InjectionType
  ObjectManager::GetInstanceImpl(const std::string& instance_name, std::false_type)
{
  auto instance_it = FindInstance<typename internal::DependencyTraits<T>::ValueType>(instance_name);
  return static_cast<typename internal::DependencyTraits<T>::InjectionType>(
    instance_it->second->Get());
}

template <typename T>
ObjectManager::ServiceMapIterator
ObjectManager::FindInstance(const std::string& instance_name)
{
  auto service_map_it = instance_map.find<T>();
  if (service_map_it == instance_map.end())
  {
    throw std::runtime_error("ObjectManager::FindInstance: accessing unknow service type");
  }
  auto instance_it = service_map_it->second.find(instance_name);
  if (instance_it == service_map_it->second.end())
  {
    throw std::runtime_error("ObjectManager::FindInstance: accessing unknow instance");
  }
  return instance_it;
}

template <typename T>
void ObjectManager::RemoveInstance(ObjectManager::ServiceMapIterator it)
{
  auto service_map_it = instance_map.find<T>();
  service_map_it->second.erase(it);
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
