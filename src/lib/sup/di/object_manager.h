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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_OBJECT_MANAGER_H_
#define SUP_DI_OBJECT_MANAGER_H_

#include <sup/di/dependency_traits.h>
#include <sup/di/error_codes.h>
#include <sup/di/index_sequence.h>
#include <sup/di/instance_container.h>
#include <sup/di/type_functions.h>
#include <sup/di/type_map.h>
#include <sup/di/type_key_list.h>

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace sup
{
namespace di
{
namespace internal
{
template <typename... Types>
using TypeStringList = TypeKeyList<std::string, Types...>;

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
    std::function<ErrorCode(const std::string&, const std::list<std::string>&)>;
  using RegisteredGlobalFunction = std::function<ErrorCode(const std::list<std::string>&)>;
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
   *
   * @return ErrorCode representing success or a specific failure.
   */
  ErrorCode CreateInstance(const std::string& registered_typename,
                           const std::string& instance_name,
                           const std::list<std::string>& dependency_names);

  /**
   * @brief Call a global function on the named instances.
   *
   * @param registered_function_name Name under which the global function was registered.
   * @param dependency_names List of instance names that need to be injected as dependencies.
   *
   * @return ErrorCode representing success or a specific failure.
   */
  ErrorCode CallGlobalFunction(const std::string& registered_function_name,
                               const std::list<std::string>& dependency_names);

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
  internal::InjectionType<T> GetInstance(const std::string& instance_name);

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
  ErrorCode CallFromTypeStringList(internal::GlobalFunction<Deps...> global_function,
                                   const internal::TypeStringList<Deps...>& type_string_list,
                                   internal::IndexSequence<I...> index_sequence);

  /**
   * @brief Helper method to retrieve an instance of the correct type, based on an index.
   */
  template <std::size_t I, typename... Deps>
  internal::InjectionType<internal::NthType<internal::TypeStringList<Deps...>, I>>
    IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list);

  /**
   * @brief Helper method to retrieve an instance when ownership needs to be passed.
   */
  template <typename T>
  internal::InjectionType<T> GetInstanceImpl(const std::string& instance_name,
                                             std::true_type transfer_ownership);

  /**
   * @brief Helper method to retrieve an instance when ownership is managed by the ObjectManager.
   */
  template <typename T>
  internal::InjectionType<T> GetInstanceImpl(const std::string& instance_name,
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
 * @brief Function template for a factory function that forwards its arguments to a constructor
 * with the same signature.
 */
template <typename ServiceType, typename ConcreteType, typename... Deps>
std::unique_ptr<ServiceType>
ForwardingInstanceFactoryFunction(internal::FactoryArgumentType<Deps>... dependencies)
{
  return std::unique_ptr<ServiceType>(
    new ConcreteType(internal::ForwardDependencyType<Deps>::Forward(dependencies)...));
}

/**
 * @brief Retrieve global ObjectManager instance.
 */
ObjectManager& GlobalObjectManager();

template <typename T>
internal::InjectionType<T> ObjectManager::GetInstance(const std::string& instance_name)
{
  return GetInstanceImpl<T>(instance_name, internal::TransferOwnership<T>{});
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
    [this, factory_function](const std::string& instance_name, const std::list<std::string>& dependency_names)
    {
      if (dependency_names.size() != sizeof...(Deps))
      {
        return ErrorCode::kWrongNumberOfDependencies;
      }
      internal::TypeStringList<Deps...> type_string_list(dependency_names);
      internal::MakeIndexSequence<sizeof...(Deps)> index_sequence;
      bool register_succes;
      try
      {
        auto p_instance = CreateFromTypeStringList(
          factory_function, type_string_list, index_sequence);
        register_succes = RegisterInstance(std::move(p_instance), instance_name);
      }
      catch(const std::runtime_error&)
      {
        return ErrorCode::kDependencyNotFound;
      }
      if (!register_succes)
      {
        return ErrorCode::kInvalidInstanceName;
      }
      return ErrorCode::kSuccess;
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
    return false;
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
    [this, global_function](const std::list<std::string>& dependency_names)
    {
      if (dependency_names.size() != sizeof...(Deps))
      {
        return ErrorCode::kWrongNumberOfDependencies;
      }
      internal::TypeStringList<Deps...> type_string_list(dependency_names);
      internal::MakeIndexSequence<sizeof...(Deps)> index_sequence;
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
ErrorCode ObjectManager::CallFromTypeStringList(
  internal::GlobalFunction<Deps...> global_function,
  const internal::TypeStringList<Deps...>& type_string_list,
  internal::IndexSequence<I...> index_sequence)
{
  bool function_result;
  try
  {
    function_result = global_function(IndexedArgument<I>(type_string_list)...);
  }
  catch(const std::runtime_error&)
  {
    return ErrorCode::kDependencyNotFound;
  }
  if (!function_result)
  {
    return ErrorCode::kGlobalFunctionFailed;
  }
  return ErrorCode::kSuccess;
}

template <std::size_t I, typename... Deps>
internal::InjectionType<internal::NthType<internal::TypeStringList<Deps...>, I>>
  ObjectManager::IndexedArgument(const internal::TypeStringList<Deps...>& type_string_list)
{
  return GetInstance<internal::NthType<internal::TypeStringList<Deps...>, I>>(
    internal::NthKey<I>(type_string_list) );
}

template <typename T>
internal::InjectionType<T> ObjectManager::GetInstanceImpl(const std::string& instance_name,
                                                          std::true_type)
{
  auto instance_it = FindInstance<internal::ValueType<T>>(instance_name);
  auto result = internal::PointerToInjectionType<T>::Forward(instance_it->second->Release());
  RemoveInstance<internal::ValueType<T>>(instance_it);
  return std::move(result);
}

template <typename T>
internal::InjectionType<T> ObjectManager::GetInstanceImpl(const std::string& instance_name,
                                                          std::false_type)
{
  auto instance_it = FindInstance<internal::ValueType<T>>(instance_name);
  return internal::PointerToInjectionType<T>::Forward(instance_it->second->Get());
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

#endif  // SUP_DI_OBJECT_MANAGER_H_
