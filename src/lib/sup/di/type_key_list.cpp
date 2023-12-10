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

#include "type_key_list.h"

#include <stdexcept>

namespace sup
{
namespace di
{
namespace internal
{

template <typename Key>
Key HeadOf(const std::list<Key>& list)
{
  if (list.empty())
  {
    throw std::runtime_error("Trying to fetch head of empty list");
  }
  return list.front();
}

template <typename Key>
std::list<Key> TailOf(const std::list<Key>& list)
{
  if (list.empty())
  {
    throw std::runtime_error("Trying to create tail of empty list");
  }
  std::list<Key> result{list};
  result.pop_front();
  return result;
}

}  // namespace internal

}  // namespace di

}  // namespace sup
