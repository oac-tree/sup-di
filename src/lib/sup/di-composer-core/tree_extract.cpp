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

#include "tree_extract.h"

#include "exceptions.h"

namespace sup
{
namespace di
{
namespace utils
{

void SetFromTreeNodeContent(std::string& dest, const sup::xml::TreeData& tree)
{
  auto content = tree.GetContent();
  if (content.empty())
  {
    std::string error_message = "SetFromTreeNodeContent(): content of tag [" +
      tree.GetNodeName() + "] must not be empty";
    throw sup::di::ParseException(error_message);
  }
  dest = content;
}

void AppendFromTreeNodeContent(std::vector<std::string>& dest, const sup::xml::TreeData& tree)
{
  auto content = tree.GetContent();
  if (content.empty())
  {
    std::string error_message = "AppendFromTreeNodeContent: content of tag [" +
       tree.GetNodeName() + "] must not be empty";
    throw sup::di::ParseException(error_message);
  }
  dest.push_back(content);
}

}  // namespace utils

}  // namespace di

}  // namespace sup

