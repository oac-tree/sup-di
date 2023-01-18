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

#include "utils.h"
#include "exceptions.h"

#include <sup/xml/tree_data_parser.h>

#include <dlfcn.h>

namespace sup
{
namespace di
{

std::unique_ptr<sup::xml::TreeData> ComposerTreeFromFile(const std::string& filename)
{
  return sup::xml::TreeDataFromFile(filename);
}

std::unique_ptr<sup::xml::TreeData> ComposerTreeFromString(const std::string& representation)
{
  return sup::xml::TreeDataFromString(representation);
}

void ExecuteComposerTree(const sup::xml::TreeData& tree)
{
  (void)tree;
}

namespace utils
{
void LoadLibrary(const std::string& library_name)
{
  if (library_name.empty())
  {
    std::string error_message =
      "sup::di::utils::LoadLibrary(): trying to load library with empty name";
    throw InvalidOperationException(error_message);
  }
  auto handle = dlopen(library_name.c_str(), RTLD_NOW);
  if (handle == nullptr)
  {
    std::string error_message =
    "sup::di::utils::LoadLibrary(): could not load library with name [" + library_name + "]";
    throw RuntimeException(error_message);
  }
}

void CreateStringInstance(const sup::xml::TreeData& instance_tree)
{
  (void)instance_tree;
}

void CreateInstance(const sup::xml::TreeData& instance_tree)
{
  (void)instance_tree;
}

void CallFunction(const sup::xml::TreeData& function_tree)
{
  (void)function_tree;
}

}  // namespace utils

}  // namespace di

}  // namespace sup
