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

#include "object_composer.h"

#include "constants.h"
#include "exceptions.h"
#include "global_function.h"
#include "instances.h"

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{
namespace utils
{

void ValidateLoadLibraryTree(const sup::xml::TreeData& load_library_tree)
{
  sup::xml::ValidateNoAttributes(load_library_tree);
  sup::xml::ValidateNoChildren(load_library_tree);
}

void ValidateComposerTree(const sup::xml::TreeData& composer_tree)
{
  sup::xml::ValidateNoContent(composer_tree);
  sup::xml::ValidateAllowedChildTags(composer_tree,
    { constants::LOAD_LIBRARY_TAG, constants::CREATE_INSTANCE_TAG, constants::STRING_INSTANCE_TAG,
      constants::CALL_FUNCTION_TAG });
  for (const auto& child : composer_tree.Children())
  {
    auto child_tag = child.GetNodeName();
    if (child_tag == constants::LOAD_LIBRARY_TAG)
    {
      ValidateLoadLibraryTree(child);
    }
    else if (child_tag == constants::CREATE_INSTANCE_TAG)
    {
      ValidateInstanceTree(child);
    }
    else if (child_tag == constants::STRING_INSTANCE_TAG)
    {
      ValidateStringInstanceTree(child);
    }
    else if (child_tag == constants::CALL_FUNCTION_TAG)
    {
      ValidateFunctionTree(child);
    }
  }
}

void ExecuteComposerTree(const sup::xml::TreeData& composer_tree)
{
  (void)composer_tree;
}

}  // namespace utils

}  // namespace di

}  // namespace sup

