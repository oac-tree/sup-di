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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "instance_container.h"

namespace sup
{
namespace di
{
namespace internal
{
AbstractInstanceContainer::~AbstractInstanceContainer() = default;

void* GetInstancePointer(AbstractInstanceContainer& container, std::true_type)
{
  return container.Release();
}

void* GetInstancePointer(AbstractInstanceContainer& container, std::false_type)
{
  return container.Get();
}

}  // namespace internal

}  // namespace di

}  // namespace sup
