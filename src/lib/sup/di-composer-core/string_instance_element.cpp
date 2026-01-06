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

#include "string_instance_element.h"

#include "constants.h"
#include "exceptions.h"
#include "tree_extract.h"

#include <sup/di/object_manager.h>

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{

StringInstanceElement::StringInstanceElement(const sup::xml::TreeData& string_instance_tree)
  : m_instance_name{}
  , m_value{}
{
  ValidateLiteralInstanceTree(string_instance_tree);
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
{
  auto& global_object_manager = GlobalObjectManager();
  if (!global_object_manager.RegisterInstance(m_value, m_instance_name))
  {
    std::string error_message = "StringInstanceElement::Execute(): creating string with name [" +
      m_instance_name + "] and value [" + m_value + "] failed";
    throw sup::di::RuntimeException(error_message);
  }
}

}  // namespace di

}  // namespace sup
