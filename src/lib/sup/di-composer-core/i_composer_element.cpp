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

#include "i_composer_element.h"

#include "constants.h"

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{

IComposerElement::~IComposerElement() = default;

void ValidateLiteralInstanceTree(const sup::xml::TreeData& instance_tree)
{
  sup::xml::ValidateNoContent(instance_tree);
  sup::xml::ValidateNoAttributes(instance_tree);
  sup::xml::ValidateAllowedChildTags(instance_tree,
    { constants::INSTANCE_NAME_TAG, constants::VALUE_TAG });
  sup::xml::ValidateSingleChildWithTag(instance_tree, constants::INSTANCE_NAME_TAG);
  for (const auto& child : instance_tree.Children())
  {
    sup::xml::ValidateNoAttributes(child);
    sup::xml::ValidateNoChildren(child);
  }
}

}  // namespace di

}  // namespace sup
