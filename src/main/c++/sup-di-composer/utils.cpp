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

#include <sup/xml/tree_data_parser.h>

namespace sup
{
namespace di
{
namespace utils
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

}  // namespace utils

}  // namespace di

}  // namespace sup
