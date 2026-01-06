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

#ifndef SUP_DI_TEMPLATE_UTILS_H_
#define SUP_DI_TEMPLATE_UTILS_H_

namespace sup
{
namespace di
{
namespace internal
{
// Class template that defines a Type type member conditionally
template <typename T, bool>
struct ConditionalIdentity
{
  using Type = T;
};

template <typename T>
struct ConditionalIdentity<T, false>
{};

// VoidT implementation
template<typename... Ts>
struct MakeVoid
{
  using Type = void;
};

template<typename... Ts>
using VoidT = typename MakeVoid<Ts...>::Type;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TEMPLATE_UTILS_H_
