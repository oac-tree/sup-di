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
#include <gmock/gmock.h>

#include <sup/di-services/registered_names.h>
#include <sup/di-services/keep_alive.h>
#include <thread>
#include <csignal>

using namespace sup::di::services;

TEST(KeepAliveTest, InterruptHandlerTest)
{
  testing::internal::CaptureStdout();
  int signal = SIGINT;

  interruptHandler(signal);

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("Terminating the execution with signal: " + std::to_string(signal)));
}

TEST(KeepAliveTest, KeepAliveThreadTermination)
{
  std::thread t(KeepAlive);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  EXPECT_TRUE(t.joinable());
  std::raise(SIGINT);
  t.join();

  EXPECT_FALSE(t.joinable());
}

