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

#ifndef SUP_DI_COMPOSER_INTEGER_INSTANCE_ELEMENT_H_
#define SUP_DI_COMPOSER_INTEGER_INSTANCE_ELEMENT_H_

#include "i_composer_element.h"

#include <sup/xml/tree_data.h>

namespace sup
{
namespace di
{

class IntegerInstanceElement : public IComposerElement
{
public:
  IntegerInstanceElement(const sup::xml::TreeData& string_instance_tree);
  ~IntegerInstanceElement();

  void Execute() override;

private:
  std::string m_instance_name;
  int m_value;
};

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_INTEGER_INSTANCE_ELEMENT_H_
