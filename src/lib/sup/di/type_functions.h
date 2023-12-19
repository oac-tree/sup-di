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

#ifndef SUP_DI_TYPE_FUNCTIONS_H_
#define SUP_DI_TYPE_FUNCTIONS_H_

#include <sup/di/dependency_traits.h>

#include <memory>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Type function that forwards a void pointer to the proper injection type.
 */
template <typename T>
struct PointerToInjectionType
{
  static InjectionType<T> Forward(void* arg)
  {
    return *static_cast<ValueType<T>*>(arg);
  }
};

template <typename T>
struct PointerToInjectionType<T*>
{
  static InjectionType<T*> Forward(void* arg)
  {
    return static_cast<InjectionType<T*>>(arg);
  }
};

template <typename T>
struct PointerToInjectionType<std::unique_ptr<T>>
{
  static InjectionType<std::unique_ptr<T>> Forward(void* arg)
  {
    auto typed_arg = static_cast<internal::ValueType<std::unique_ptr<T>>*>(arg);
    return InjectionType<std::unique_ptr<T>>{typed_arg};
  }
};

template <typename T>
struct PointerToInjectionType<std::unique_ptr<T>&&>
{
  static InjectionType<std::unique_ptr<T>&&> Forward(void* arg)
  {
    auto typed_arg = static_cast<internal::ValueType<std::unique_ptr<T>&&>*>(arg);
    return InjectionType<std::unique_ptr<T>&&>{typed_arg};
  }
};

/**
 * @brief Type function that forwards a pointer to a value type to the proper injection type.
 */
template <typename T>
struct ValuePointerToInjectionType
{
  static InjectionType<T> Forward(ValueType<T>* arg)
  {
    return *arg;
  }
};

template <typename T>
struct ValuePointerToInjectionType<T*>
{
  static InjectionType<T*> Forward(ValueType<T*>* arg)
  {
    return arg;
  }
};

template <typename T>
struct ValuePointerToInjectionType<std::unique_ptr<T>>
{
  static InjectionType<std::unique_ptr<T>> Forward(ValueType<std::unique_ptr<T>>* arg)
  {
    return InjectionType<std::unique_ptr<T>>{arg};
  }
};

template <typename T>
struct ValuePointerToInjectionType<std::unique_ptr<T>&&>
{
  static InjectionType<std::unique_ptr<T>&&> Forward(ValueType<std::unique_ptr<T>&&>* arg)
  {
    return InjectionType<std::unique_ptr<T>&&>{arg};
  }
};

/**
 * @brief Type function that perfectly forwards a dependency type to its injection type (for
 * forwarding of arguments in a creation function to a constructor).
 */
template <typename T>
struct ForwardDependencyType
{
  static InjectionType<T> Forward(InjectionType<T>& arg)
  {
    return arg;
  }
};

template <typename T>
struct ForwardDependencyType<T*>
{
  static InjectionType<T*> Forward(InjectionType<T*> arg)
  {
    return arg;
  }
};

template <typename T>
struct ForwardDependencyType<std::unique_ptr<T>&&>
{
  static InjectionType<std::unique_ptr<T>&&>
  Forward(InjectionType<std::unique_ptr<T>&&>& arg)
  {
    return std::move(arg);
  }
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TYPE_FUNCTIONS_H_
