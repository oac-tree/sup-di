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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#ifndef SUP_DI_GLOBAL_TEST_OBJECTS_H_
#define SUP_DI_GLOBAL_TEST_OBJECTS_H_

#include <string>

namespace sup
{
namespace di
{
namespace test
{

const std::string Test_StringWrapper_Name = "test_string_wrapper";
const std::string Test_CheckStringNotNull_Name = "test_check_string_not_null";
const std::string Test_CompareWrapperWithString_Name = "test_compare_wrapper_with_string";
const std::string Test_String_Name = "test_string";
const std::string Test_Literals_Name = "test_literals_positive";

class Test_StringWrapper
{
public:
  Test_StringWrapper(const std::string& str);
  ~Test_StringWrapper();

  std::string GetString() const;
private:
  std::string m_str;
};

bool Test_CheckStringNotNull(const std::string& str);

bool Test_CompareWrapperWithString(const Test_StringWrapper& wrapper, const std::string& str);

bool Test_Literals(const std::string& str, int i, double d);

}  // namespace test

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_GLOBAL_TEST_OBJECTS_H_
