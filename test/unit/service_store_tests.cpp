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

#include <sup/di/service_store.h>

#include <gtest/gtest.h>

#include <string>

using namespace sup::di::internal;

using StringServiceStore = ServiceStore<std::string>;

class ServiceStoreTest : public ::testing::Test
{
protected:
  ServiceStoreTest() = default;
  ~ServiceStoreTest() = default;
};

class TestServiceA
{};

class TestServiceB
{};

bool UseTestServices(TestServiceA&, std::unique_ptr<TestServiceB>)
{
  return true;
}

class TestClient
{
public:
  TestClient(TestServiceA&, std::unique_ptr<TestServiceB>) {}
};

TEST_F(ServiceStoreTest, StoreRetrieve)
{
  StringServiceStore store;
  // Store two services
  EXPECT_TRUE(store.StoreInstance(std::make_unique<TestServiceA>(), "A"));
  EXPECT_TRUE(store.StoreInstance(std::make_unique<TestServiceB>(), "B"));

  // Invoke function with those services
  EXPECT_TRUE((InvokeWithStoreArgs<TestServiceA&, std::unique_ptr<TestServiceB>>(
    UseTestServices, store, {"A", "B"})));

  // Verify service A is still in the store, while B was removed because of transfer of ownership
  EXPECT_NO_THROW(store.GetInstance<TestServiceA*>("A"));
  EXPECT_THROW(store.GetInstance<TestServiceB*>("B"), std::runtime_error);
}
