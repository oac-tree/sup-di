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

#include "instances.h"

#include "constants.h"
#include "exceptions.h"

#include <sup/xml/tree_data_validate.h>

#include <algorithm>

namespace
{

void SetTypeNameOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                           const sup::xml::TreeData& type_tree);
void SetInstanceNameOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                               const sup::xml::TreeData& name_tree);
void AddDependencyOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                             const sup::xml::TreeData& dep_tree);

}  // unnamed namespace

namespace sup
{
namespace di
{
namespace utils
{

InstanceDefinition::InstanceDefinition()
  : m_type_name{}
  , m_instance_name{}
  , m_dependencies{}
{}

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

InstanceDefinition ParseInstanceDefinition(const sup::xml::TreeData& instance_tree)
{
  InstanceDefinition result;
  for (const auto& child : instance_tree.Children())
  {
    auto nodename = child.GetNodeName();
    if (nodename == constants::TYPE_NAME_TAG)
    {
      SetTypeNameOfInstance(result, child);
    }
    else if (nodename == constants::INSTANCE_NAME_TAG)
    {
      SetInstanceNameOfInstance(result, child);
    }
    else if (nodename == constants::DEPENDENCY_TAG)
    {
      AddDependencyOfInstance(result, child);
    }
  }
  return result;
}

}  // namespace utils

}  // namespace di

}  // namespace sup

namespace
{
void SetTypeNameOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                           const sup::xml::TreeData& type_tree)
{
  auto instance_type = type_tree.GetContent();
  if (instance_type.empty())
  {
    std::string error_message =
      "sup::di::utils::SetTypeNameOfInstance(): content of tag [" +
      sup::di::constants::TYPE_NAME_TAG + "] must not be empty";
    throw sup::di::ParseException(error_message);
  }
  instance_def.m_type_name = instance_type;
}

void SetInstanceNameOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                               const sup::xml::TreeData& name_tree)
{
  auto instance_name = name_tree.GetContent();
  if (instance_name.empty())
  {
    std::string error_message =
      "sup::di::utils::SetInstanceNameOfInstance(): content of tag [" +
      sup::di::constants::INSTANCE_NAME_TAG +"] must not be empty";
    throw sup::di::ParseException(error_message);
  }
  instance_def.m_instance_name = instance_name;
}

void AddDependencyOfInstance(sup::di::utils::InstanceDefinition& instance_def,
                             const sup::xml::TreeData& dep_tree)
{
  auto dependency_name = dep_tree.GetContent();
  if (dependency_name.empty())
  {
    std::string error_message =
      "sup::di::utils::AddDependencyOfInstance(): content of tag [" +
       sup::di::constants::DEPENDENCY_TAG + "] must not be empty";
    throw sup::di::ParseException(error_message);
  }
  instance_def.m_dependencies.push_back(dependency_name);
}

}  // unnamed namespace
