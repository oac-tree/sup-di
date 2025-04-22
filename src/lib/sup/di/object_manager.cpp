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

#include "sup/di/object_manager.h"

namespace sup
{
namespace di
{
ObjectManager::ObjectManager()
  : factory_functions{}
  , global_functions{}
  , m_service_store{}
{}

ObjectManager::~ObjectManager() = default;

ErrorCode ObjectManager::CreateInstance(
  const std::string& registered_typename, const std::string& instance_name,
  const std::vector<std::string>& dependency_names)
{
  auto it = factory_functions.find(registered_typename);
  if (it == factory_functions.end())
  {
    return ErrorCode::kFactoryFunctionNotFound;
  }
  return it->second(instance_name, dependency_names);
}

ErrorCode ObjectManager::CallGlobalFunction(const std::string& registered_function_name,
                                            const std::vector<std::string>& dependency_names)
{
  auto it = global_functions.find(registered_function_name);
  if (it == global_functions.end())
  {
    return ErrorCode::kGlobalFunctionNotFound;
  }
  return it->second(dependency_names);
}

ObjectManager& GlobalObjectManager()
{
  static ObjectManager global_object_manager;
  return global_object_manager;
}

}  // namespace di

}  // namespace sup
