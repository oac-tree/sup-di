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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_TYPE_LIST_H_
#define SUP_DI_TYPE_LIST_H_

#include <list>
#include <stdexcept>

namespace sup
{
namespace di
{
namespace internal
{

// TypeList
template <typename... Types>
class TypeList;

// Get first type in any type list
template <typename List>
struct FrontT;

template <typename List>
using Front = typename FrontT<List>::Type;

// Specialize FrontT for TypeList with at least one type
template <typename Head, typename... Tail>
struct FrontT<TypeList<Head, Tail...>>
{
  using Type = Head;
};

// Remove first type of any type list
template <typename List>
struct PopFrontT;

template <typename List>
using PopFront = typename PopFrontT<List>::Type;

// Specialize PopFrontT for TypeList with at least one type
template <typename Head, typename... Tail>
struct PopFrontT<TypeList<Head, Tail...>>
{
  using Type = TypeList<Tail...>;
};

// Get Nth type in any type list
template <typename List, std::size_t N>
class NthTypeT : public NthTypeT<PopFront<List>, N-1>
{};

template <typename List>
class NthTypeT<List, 0> : public FrontT<List>
{};

template <typename List, std::size_t N>
using NthType = typename NthTypeT<List, N>::Type;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TYPE_LIST_H_
