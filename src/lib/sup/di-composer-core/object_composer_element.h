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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DI_COMPOSER_OBJECT_COMPOSER_ELEMENT_H_
#define SUP_DI_COMPOSER_OBJECT_COMPOSER_ELEMENT_H_

#include "i_composer_element.h"

#include <sup/xml/tree_data.h>

#include <memory>
#include <vector>

namespace sup
{
namespace di
{

class ObjectComposerElement : public IComposerElement
{
public:
  ObjectComposerElement(const sup::xml::TreeData& composer_tree);
  ~ObjectComposerElement();

  void Execute() override;

private:
  std::vector<std::unique_ptr<IComposerElement>> m_elements;
};

void ValidateComposerTree(const sup::xml::TreeData& composer_tree);

std::unique_ptr<IComposerElement> CreateComposerElement(const sup::xml::TreeData& child_tree);

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_OBJECT_COMPOSER_ELEMENT_H_
