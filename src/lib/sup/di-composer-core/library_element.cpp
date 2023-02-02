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

#include "library_element.h"

#include "constants.h"
#include "exceptions.h"
#include "tree_extract.h"

#include <sup/xml/tree_data_validate.h>

#include <dlfcn.h>

namespace sup
{
namespace di
{

LibraryElement::LibraryElement(const sup::xml::TreeData& library_tree)
  : m_library_name{}
{
  ValidateLibraryTree(library_tree);
  utils::SetFromTreeNodeContent(m_library_name, library_tree);
}

LibraryElement::~LibraryElement() = default;

void LibraryElement::Execute()
{
  auto handle = dlopen(m_library_name.c_str(), RTLD_NOW);
  if (handle == nullptr)
  {
    std::string error_message =
    "LibraryElement::Execute(): could not load library with name [" + m_library_name + "]";
    throw RuntimeException(error_message);
  }
}

void ValidateLibraryTree(const sup::xml::TreeData& library_tree)
{
  sup::xml::ValidateNoAttributes(library_tree);
  sup::xml::ValidateNoChildren(library_tree);
}

}  // namespace di

}  // namespace sup
