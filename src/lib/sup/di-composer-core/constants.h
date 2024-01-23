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

#ifndef SUP_DI_COMPOSER_CONSTANTS_H_
#define SUP_DI_COMPOSER_CONSTANTS_H_

#include <string>

namespace sup
{
namespace di
{
namespace constants
{

// XML tags
const std::string OBJECT_COMPOSER_TAG = "ObjectComposer";
const std::string LOAD_LIBRARY_TAG = "LoadLibrary";

const std::string CREATE_INSTANCE_TAG = "Instance";
const std::string TYPE_NAME_TAG = "TypeName";
const std::string INSTANCE_NAME_TAG = "InstanceName";
const std::string DEPENDENCY_TAG = "Dependency";

const std::string STRING_INSTANCE_TAG = "StringInstance";
const std::string INTEGER_INSTANCE_TAG = "IntegerInstance";
const std::string VALUE_TAG = "Value";

const std::string CALL_FUNCTION_TAG = "CallFunction";
const std::string FUNCTION_NAME_TAG = "FunctionName";

}  // namespace constants

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_CONSTANTS_H_
