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

#ifndef SUP_DI_OWNERSHIP_TRAITS_H_
#define SUP_DI_OWNERSHIP_TRAITS_H_

#include "storage_type_traits.h"

namespace sup
{
namespace di
{
namespace internal
{
/**
 * @brief Type trait that indicates if passing a variable as the given type requires transfer of
 * ownership.
 *
 * @details A boolean member constant value is defined, which is only true for valid (rvalue refs
 * to) unique_ptr.
 */
template <typename T>
struct TransferOwnership : public std::false_type
{};

template <typename T>
struct TransferOwnership<std::unique_ptr<T>> : public IsLegalDependencyType<std::unique_ptr<T>>
{};

template <typename T>
struct TransferOwnership<std::unique_ptr<T>&&> : public IsLegalDependencyType<std::unique_ptr<T>&&>
{};

}  // namespace internal

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_OWNERSHIP_TRAITS_H_
