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

template <typename T>
using StorageTypeHelper = ConditionalIdentity<T, IsValidStorageType<T>::value>;

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

template <typename T>
using StorageType2 = typename StorageTypeT<typename std::remove_cv<T>::type>::Type;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_STORAGE_TYPE_TRAITS_H_
