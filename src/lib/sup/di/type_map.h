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

#ifndef SUP_DI_TYPE_MAP_H_
#define SUP_DI_TYPE_MAP_H_

#include <map>
#include <typeinfo>
#include <typeindex>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Class template for a map whose keys are types instead of values.
 */
template <typename Val>
class TypeMap
{
  using Container = std::map<std::type_index, Val>;
public:
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;

  TypeMap() : container{} {}

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
  void put(Val &&value)
  {
    container[TypeId<Key>()] = std::forward<Val>(value);
  }

  template <class Key>
  static std::type_index TypeId()
  {
    return std::type_index(typeid(Key));
  }

private:
  Container container;
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TYPE_MAP_H_
