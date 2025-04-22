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

#include "error_codes.h"

#include <map>

namespace sup
{
namespace di
{

std::string ErrorString(const ErrorCode& code)
{
  static const std::map<ErrorCode, std::string> code_map{
    { ErrorCode::kSuccess, "Success" },
    { ErrorCode::kFactoryFunctionNotFound, "Factory function not found" },
    { ErrorCode::kGlobalFunctionNotFound, "Global function not found" },
    { ErrorCode::kDependencyNotFound, "Dependency not found" },
    { ErrorCode::kWrongNumberOfDependencies, "Wrong number of dependencies" },
    { ErrorCode::kInvalidInstanceName, "Invalid instance name" },
    { ErrorCode::kGlobalFunctionFailed, "Global function failed" },
    { ErrorCode::kLibraryNotLoaded, "Could not load library"}
  };
  auto it = code_map.find(code);
  if (it == code_map.end())
  {
    return "Unknown error code";
  }
  return it->second;
}
}  // namespace di

}  // namespace sup
