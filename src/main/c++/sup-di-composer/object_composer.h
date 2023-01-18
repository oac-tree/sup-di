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

#ifndef SUP_DI_COMPOSER_OBJECT_COMPOSER_H_
#define SUP_DI_COMPOSER_OBJECT_COMPOSER_H_

#include <sup/xml/tree_data.h>

namespace sup
{
namespace di
{
namespace utils
{

void ValidateLoadLibraryTree(const sup::xml::TreeData& load_library_tree);

void ValidateComposerTree(const sup::xml::TreeData& composer_tree);

void ExecuteComposerTree(const sup::xml::TreeData& composer_tree);

}  // namespace utils

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_OBJECT_COMPOSER_H_
