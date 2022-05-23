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

#include "sup/di/ObjectManager.h"
#include "TestServices.h"

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

const std::string HelloPrinterInstanceName = "HelloPrinterInstance";
const std::string PrinterDecoratorInstanceName = "PrinterDecoratorInstance";
const std::string PrinterAggregatorInstanceName = "PrinterAggregatorInstance";
const std::string IntInstanceName = "IntInstance";

const std::string HelloTestName = "HelloTest";
const std::string DecoratorHelloTestName = "DecoratorHelloTest";
const std::string AggregatorPrinterTestName = "AggregatorPrinterTest";

TEST_F(ObjectManagerTest, NoDependencies)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, HelloPrinterFactoryFunction));

  // Global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));

  // Create instances
  EXPECT_THROW(object_manager.GetInstance<IPrinter*>(HelloPrinterInstanceName),
               std::runtime_error);
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));

  // Call global functions
  EXPECT_TRUE(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}));
  EXPECT_THROW(object_manager.CallGlobalFunction(HelloTestName, {}), std::runtime_error);

  // Access instances of known type
  IPrinter*print_service = nullptr;
  EXPECT_NO_THROW(print_service = object_manager.GetInstance<IPrinter*>(HelloPrinterInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), HelloWorld);
}

TEST_F(ObjectManagerTest, Decorator)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, HelloPrinterFactoryFunction));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      PrinterDecoratorName, PrinterDecoratorFactoryFunction));

  // Global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(DecoratorHelloTestName,
                                                    TestDecoratedHelloPrinter));

  // Create instances
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                                {HelloPrinterInstanceName}));

  // Call global functions
  EXPECT_TRUE(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}));
  EXPECT_TRUE(object_manager.CallGlobalFunction(DecoratorHelloTestName,
                                                {PrinterDecoratorInstanceName}));

  // Access instances of known type
  IPrinter*print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, GenericFactoryFunction)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, GenericInstanceFactoryFunction<IPrinter, HelloPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      PrinterDecoratorName, GenericInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter>));

  // Create instances
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                                {HelloPrinterInstanceName}));

  // Access instances of known type
  IPrinter*print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, ComplexObjectTree)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, GenericInstanceFactoryFunction<IPrinter, HelloPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      PrinterDecoratorName, GenericInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
                PrinterAggregatorName,
                GenericInstanceFactoryFunction<IPrinter, PrinterAggregator, IPrinter, IPrinter>));

  // Global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(DecoratorHelloTestName,
                                                    TestDecoratedHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(AggregatorPrinterTestName,
                                                    TestAggregatedPrinter));

  // Create instances
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(
      PrinterDecoratorName, PrinterDecoratorInstanceName, {HelloPrinterInstanceName}));
  EXPECT_NO_THROW(object_manager.CreateInstance(
      PrinterAggregatorName, PrinterAggregatorInstanceName,
      {HelloPrinterInstanceName, PrinterDecoratorInstanceName}));

  // Call global functions
  EXPECT_TRUE(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}));
  EXPECT_TRUE(object_manager.CallGlobalFunction(DecoratorHelloTestName,
                                                {PrinterDecoratorInstanceName}));
  EXPECT_TRUE(object_manager.CallGlobalFunction(AggregatorPrinterTestName,
                                                {PrinterAggregatorInstanceName}));

  // Access instances of known type
  IPrinter*print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                      object_manager.GetInstance<IPrinter*>(PrinterAggregatorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), HelloWorld + DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, Exceptions)
{
  // Duplicate name for factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, HelloPrinterFactoryFunction));
  EXPECT_THROW(object_manager.RegisterFactoryFunction(
                   HelloPrinterName, PrinterDecoratorFactoryFunction),
               std::runtime_error);
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      PrinterDecoratorName, PrinterDecoratorFactoryFunction));

  // Duplicate name for instance creation
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_THROW(object_manager.CreateInstance(PrinterDecoratorName, HelloPrinterInstanceName,
                                             {HelloPrinterInstanceName}),
               std::runtime_error);
  EXPECT_NO_THROW(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                                {HelloPrinterInstanceName}));

  // Retrieve unknown instance
  IPrinter*print_service = nullptr;
  EXPECT_NO_THROW(print_service = object_manager.GetInstance<IPrinter*>(HelloPrinterInstanceName));
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_THROW(print_service = object_manager.GetInstance<IPrinter*>(PrinterAggregatorInstanceName),
               std::runtime_error);

  // Create unknown instance
  EXPECT_THROW(object_manager.CreateInstance(PrinterAggregatorName, PrinterAggregatorInstanceName,
                {HelloPrinterInstanceName, PrinterDecoratorInstanceName}),
               std::runtime_error);

  // Duplicate name for global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_THROW(object_manager.RegisterGlobalFunction(HelloTestName, TestDecoratedHelloPrinter),
               std::runtime_error);

  // Call unknown global function
  EXPECT_THROW(object_manager.CallGlobalFunction(DecoratorHelloTestName, {}), std::runtime_error);

  // Call global function with wrong list of parameters
  EXPECT_THROW(object_manager.CallGlobalFunction(HelloTestName, {}), std::runtime_error);

  // Call global function with wrong type of parameters
  EXPECT_TRUE(object_manager.RegisterInstance(std::unique_ptr<int>{new int{1}}, IntInstanceName));
  EXPECT_THROW(object_manager.CallGlobalFunction(HelloTestName, {IntInstanceName}),
               std::runtime_error);
}

ObjectManagerTest::ObjectManagerTest()
{
}

ObjectManagerTest::~ObjectManagerTest() = default;
