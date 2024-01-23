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

#include "global_test_objects.h"

namespace sup
{
namespace di
{
namespace test
{

Test_StringWrapper::Test_StringWrapper(const std::string& str)
  : m_str{str}
{}

Test_StringWrapper::~Test_StringWrapper() = default;

std::string Test_StringWrapper::GetString() const
{
  return m_str;
}

bool Test_CheckStringNotNull(const std::string& str)
{
  if (str.size() == 0)
  {
    return false;
  }
  return true;
}

bool Test_CompareWrapperWithString(const Test_StringWrapper& wrapper, const std::string& str)
{
  return wrapper.GetString() == str;
}

bool Test_Literals(const std::string& str, int i, double d)
{
  return str.size() > 0 && i > 0 && d > 0;
}


}  // namespace test

}  // namespace di

}  // namespace sup
