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

#include "sup/di/error_codes.h"

#include <gtest/gtest.h>

#include <set>

using namespace sup::di;

class ErrorCodesTest : public ::testing::Test
{
protected:
  ErrorCodesTest();
  virtual ~ErrorCodesTest();

};

TEST_F(ErrorCodesTest, StringNotEmpty)
{
  EXPECT_FALSE(ErrorString(ErrorCode::kSuccess).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kFactoryFunctionNotFound).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kGlobalFunctionNotFound).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kDependencyNotFound).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kWrongNumberOfDependencies).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kInvalidInstanceName).empty());
  EXPECT_FALSE(ErrorString(ErrorCode::kGlobalFunctionFailed).empty());
  EXPECT_FALSE(ErrorString(static_cast<ErrorCode>(2000)).empty());
}

TEST_F(ErrorCodesTest, StringsDifferent)
{
  std::set<std::string> error_strings;
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kSuccess)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kFactoryFunctionNotFound)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kGlobalFunctionNotFound)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kDependencyNotFound)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kWrongNumberOfDependencies)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kInvalidInstanceName)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(ErrorCode::kGlobalFunctionFailed)).second);
  EXPECT_TRUE(error_strings.insert(ErrorString(static_cast<ErrorCode>(2000))).second);
  EXPECT_FALSE(error_strings.insert(ErrorString(static_cast<ErrorCode>(2001))).second);
}

ErrorCodesTest::ErrorCodesTest() = default;

ErrorCodesTest::~ErrorCodesTest() = default;
