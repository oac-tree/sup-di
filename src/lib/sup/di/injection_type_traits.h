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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_INJECTION_TYPE_TRAITS_H_
#define SUP_DI_INJECTION_TYPE_TRAITS_H_

#include "storage_type_traits.h"

namespace sup
{
namespace di
{
namespace internal
{
/**
 * @brief Helper type trait (and specializations) for the injection type traits.
 */
template <typename T>
struct InjectionTypeT : public EnableIfValid<T&, T>
{};

template <typename T>
struct InjectionTypeT<T*> : public EnableIfValid<typename std::remove_cv<T>::type*, T*>
{};

template <typename T>
struct InjectionTypeT<T&> : public EnableIfValid<typename std::remove_cv<T>::type&, T&>
{};

template <typename T>
struct InjectionTypeT<std::unique_ptr<T>>
  : public EnableIfValid<std::unique_ptr<T>, std::unique_ptr<T>>
{};

template <typename T>
struct InjectionTypeT<std::unique_ptr<T>&&>
  : public EnableIfValid<std::unique_ptr<T>, std::unique_ptr<T>&&>
{};

/**
 * @brief Type trait that provides the argument type to inject into a given dependency type.
 *
 * @details The type trait will first remove the outermost CV qualification and chech if the
 * resulting type is a valid type to store and add a lvalue reference. Special cases are:
 * - T* : std::remove_cv<T>::type* if std::remove_cv<T>::type is a valid storage type;
 * - T& : std::remove_cv<T>::type& if std::remove_cv<T>::type is a valid storage type;
 * - unique_ptr<T> : unique_ptr<T> if T is a valid storage type;
 * - unique_ptr<T>&& : unique_ptr<T> if T is a valid storage type.
 */
template <typename T>
using InjectionType = typename InjectionTypeT<typename std::remove_cv<T>::type>::Type;

/**
 * @brief Type function that forwards a pointer to a storage type to the proper type for injection.
 *
 * @tparam T Dependency type.
 */
template <typename T>
struct ValuePointerToInjectionType
{
  static InjectionType<T> Forward(StorageType<T>* arg)
  {
    return *arg;
  }
};

template <typename T>
struct ValuePointerToInjectionType<T*>
{
  static InjectionType<T*> Forward(StorageType<T*>* arg)
  {
    return arg;
  }
};

template <typename T>
struct ValuePointerToInjectionType<std::unique_ptr<T>>
{
  static InjectionType<std::unique_ptr<T>> Forward(StorageType<std::unique_ptr<T>>* arg)
  {
    return InjectionType<std::unique_ptr<T>>{arg};
  }
};

template <typename T>
struct ValuePointerToInjectionType<std::unique_ptr<T>&&>
{
  static InjectionType<std::unique_ptr<T>&&> Forward(StorageType<std::unique_ptr<T>&&>* arg)
  {
    return InjectionType<std::unique_ptr<T>&&>{arg};
  }
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_INJECTION_TYPE_TRAITS_H_
