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

#ifndef SUP_DI_COMPOSER_DI_UTILS_H_
#define SUP_DI_COMPOSER_DI_UTILS_H_

#include "error_codes.h"

#include <string>

namespace sup
{
namespace di
{
namespace utils
{

ErrorCode LoadLibrary(const std::string& library_name);

}  // namespace utils

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_DI_UTILS_H_
