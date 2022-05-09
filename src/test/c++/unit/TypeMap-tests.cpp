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
#include <string>

#include "TypeMap.h"

using namespace sup::di::internal;

class TypeMapTest : public ::testing::Test
{
protected:
  TypeMapTest();
  virtual ~TypeMapTest();

  TypeMap<std::string> type_map;
};

TEST_F(TypeMapTest, TypeId)
{
  auto int_id = type_map.TypeId<int>();
  auto string_id = type_map.TypeId<std::string>();
  EXPECT_EQ(int_id, type_map.TypeId<int>());
  EXPECT_EQ(string_id, type_map.TypeId<std::string>());
  type_map.put<int>("integer");
  type_map.put<std::string>("string");
  EXPECT_EQ(int_id, type_map.TypeId<int>());
  EXPECT_EQ(string_id, type_map.TypeId<std::string>());
  auto it = type_map.find<int>();
  EXPECT_NE(it, type_map.end());
  EXPECT_EQ(it->second, "integer");
  it = type_map.find<std::string>();
  EXPECT_NE(it, type_map.end());
  EXPECT_EQ(it->second, "string");
}

TypeMapTest::TypeMapTest() = default;

TypeMapTest::~TypeMapTest() = default;
