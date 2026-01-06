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

#include <sup/di-composer-core/exceptions.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string PARSE_ERROR_MESSAGE = "Parsing error!";
const std::string RUNTIME_ERROR_MESSAGE = "Runtime error!";

class ExceptionsTest : public ::testing::Test
{
protected:
  ExceptionsTest();
  virtual ~ExceptionsTest();
};

TEST_F(ExceptionsTest, ParseException)
{
  ParseException err{PARSE_ERROR_MESSAGE};
  std::string err_message = err.what();
  EXPECT_EQ(err_message, PARSE_ERROR_MESSAGE);
}

TEST_F(ExceptionsTest, RuntimeException)
{
  RuntimeException err{RUNTIME_ERROR_MESSAGE};
  std::string err_message = err.what();
  EXPECT_EQ(err_message, RUNTIME_ERROR_MESSAGE);
}

ExceptionsTest::ExceptionsTest() = default;

ExceptionsTest::~ExceptionsTest() = default;
