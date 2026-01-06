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

#include "instance_element.h"

#include "constants.h"
#include "exceptions.h"
#include "tree_extract.h"

#include <sup/di/object_manager.h>

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{

InstanceElement::InstanceElement(const sup::xml::TreeData& instance_tree)
  : m_type_name{}
  , m_instance_name{}
  , m_dependencies{}
{
  ValidateInstanceTree(instance_tree);
  for (const auto& child : instance_tree.Children())
  {
    auto nodename = child.GetNodeName();
    if (nodename == constants::TYPE_NAME_TAG)
    {
      utils::SetFromTreeNodeContent(m_type_name, child);
    }
    else if (nodename == constants::INSTANCE_NAME_TAG)
    {
      utils::SetFromTreeNodeContent(m_instance_name, child);
    }
    else if (nodename == constants::DEPENDENCY_TAG)
    {
      utils::AppendFromTreeNodeContent(m_dependencies, child);
    }
  }
}

InstanceElement::~InstanceElement() = default;

void InstanceElement::Execute()
{
  auto& global_object_manager = GlobalObjectManager();
  auto result = global_object_manager.CreateInstance(m_type_name, m_instance_name, m_dependencies);
  if ( result != ErrorCode::kSuccess)
  {
    std::string error_message = "InstanceElement::Execute(): creating instance with type [" +
      m_type_name + "] and name [" + m_instance_name + "] failed with error [" +
      ErrorString(result) + "]";
    throw sup::di::RuntimeException(error_message);
  }
}

void ValidateInstanceTree(const sup::xml::TreeData& instance_tree)
{
  sup::xml::ValidateNoContent(instance_tree);
  sup::xml::ValidateNoAttributes(instance_tree);
  sup::xml::ValidateAllowedChildTags(instance_tree,
    { constants::TYPE_NAME_TAG, constants::INSTANCE_NAME_TAG, constants::DEPENDENCY_TAG });
  sup::xml::ValidateSingleChildWithTag(instance_tree, constants::TYPE_NAME_TAG);
  sup::xml::ValidateSingleChildWithTag(instance_tree, constants::INSTANCE_NAME_TAG);
  for (const auto& child : instance_tree.Children())
  {
    sup::xml::ValidateNoAttributes(child);
    sup::xml::ValidateNoChildren(child);
  }
}

}  // namespace di

}  // namespace sup
