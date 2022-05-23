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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef _SUP_DependencyTraits_h_
#define _SUP_DependencyTraits_h_

#include <memory>
#include <type_traits>

namespace sup
{
namespace di
{
namespace internal
{

template <typename Dep>
struct DependencyTraits {};

template <typename Dep>
struct DependencyTraits<Dep*>
{
  using ValueType = typename std::remove_cv<Dep>::type;
  using InjectionType = typename std::add_pointer<ValueType>::type;
  using TransferOwnership = std::false_type;
};

template <typename Dep>
struct DependencyTraits<std::unique_ptr<Dep>&&>
{
  using ValueType = typename std::remove_cv<Dep>::type;
  using InjectionType = std::unique_ptr<Dep>;
  using TransferOwnership = std::true_type;
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // _SUP_DependencyTraits_h_
