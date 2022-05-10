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

#ifndef _SUP_IndexSequence_h_
#define _SUP_IndexSequence_h_

#include <cstddef>

namespace sup
{
namespace di
{
namespace internal
{

template<std::size_t... >
struct IndexSequence {};

template<std::size_t N, std::size_t ...S>
struct MakeIndexSequence
{
  using type = typename MakeIndexSequence<N-1, N-1, S...>::type;
};

template<std::size_t ...S>
struct MakeIndexSequence<0, S...>
{
  using type = IndexSequence<S...>;
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // _SUP_IndexSequence_h_
