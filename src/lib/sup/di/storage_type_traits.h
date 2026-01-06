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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#ifndef SUP_DI_STORAGE_TYPE_TRAITS_H_
#define SUP_DI_STORAGE_TYPE_TRAITS_H_

#include "template_utils.h"

#include <memory>
#include <type_traits>

namespace sup
{
namespace di
{
namespace internal
{
/**
 * @brief Trait to check if a type is a std::unique_ptr
 */
template <typename T>
struct IsUniquePtr : public std::false_type
{};

template <typename T>
struct IsUniquePtr<std::unique_ptr<T>> : public std::true_type
{};

/**
 * @brief Trait to check if a type is a valid type for storing in the ServiceStore
 *
 * @details Valid storage types are non-CV qualified types, excluding: void, functions, references,
 * pointers or std::unique_ptr.
 */
template <typename T>
struct IsValidStorageType
  : public std::conditional<std::is_object<T>::value && !std::is_pointer<T>::value
                              && !IsUniquePtr<typename std::remove_cv<T>::type>::value
                              && !std::is_const<T>::value && !std::is_volatile<T>::value,
                            std::true_type, std::false_type>::type
{};

/**
 * @brief Helper alias template for storage type traits.
 */
template <typename T>
using StorageTypeHelper = ConditionalIdentity<T, IsValidStorageType<T>::value>;

/**
 * @brief Helper type trait (and specializations) for the storage type traits.
 */
template <typename T>
struct StorageTypeT : public StorageTypeHelper<T>
{};

template <typename T>
struct StorageTypeT<T*> : public StorageTypeHelper<typename std::remove_cv<T>::type>
{};

template <typename T>
struct StorageTypeT<T&> : public StorageTypeHelper<typename std::remove_cv<T>::type>
{};

template <typename T>
struct StorageTypeT<std::unique_ptr<T>> : public StorageTypeHelper<T>
{};

template <typename T>
struct StorageTypeT<std::unique_ptr<T>&&> : public StorageTypeHelper<T>
{};

/**
 * @brief Type trait that provides the underlying value type (as it will be stored) from a
 * given dependency type.
 *
 * @details The type trait will first remove the outermost CV qualification and chech if the
 * resulting type is a valid type to store. Special cases are:
 * - T* : std::remove_cv<T>::type if it is a valid storage type;
 * - T& : std::remove_cv<T>::type if it is a valid storage type;
 * - unique_ptr<T> : T if it is a valid storage type;
 * - unique_ptr<T>&& : T if it is a valid storage type.
 */
template <typename T>
using StorageType = typename StorageTypeT<typename std::remove_cv<T>::type>::Type;

/**
 * @brief Type trait to determine if a type can be used as a dependency type, i.e. it has a
 * valid storage type.
 */
template <typename T, typename = void>
struct IsLegalDependencyType : public std::false_type
{};

template <typename T>
struct IsLegalDependencyType<T, VoidT<StorageType<T>>> : public std::true_type
{};

/**
 * @brief Variadic template to determine if all given types can be used as a dependency types, i.e.
 * they all have a valid storage type.
 */
template <typename... Deps>
struct AreLegalDependencyTypes;

template <typename Head, typename... Tail>
struct AreLegalDependencyTypes<Head, Tail...>
  : public std::conditional<IsLegalDependencyType<Head>::value, AreLegalDependencyTypes<Tail...>,
                            std::false_type>::type
{};

template <>
struct AreLegalDependencyTypes<> : public std::true_type
{};

/**
 * @brief Helper alias template defines a member Type equal to T when the given dependency type
 * Dep has a valid storage type.
 */
template <typename T, typename Dep>
using EnableIfValid = ConditionalIdentity<T, IsLegalDependencyType<Dep>::value>;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_STORAGE_TYPE_TRAITS_H_
