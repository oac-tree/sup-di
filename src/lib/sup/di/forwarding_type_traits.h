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

#ifndef SUP_DI_FORWARDING_TYPE_TRAITS_H_
#define SUP_DI_FORWARDING_TYPE_TRAITS_H_

#include "storage_type_traits.h"

namespace sup
{
namespace di
{
namespace internal
{
/**
 * @brief Type trait that provides the parameter type of a function that will forward it to a given
 * dependency type.
 */
template <typename T>
struct ForwardingArgTypeT : public ConditionalIdentity<T&, IsValidStorageType<T>::value>
{};

template <typename T>
struct ForwardingArgTypeT<T*>
  : public ConditionalIdentity<typename std::remove_cv<T>::type*,
                               IsValidStorageType<typename std::remove_cv<T>::type>::value>
{};

template <typename T>
struct ForwardingArgTypeT<T&>
  : public ConditionalIdentity<typename std::remove_cv<T>::type&,
                               IsValidStorageType<typename std::remove_cv<T>::type>::value>
{};

template <typename T>
struct ForwardingArgTypeT<std::unique_ptr<T>>
  : public ConditionalIdentity<std::unique_ptr<T>&&, IsValidStorageType<T>::value>
{};

template <typename T>
struct ForwardingArgTypeT<std::unique_ptr<T>&&>
  : public ConditionalIdentity<std::unique_ptr<T>&&, IsValidStorageType<T>::value>
{};

template <typename T>
using ForwardingArgType = typename ForwardingArgTypeT<typename std::remove_cv<T>::type>::Type;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_FORWARDING_TYPE_TRAITS_H_
