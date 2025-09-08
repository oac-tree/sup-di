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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <sup/di/instance_container.h>

#include <gtest/gtest.h>

using namespace sup::di;

class InstanceContainerTest : public ::testing::Test
{
protected:
  InstanceContainerTest();
  virtual ~InstanceContainerTest();
};

TEST_F(InstanceContainerTest, WrapIntoContainer)
{
  auto up_int = std::make_unique<int>(42);
  auto container = internal::WrapIntoContainer(std::move(up_int));
  auto content = std::unique_ptr<int>{static_cast<int*>(container->Get())};
  EXPECT_NE(content.get(), nullptr);
  EXPECT_EQ(container->Release(), content.get());
  EXPECT_EQ(container->Get(), nullptr);
}

InstanceContainerTest::InstanceContainerTest() {}

InstanceContainerTest::~InstanceContainerTest() = default;
