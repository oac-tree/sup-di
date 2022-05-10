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

#include "ObjectManager.h"

#include <memory>
#include <string>

using namespace sup::di;

class ObjectManagerTest : public ::testing::Test
{
protected:
  ObjectManagerTest();
  virtual ~ObjectManagerTest();

  ObjectManager object_manager;
};

class IPrinter
{
public:
  virtual ~IPrinter() = default;

  virtual std::string Print() = 0;
};

const std::string HelloWorld = "Hello, world!";

class HelloPrinter : public IPrinter
{
public:
  HelloPrinter() = default;
  ~HelloPrinter() = default;

  std::string Print() override
  {
    return HelloWorld;
  }
};

const std::string HelloPrinterName = "HelloPrinter";
const std::string HelloPrinterInstanceName = "HelloPrinterInstance";

std::unique_ptr<IPrinter> HelloPrinterFactoryFunction()
{
  return std::unique_ptr<IPrinter>(new HelloPrinter());
}

TEST_F(ObjectManagerTest, NoDependencies)
{
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    HelloPrinterName, HelloPrinterFactoryFunction));
  EXPECT_THROW(object_manager.GetInstance<IPrinter>(HelloPrinterInstanceName), std::runtime_error);
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service = object_manager.GetInstance<IPrinter>(HelloPrinterInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), HelloWorld);
}

ObjectManagerTest::ObjectManagerTest()
{}

ObjectManagerTest::~ObjectManagerTest() = default;
