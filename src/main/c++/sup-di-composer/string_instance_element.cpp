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

#include "string_instance_element.h"

#include "constants.h"
#include "tree_extract.h"

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{

StringInstanceElement::StringInstanceElement(const sup::xml::TreeData& string_instance_tree)
  : m_instance_name{}
  , m_value{}
{
  ValidateStringInstanceTree(string_instance_tree);
  for (const auto& child : string_instance_tree.Children())
  {
    auto nodename = child.GetNodeName();
    if (nodename == constants::INSTANCE_NAME_TAG)
    {
      utils::SetFromTreeNodeContent(m_instance_name, child);
    }
    else if (nodename == constants::VALUE_TAG)
    {
      utils::SetFromTreeNodeContent(m_value, child);
    }
  }
}

StringInstanceElement::~StringInstanceElement() = default;

void StringInstanceElement::Execute()
{}

void ValidateStringInstanceTree(const sup::xml::TreeData& instance_tree)
{
  sup::xml::ValidateNoContent(instance_tree);
  sup::xml::ValidateNoAttributes(instance_tree);
  sup::xml::ValidateAllowedChildTags(instance_tree,
    { constants::INSTANCE_NAME_TAG, constants::VALUE_TAG });
  sup::xml::ValidateSingleChildWithTag(instance_tree, constants::INSTANCE_NAME_TAG);
  sup::xml::ValidateSingleChildWithTag(instance_tree, constants::VALUE_TAG);
  for (const auto& child : instance_tree.Children())
  {
    sup::xml::ValidateNoAttributes(child);
    sup::xml::ValidateNoChildren(child);
  }
}

}  // namespace di

}  // namespace sup
