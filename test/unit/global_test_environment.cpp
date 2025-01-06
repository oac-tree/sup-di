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
#include "global_test_objects.h"

#include <gtest/gtest.h>

#include <sup/di/object_manager.h>

using namespace sup::di;

const std::string TEST_STRING_VALUE = "Test_String_Value";

class ObjectManagerEnvironment : public ::testing::Environment
{
public:
  ObjectManagerEnvironment();
  ~ObjectManagerEnvironment();

  void SetUp() override;
  void TearDown() override;
};

::testing::Environment* const object_manager_environment =
  ::testing::AddGlobalTestEnvironment(new ObjectManagerEnvironment);

ObjectManagerEnvironment::ObjectManagerEnvironment() = default;

ObjectManagerEnvironment::~ObjectManagerEnvironment() = default;

void ObjectManagerEnvironment::SetUp()
{
  GlobalObjectManager().RegisterGlobalFunction(test::Test_CheckStringNotNull_Name,
                                               test::Test_CheckStringNotNull);
  GlobalObjectManager().RegisterInstance(TEST_STRING_VALUE, test::Test_String_Name);
  GlobalObjectManager().RegisterFactoryFunction(
    test::Test_StringWrapper_Name,
    ForwardingInstanceFactoryFunction<test::Test_StringWrapper, test::Test_StringWrapper,
      const std::string&>);
  GlobalObjectManager().RegisterGlobalFunction(test::Test_Literals_Name,
                                               test::Test_Literals);
}

void ObjectManagerEnvironment::TearDown()
{}
