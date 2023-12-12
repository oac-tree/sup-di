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

#ifndef SUP_DI_TEMPLATE_UTILS_H_
#define SUP_DI_TEMPLATE_UTILS_H_

namespace sup
{
namespace di
{
namespace internal
{

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
