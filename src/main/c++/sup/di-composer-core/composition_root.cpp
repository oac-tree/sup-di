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

#include "composition_root.h"

#include "object_composer_element.h"

#include <sup/xml/tree_data_parser.h>

namespace
{
void ExecuteComposerTree(const sup::xml::TreeData& composer_tree);
}  // unnamed namespace

namespace sup
{
namespace di
{

void ExecuteObjectTreeFromFile(const std::string& filename)
{
  auto composer_tree = sup::xml::TreeDataFromFile(filename);
  ExecuteComposerTree(*composer_tree);
}

void ExecuteObjectTreeFromString(const std::string& representation)
{
  auto composer_tree = sup::xml::TreeDataFromString(representation);
  ExecuteComposerTree(*composer_tree);
}

}  // namespace di

}  // namespace sup

namespace
{
void ExecuteComposerTree(const sup::xml::TreeData& composer_tree)
{
  sup::di::ObjectComposerElement object_composer{composer_tree};
  object_composer.Execute();
}
}  // unnamed namespace
