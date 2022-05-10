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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "ObjectManager.h"

namespace sup
{
namespace di
{
ObjectManager::ObjectManager() = default;

ObjectManager::~ObjectManager() = default;

void ObjectManager::CreateInstance(
  const std::string& registered_typename, const std::string& instance_name,
  const std::vector<std::string>& dependency_names)
{
  auto it = factory_functions.find(registered_typename);
  if (it == factory_functions.end())
  {
    throw std::runtime_error("ObjectManager::CreateInstance: typename not registered");
  }
  it->second(instance_name, dependency_names);
}

}  // namespace di

}  // namespace sup
