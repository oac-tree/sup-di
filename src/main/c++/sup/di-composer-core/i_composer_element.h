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

#ifndef SUP_DI_COMPOSER_I_COMPOSER_ELEMENT_H_
#define SUP_DI_COMPOSER_I_COMPOSER_ELEMENT_H_

#include <sup/xml/tree_data.h>

#include <memory>

namespace sup
{
namespace di
{

class IComposerElement
{
public:
  virtual ~IComposerElement();

  virtual void Execute() = 0;
};

std::unique_ptr<IComposerElement> CreateComposerElement(const sup::xml::TreeData& tree);

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_I_COMPOSER_ELEMENT_H_
