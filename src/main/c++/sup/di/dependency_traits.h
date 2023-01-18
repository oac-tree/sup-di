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
 * @brief Class template for handling different types of dependency injection.
 *
 * @details This template is specialized for two types of dependency injection:
 * Injection without ownership passing:
 *    Dep is of type (const) T*
 *    With ValueType = T
 *         InjectionType = T*
 *         TransferOwnership = false_type
 * Injection with ownership passing:
 *    Dep is of type std::unique_ptr<(const) T>&&
 *    With ValueType = T
 *         InjectionType = std::unique_ptr<T>
 *         TransferOwnership = true_type
 */
template <typename Dep>
struct DependencyTraits {};

template <typename T>
struct DependencyTraits<T*>
{
  using ValueType = typename std::enable_if<!std::is_volatile<T>::value,
                               typename std::remove_const<T>::type>::type;
  using InjectionType = typename std::add_pointer<ValueType>::type;
  using TransferOwnership = std::false_type;
};

template <typename T>
struct DependencyTraits<std::unique_ptr<T>&&>
{
  using ValueType = typename std::enable_if<!std::is_volatile<T>::value,
                               typename std::remove_const<T>::type>::type;
  using InjectionType = std::unique_ptr<ValueType>;
  using TransferOwnership = std::true_type;
};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_DEPENDENCY_TRAITS_H_
