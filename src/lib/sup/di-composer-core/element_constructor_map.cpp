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

#include "element_constructor_map.h"

#include "constants.h"
#include "double_instance_element.h"
#include "function_element.h"
#include "instance_element.h"
#include "integer_instance_element.h"
#include "library_element.h"
#include "string_instance_element.h"
#include <memory>

namespace
{
template <typename Elem>
struct TElementConstructor
{
  static std::unique_ptr<sup::di::IComposerElement> Create(const sup::xml::TreeData& tree)
  {
    return std::make_unique<Elem>(tree);
  }
};
}  // unnamed namespace

namespace sup
{
namespace di
{

const std::map<std::string, ElementConstructor>& ElementConstructorMap()
{
  static const std::map<std::string, ElementConstructor> constr_map {
    { constants::CALL_FUNCTION_TAG, TElementConstructor<FunctionElement>::Create },
    { constants::CREATE_INSTANCE_TAG, TElementConstructor<InstanceElement>::Create },
    { constants::LOAD_LIBRARY_TAG, TElementConstructor<LibraryElement>::Create },
    { constants::STRING_INSTANCE_TAG, TElementConstructor<StringInstanceElement>::Create },
    { constants::INTEGER_INSTANCE_TAG, TElementConstructor<IntegerInstanceElement>::Create },
    { constants::DOUBLE_INSTANCE_TAG, TElementConstructor<DoubleInstanceElement>::Create }
  };
  return constr_map;
}

}  // namespace di

}  // namespace sup
