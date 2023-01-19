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

#ifndef SUP_DI_COMPOSER_GLOBAL_FUNCTION_H_
#define SUP_DI_COMPOSER_GLOBAL_FUNCTION_H_

#include "i_composer_element.h"

#include <sup/xml/tree_data.h>

#include <vector>

namespace sup
{
namespace di
{

class FunctionElement : public IComposerElement
{
public:
  FunctionElement(const sup::xml::TreeData& function_tree);
  ~FunctionElement();

  void Execute() override;

private:
  std::string m_function_name;
  std::vector<std::string> m_dependencies;
};

void ValidateFunctionTree(const sup::xml::TreeData& function_tree);

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_GLOBAL_FUNCTION_H_
