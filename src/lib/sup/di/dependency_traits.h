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

#include "template_utils.h"

#include <memory>
#include <type_traits>

namespace sup
{
namespace di
{
namespace internal
{
// Forward declaration of DependencyTraits
template <typename T>
struct DependencyTraits;

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
using ValueType = typename DependencyTraits<T>::ValueTypeT::Type;

/**
 * @brief Type trait that transforms a function parameter type into the type that needs to be
 * returned to inject it into that function.
 *
 * @details The type trait will in general transform the underlying type (for pointers and
 * lvalue references) by removing the const/volatile qualifiers. For value types, the transformation
 * returns an lvalue reference to that type. Finally, for rvalue references to a unique_ptr, the
 * result is a unique_ptr to the underlying type without const/volatile qualifiers.
 *
 * @note The same restrictions apply as for ValueType.
 */
template <typename T>
using InjectionType = typename DependencyTraits<T>::InjectionTypeT::Type;

/**
 * @brief Type trait that gives the argument type for a factory function that forwards the
 * argument to a constructor in its body.
 *
 * @note The same restrictions apply as for ValueType.
 */
template <typename T>
using FactoryArgumentType = typename DependencyTraits<T>::FactoryArgumentTypeT::Type;

/**
 * @brief Type trait that indicates if passing a variable as the given type requires transfer of
 * ownership.
 *
 * @details A boolean member constant value is defined, which is only true for (rvalue references
 * to) a unique_ptr.
 */
template <typename T>
struct TransferOwnership : public DependencyTraits<T>::TransferOwnerShipT
{};

// Check if type is same as its ValueType, if that exists
template <typename T, typename = void>
struct IsSameAsValueType : std::false_type {};

template <typename T>
struct IsSameAsValueType<T, VoidT<ValueType<T>>>
  : public std::is_same<T, ValueType<T>> {};

// Type functions to determine if a type(s) can be used as a dependency type, i.e. it has a ValueType
template <typename T, typename = void>
struct IsLegalDependencyType : std::false_type
{};

template <typename T>
struct IsLegalDependencyType<T, VoidT<ValueType<T>>> : std::true_type
{};

template <typename... Deps>
struct AreLegalDependencyTypes;

template <typename Head, typename... Tail>
struct AreLegalDependencyTypes<Head, Tail...>
  : public std::conditional<IsLegalDependencyType<Head>::value, AreLegalDependencyTypes<Tail...>, std::false_type>::type
{};

template <>
struct AreLegalDependencyTypes<> : public std::true_type
{};

// Type function that defines a Type type member with an added pointer if the given type has
// a Type type member.
template <typename T, typename = void>
struct AddPointer
{};

template <typename T>
struct AddPointer<T, VoidT<typename T::Type>>
{
  using Type = typename T::Type*;
};

// Type function that defines a Type type member with an added lvalue reference if the given type
// has a Type type member.
template <typename T, typename = void>
struct AddReference
{};

template <typename T>
struct AddReference<T, VoidT<typename T::Type>>
{
  using Type = typename T::Type&;
};

// Specialization of DependencyTraits for different classes of type arguments.
template <typename T>
struct DependencyTraits
{
  using ValueTypeT = Identity<typename std::remove_cv<
                                typename std::remove_reference<
                                  typename std::remove_pointer<T>::type>::type>::type>;
  using InjectionTypeT = AddReference<ValueTypeT>;
  using FactoryArgumentTypeT = AddReference<ValueTypeT>;
  using TransferOwnerShipT = std::false_type;
};

template <typename T>
struct DependencyTraits<T*>
{
  using ValueTypeT = Identity<typename std::remove_cv<
                                typename std::remove_reference<T>::type>::type>;
  using InjectionTypeT = AddPointer<ValueTypeT>;
  using FactoryArgumentTypeT = AddPointer<ValueTypeT>;
  using TransferOwnerShipT = std::false_type;
};

template <typename T>
struct DependencyTraits<T&>
{
  using ValueTypeT = Identity<typename std::remove_cv<T>::type>;
  using InjectionTypeT = AddReference<ValueTypeT>;
  using FactoryArgumentTypeT = AddReference<ValueTypeT>;
  using TransferOwnerShipT = std::false_type;
};

template <typename T>
struct DependencyTraits<std::unique_ptr<T>>
{
  using ValueTypeT = ConditionalIdentity<T, IsSameAsValueType<T>::value>;
  using InjectionTypeT = ConditionalIdentity<std::unique_ptr<T>, IsSameAsValueType<T>::value>;
  using FactoryArgumentTypeT =
    ConditionalIdentity<std::unique_ptr<T>&&, IsSameAsValueType<T>::value>;
  using TransferOwnerShipT = IsSameAsValueType<T>;
};

template <typename T>
struct DependencyTraits<std::unique_ptr<T>&&>
{
  using ValueTypeT = ConditionalIdentity<T, IsSameAsValueType<T>::value>;
  using InjectionTypeT = ConditionalIdentity<std::unique_ptr<T>, IsSameAsValueType<T>::value>;
  using FactoryArgumentTypeT =
    ConditionalIdentity<std::unique_ptr<T>&&, IsSameAsValueType<T>::value>;
  using TransferOwnerShipT = IsSameAsValueType<T>;
};

template <typename T>
struct DependencyTraits<T&&>
{
  using TransferOwnerShipT = std::false_type;
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_DEPENDENCY_TRAITS_H_
