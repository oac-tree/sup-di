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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <gtest/gtest.h>

#include "TypeStringList.h"

#include <type_traits>

using namespace sup::di::internal;

class TypeStringListTest : public ::testing::Test
{
protected:
  TypeStringListTest();
  virtual ~TypeStringListTest();

  TypeStringList<int, std::string> type_string_list;
};

TEST_F(TypeStringListTest, MemberFunctions)
{
  EXPECT_EQ(type_string_list.IndexedString(0), "int");
  EXPECT_EQ(type_string_list.IndexedString(1), "std::string");
  EXPECT_TRUE((std::is_same<int, decltype(type_string_list)::IndexedType<0>>::value));
  EXPECT_TRUE((std::is_same<std::string, decltype(type_string_list)::IndexedType<1>>::value));
}

TypeStringListTest::TypeStringListTest()
  : type_string_list({"int", "std::string"})
{}

TypeStringListTest::~TypeStringListTest() = default;
