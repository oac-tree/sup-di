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

#ifndef SUP_DI_COMPOSER_TREE_EXTRACT_H_
#define SUP_DI_COMPOSER_TREE_EXTRACT_H_

#include <sup/xml/tree_data.h>

#include <vector>

namespace sup
{
namespace di
{
namespace utils
{

void SetFromTreeNodeContent(std::string& dest, const sup::xml::TreeData& tree);

void AppendFromTreeNodeContent(std::vector<std::string>& dest, const sup::xml::TreeData& tree);

}  // namespace utils

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_TREE_EXTRACT_H_
