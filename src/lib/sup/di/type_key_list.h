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

#ifndef SUP_DI_TYPE_KEY_LIST_H_
#define SUP_DI_TYPE_KEY_LIST_H_

#include <list>

namespace sup
{
namespace di
{
namespace internal
{

template <typename Key>
Key HeadOf(const std::list<Key>& list);

template <typename Key>
std::list<Key> TailOf(const std::list<Key>& list);

template <typename Key, typename... Types>
class TypeKeyList;

template <typename Key, typename Head, typename... Tail>
class TypeKeyList<Key, Head, Tail...>
{
private:
  Key m_key;
  TypeKeyList<Key, Tail...> m_tail;
public:
  TypeKeyList() {}
  TypeKeyList(const Key& key, const TypeKeyList<Key, Tail...>& tail)
    : m_key{key}, m_tail{tail} {}
  TypeKeyList(const std::list<Key>& key_list)
    : m_key{HeadOf(key_list)}
    , m_tail{TailOf(key_list)} {}
  TypeKeyList(const TypeKeyList<Key, Head, Tail...>& type_key_list)
    : TypeKeyList{type_key_list.GetHead(), type_key_list.GetTail()} {}

  Key& GetHead() { return m_key; }
  const Key& GetHead() const { return m_key; }
  TypeKeyList<Key, Tail...>& GetTail() { return m_tail; }
  const TypeKeyList<Key, Tail...>& GetTail() const { return m_tail; }
};

template <typename Key>
class TypeKeyList<Key>
{};

// Type algorithms
template <typename List>
class FrontT;

template <typename Key, typename Head, typename... Tail>
class FrontT<TypeKeyList<Key, Head, Tail...>>
{
public:
  using Type = Head;
};

template <typename List>
using Front = typename FrontT<List>::Type;

template <typename List>
class PopFrontT;

template <typename Key, typename Head, typename... Tail>
class PopFrontT<TypeKeyList<Key, Head, Tail...>>
{
public:
  using Type = TypeKeyList<Key, Tail...>;
};

template <typename List>
using PopFront = typename PopFrontT<List>::Type;

template <typename List, std::size_t N>
class NthTypeT : public NthTypeT<PopFront<List>, N-1>
{};

template <typename List>
class NthTypeT<List, 0> : public FrontT<List>
{};

template <typename List, std::size_t N>
using NthType = typename NthTypeT<List, N>::Type;

// Key algorithms
template <std::size_t N>
struct TypeKeyListGet
{
  template <typename Key, typename Head, typename... Tail>
  static Key apply(const TypeKeyList<Key, Head, Tail...>& list)
  {
    return TypeKeyListGet<N-1>::apply(list.GetTail());
  }
};

template <>
struct TypeKeyListGet<0>
{
  template <typename Key, typename Head, typename... Tail>
  static Key apply(const TypeKeyList<Key, Head, Tail...>& list)
  {
    return list.GetHead();
  }
};

template <std::size_t N, typename Key, typename... Types>
Key NthKey(const TypeKeyList<Key, Types...>& list)
{
  return TypeKeyListGet<N>::apply(list);
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TYPE_KEY_LIST_H_
