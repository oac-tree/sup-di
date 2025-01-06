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

#ifndef SUP_DI_INDEX_SEQUENCE_H_
#define SUP_DI_INDEX_SEQUENCE_H_

#include <cstddef>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Class template representing a sequence of unsigned integers.
 */
template <std::size_t...>
struct IndexSequence {};

/**
 * @brief Class template generating a sequence of unsigned integers.
 *
 * @details MakeIndexSequence<N> represents IndexSequence<0, 1, ..., N-1>.
 */
template <std::size_t N, std::size_t... Idx>
struct MakeIndexSequenceT : public MakeIndexSequenceT<N-1, N-1, Idx...>
{};

template <std::size_t... Idx>
struct MakeIndexSequenceT<0, Idx...>
{
  using Type = IndexSequence<Idx...>;
};

template <std::size_t N>
using MakeIndexSequence = typename MakeIndexSequenceT<N>::Type;

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_INDEX_SEQUENCE_H_
