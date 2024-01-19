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
template <typename T, typename = void>
struct StorageTypeT
{};

template <typename T>
using StorageType2 = typename StorageTypeT<typename std::remove_cv<T>::type>::Type;

// Check if type is same as its StorageType, if that exists
template <typename T, typename = void>
struct IsSameAsStorageType : std::false_type {};

template <typename T>
struct IsSameAsStorageType<T, VoidT<StorageType2<T>>>
  : public std::is_same<T, StorageType2<T>> {};

template <typename T>
struct StorageTypeT<T, typename std::enable_if<std::is_object<T>::value>::type>
{
  using Type = T;
};

template <typename T>
struct StorageTypeT<T*, void>
  : public ConditionalIdentity<typename std::remove_cv<T>::type,
                               IsSameAsStorageType<typename std::remove_cv<T>::type>::value>
{};

template <typename T>
struct StorageTypeT<T&, void>
  : public ConditionalIdentity<typename std::remove_cv<T>::type,
                               IsSameAsStorageType<typename std::remove_cv<T>::type>::value>
{};

template <typename T>
struct StorageTypeT<std::unique_ptr<T>, void>
  : public ConditionalIdentity<typename std::remove_cv<T>::type,
                               IsSameAsStorageType<typename std::remove_cv<T>::type>::value>
{};

template <typename T>
struct StorageTypeT<std::unique_ptr<T>&&, void>
  : public ConditionalIdentity<typename std::remove_cv<T>::type,
                               IsSameAsStorageType<typename std::remove_cv<T>::type>::value>
{};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_STORAGE_TYPE_TRAITS_H_
