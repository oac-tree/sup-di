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

#include "global_function.h"

#include "constants.h"
#include "exceptions.h"
#include "tree_extract.h"

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{
namespace utils
{

FunctionDefinition::FunctionDefinition()
  : m_function_name{}
  , m_dependencies{}
{}

void ValidateFunctionTree(const sup::xml::TreeData& function_tree)
{
  sup::xml::ValidateNoContent(function_tree);
  sup::xml::ValidateNoAttributes(function_tree);
  sup::xml::ValidateAllowedChildTags(function_tree,
    { constants::FUNCTION_NAME_TAG, constants::DEPENDENCY_TAG });
  sup::xml::ValidateSingleChildWithTag(function_tree, constants::FUNCTION_NAME_TAG);
  for (const auto& child : function_tree.Children())
  {
    sup::xml::ValidateNoAttributes(child);
    sup::xml::ValidateNoChildren(child);
  }
}

FunctionDefinition ParseFunctionDefinition(const sup::xml::TreeData& function_tree)
{
  FunctionDefinition result;
  for (const auto& child : function_tree.Children())
  {
    auto nodename = child.GetNodeName();
    if (nodename == constants::FUNCTION_NAME_TAG)
    {
      SetFromTreeNodeContent(result.m_function_name, child);
    }
    else if (nodename == constants::DEPENDENCY_TAG)
    {
      AppendFromTreeNodeContent(result.m_dependencies, child);
    }
  }
  return result;
}

}  // namespace utils

}  // namespace di

}  // namespace sup
