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

#ifndef _SUP_TypeMap_h_
#define _SUP_TypeMap_h_

#include <map>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Class template for a map whose keys are types instead of values.
 */
template <typename ValueType>
class TypeMap
{
  using Container = std::map<int, ValueType>;
public:
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  iterator begin() { return container.begin(); }
  iterator end() { return container.end(); }
  const_iterator begin() const { return container.begin(); }
  const_iterator end() const { return container.end(); }
  const_iterator cbegin() const { return container.cbegin(); }
  const_iterator cend() const { return container.cend(); }

  template <class Key>
  iterator find() { return container.find(TypeId<Key>()); }
  template <class Key>
  const_iterator find() const { return container.find(TypeId<Key>()); }
  template <class Key>
  void put(ValueType &&value)
  {
    container[TypeId<Key>()] = std::forward<ValueType>(value);
  }

  template <class Key>
  static int TypeId()
  {
    static int id = ++last_type_id;
    return id;
  }

private:
  static int last_type_id;
  Container container;
};

template <class T>
int TypeMap<T>::last_type_id{0};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // _SUP_TypeMap_h_
