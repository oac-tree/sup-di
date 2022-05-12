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

#ifndef _SUP_TypeStringList_h_
#define _SUP_TypeStringList_h_

#include <array>
#include <string>
#include <vector>

namespace sup
{
namespace di
{
namespace internal
{

template <typename... Args>
class TypeStringList
{
public:
  TypeStringList(const std::vector<std::string>& string_list);
  ~TypeStringList() = default;

  template<std::size_t I> using IndexedType =
    typename std::tuple_element<I, std::tuple<Args...>>::type;

  std::string IndexedString(std::size_t i) const
  {
    return names[i];
  }

private:
  std::array<std::string, sizeof...(Args)> names;
};

template <typename... Args>
TypeStringList<Args...>::TypeStringList(const std::vector<std::string>& string_list)
{
  if (string_list.size() != sizeof...(Args))
  {
    throw std::runtime_error("TypeStringList constructor: size of argument names doesn't "
                             "match number of expected argument types");
  }
  for(std::size_t i=0; i<sizeof...(Args); ++i)
  {
    names[i] = string_list[i];
  }
}

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // _SUP_TypeStringList_h_
