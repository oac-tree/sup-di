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

#include "object_composer_element.h"

#include "constants.h"
#include "exceptions.h"
#include "function_element.h"
#include "instance_element.h"
#include "string_instance_element.h"

#include <sup/xml/tree_data_validate.h>

namespace sup
{
namespace di
{

ObjectComposerElement::ObjectComposerElement(const sup::xml::TreeData& composer_tree)
  : m_elements{}
{
  ValidateComposerTree(composer_tree);
  for (const auto& child : composer_tree.Children())
  {
    // add IComposerElement to m_elements
  }
}

ObjectComposerElement::~ObjectComposerElement() = default;

void ObjectComposerElement::Execute()
{}

void ValidateComposerTree(const sup::xml::TreeData& composer_tree)
{
  sup::xml::ValidateNoContent(composer_tree);
  sup::xml::ValidateAllowedChildTags(composer_tree,
    { constants::LOAD_LIBRARY_TAG, constants::CREATE_INSTANCE_TAG, constants::STRING_INSTANCE_TAG,
      constants::CALL_FUNCTION_TAG });
}

}  // namespace di

}  // namespace sup

