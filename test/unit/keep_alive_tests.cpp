/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition and implementation for dependency injection templates in SUP.
 *
 * Author        : Ricardo Torres (Ext)
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

#include "global_test_objects.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sup/di-services/registered_names.h>
#include <sup/di-services/keep_alive.h>
#include <thread>
#include <csignal>

using namespace sup::di::services;

TEST(KeepAliveTest, OneSecond)
{
  std::thread t(KeepAliveFor, 1u);

  EXPECT_TRUE(t.joinable());
  t.join();

  EXPECT_FALSE(t.joinable());
}

TEST(KeepAliveTest, ZeroSeconds)
{
  std::thread t(KeepAliveFor, 0u);

  EXPECT_TRUE(t.joinable());
  t.join();

  EXPECT_FALSE(t.joinable());
}
