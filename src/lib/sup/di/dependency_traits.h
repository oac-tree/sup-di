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

#ifndef SUP_DI_DEPENDENCY_TRAITS_H_
#define SUP_DI_DEPENDENCY_TRAITS_H_

#include <memory>
#include <type_traits>

namespace sup
{
namespace di
{
namespace internal
{

/**
 * @brief Type trait that provides the underlying value type (as it is registered) from the
 * type of a function parameter.
 *
 * @details The type trait will in general remove pointers, references and const volatile
 * qualifiers. A special case is provided for function parameters declared with rvalue references
 * to a unique_ptr: the value type will then be the underlying type of the unique_ptr without
 * const/volatile qualifiers.
 */
template <typename T>
struct ValueTypeT
{
  using Type = typename std::remove_cv<
                 typename std::remove_reference<
                   typename std::remove_pointer<T>::type>::type>::type;
};

template <typename T>
struct ValueTypeT<std::unique_ptr<T>&&>
{
  using Type = typename std::remove_cv<T>::type;
};

template <typename T>
using ValueType = typename ValueTypeT<T>::Type;

/**
 * @brief Type trait that transforms a function parameter type into the type that needs to be
 * returned to inject it into that function.
 *
 * @details The type trait will in general transform the underlying type (for pointers and
 * lvalue references) by removing the const/volatile qualifiers. For value types, the transformation
 * returns an lvalue reference to that type. Finally, for rvalue references to a unique_ptr, the
 * result is a unique_ptr to the underlying type without const/volatile qualifiers.
 */
template <typename T>
struct InjectionTypeT
{
  using Type = ValueType<T>&;
};

template <typename T>
struct InjectionTypeT<T&>
{
  using Type = ValueType<T>&;
};

template <typename T>
struct InjectionTypeT<T*>
{
  using Type = ValueType<T>*;
};

template <typename T>
struct InjectionTypeT<std::unique_ptr<T>&&>
{
  using Type = std::unique_ptr<ValueType<T>>;
};

template <typename T>
using InjectionType = typename InjectionTypeT<T>::Type;

/**
 * @brief Type trait that gives the argument type for a factory function that forwards the
 * argument to a constructor in its body.
 */
template <typename T>
struct FactoryArgumentTypeT
{
  using Type = InjectionType<T>;
};

template <typename T>
struct FactoryArgumentTypeT<std::unique_ptr<T>&&>
{
  using Type = std::unique_ptr<ValueType<T>>&&;
};

template <typename T>
using FactoryArgumentType = typename FactoryArgumentTypeT<T>::Type;

/**
 * @brief Type trait that indicates if passing a variable as the given type requires transfer of
 * ownership.
 *
 * @details A boolean member constant value is defined, which is only true for rvalue references
 * to a unique_ptr.
 */
template <typename T>
struct TransferOwnership : public std::false_type
{};

template <typename T>
struct TransferOwnership<std::unique_ptr<T>&&> : public std::true_type
{};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_DEPENDENCY_TRAITS_H_
