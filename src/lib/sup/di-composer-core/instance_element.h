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

#ifndef SUP_DI_COMPOSER_INSTANCE_ELEMENT_H_
#define SUP_DI_COMPOSER_INSTANCE_ELEMENT_H_

#include "i_composer_element.h"

#include <sup/xml/tree_data.h>

#include <vector>

namespace sup
{
namespace di
{

class InstanceElement : public IComposerElement
{
public:
  InstanceElement(const sup::xml::TreeData& instance_tree);
  ~InstanceElement();

  void Execute() override;

private:
  std::string m_type_name;
  std::string m_instance_name;
  std::vector<std::string> m_dependencies;
};

void ValidateInstanceTree(const sup::xml::TreeData& instance_tree);

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_INSTANCE_ELEMENT_H_
