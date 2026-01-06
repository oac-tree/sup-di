/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition and implementation for dependency injection templates in SUP.
 *
 * Author        : Ricardo Torres (Ext)
 *
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include "keep_alive.h"

#include <chrono>
#include <limits>
#include <thread>

namespace sup
{
namespace di
{
namespace services
{

bool KeepAliveFor(std::uint32_t seconds)
{
  while (seconds-- > 0)
  {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return true;
}

bool KeepAlive()
{
  // Keep alive for 137 years
  return KeepAliveFor(std::numeric_limits<std::uint32_t>::max());
}

}  // namespace services

}  // namespace di

}  // namespace sup
