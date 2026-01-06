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

#ifndef SUP_DI_ERROR_CODES_H_
#define SUP_DI_ERROR_CODES_H_

#include <string>
#include <cstdint>

namespace sup
{
namespace di
{

enum class ErrorCode : std::uint32_t
{
  kSuccess = 0,
  kFactoryFunctionNotFound,
  kGlobalFunctionNotFound,
  kDependencyNotFound,
  kWrongNumberOfDependencies,
  kInvalidInstanceName,
  kGlobalFunctionFailed,
  kLibraryNotLoaded
};

std::string ErrorString(const ErrorCode& code);

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_ERROR_CODES_H_
