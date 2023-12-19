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
#include <sup/di/service_store.h>
#include <sup/di/type_functions.h>

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

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
  using RegisteredFactoryFunction =
    std::function<ErrorCode(const std::string&, const std::vector<std::string>&)>;
  using RegisteredGlobalFunction = std::function<ErrorCode(const std::vector<std::string>&)>;
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
                           const std::vector<std::string>& dependency_names);

  /**
   * @brief Call a global function on the named instances.
   *
   * @param registered_function_name Name under which the global function was registered.
   * @param dependency_names List of instance names that need to be injected as dependencies.
   *
   * @return ErrorCode representing success or a specific failure.
   */
  ErrorCode CallGlobalFunction(const std::string& registered_function_name,
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
  internal::ServiceStore<std::string> m_service_store;
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
  return m_service_store.GetInstance<T>(instance_name);
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
      if (dependency_names.size() != sizeof...(Deps))
      {
        return ErrorCode::kWrongNumberOfDependencies;
      }
      bool register_success;
      try
      {
        register_success = m_service_store.StoreInstance(
          internal::InvokeWithStoreArgs<Deps...>(factory_function, m_service_store, dependency_names),
          instance_name);
      }
      catch(const std::runtime_error&)
      {
        return ErrorCode::kDependencyNotFound;
      }
      if (!register_success)
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
  return m_service_store.StoreInstance(std::move(instance), instance_name);
}

template <typename... Deps>
bool ObjectManager::RegisterGlobalFunction(const std::string& registered_function_name,
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
      if (dependency_names.size() != sizeof...(Deps))
      {
        return ErrorCode::kWrongNumberOfDependencies;
      }
      bool call_success;
      try
      {
        call_success =
          internal::InvokeWithStoreArgs<Deps...>(global_function, m_service_store, dependency_names);
      }
      catch(const std::runtime_error&)
      {
        return ErrorCode::kDependencyNotFound;
      }
      if (!call_success)
      {
        return ErrorCode::kGlobalFunctionFailed;
      }
      return ErrorCode::kSuccess;
    };
  return true;
}

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_OBJECT_MANAGER_H_
