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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "sup/di/object_manager.h"

#include <test_services.h>

#include <gtest/gtest.h>

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
const std::string PrinterOwnerInstanceName = "PrinterOwnerInstance";
const std::string PrinterAggregatorInstanceName = "PrinterAggregatorInstance";
const std::string IntInstanceName = "IntInstance";

const std::string HelloTestName = "HelloTest";
const std::string DecoratorHelloTestName = "DecoratorHelloTest";
const std::string OwnedPrinterTestName = "OwnedPrinterTest";
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
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);

  // Call global functions
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {}),
    ErrorCode::kWrongNumberOfDependencies);

  // Access instances of known type
  IPrinter* print_service = nullptr;
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
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                          {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);

  // Call global functions
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {PrinterDecoratorInstanceName}),
    ErrorCode::kGlobalFunctionFailed);
  EXPECT_EQ(object_manager.CallGlobalFunction(DecoratorHelloTestName,
                                                {PrinterDecoratorInstanceName}),
    ErrorCode::kSuccess);

  // Access instances of known type
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, PassOwnership)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, HelloPrinterFactoryFunction));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      PrinterOwnerName, GenericInstanceFactoryFunction<IPrinter, PrinterOwner, IPrinter>));

  // Global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(OwnedPrinterTestName, TestOwnedPrinter));

  // Create instances
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(PrinterOwnerName, PrinterOwnerInstanceName,
                                          {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);

  // Call global functions
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}),
    ErrorCode::kDependencyNotFound);
  EXPECT_EQ(object_manager.CallGlobalFunction(OwnedPrinterTestName,
                                              {PrinterOwnerInstanceName}),
    ErrorCode::kSuccess);

  // Access instances of known type
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterOwnerInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), OwnedPrinterPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, GenericFactoryFunction)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, GenericInstanceFactoryFunctionShared<IPrinter, HelloPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(PrinterDecoratorName,
    GenericInstanceFactoryFunctionShared<IPrinter, PrinterDecorator, IPrinter>));

  // Create instances
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                          {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);

  // Access instances of known type
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, ComplexObjectTree)
{
  // Factory function registration
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
      HelloPrinterName, GenericInstanceFactoryFunctionShared<IPrinter, HelloPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(PrinterDecoratorName,
    GenericInstanceFactoryFunctionShared<IPrinter, PrinterDecorator, IPrinter>));
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(PrinterAggregatorName,
    GenericInstanceFactoryFunctionShared<IPrinter, PrinterAggregator, IPrinter, IPrinter>));

  // Global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(DecoratorHelloTestName,
                                                    TestDecoratedHelloPrinter));
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(AggregatorPrinterTestName,
                                                    TestAggregatedPrinter));

  // Create instances
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(
      PrinterDecoratorName, PrinterDecoratorInstanceName, {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(
      PrinterAggregatorName, PrinterAggregatorInstanceName,
      {HelloPrinterInstanceName, PrinterDecoratorInstanceName}),
    ErrorCode::kSuccess);

  // Call global functions
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CallGlobalFunction(DecoratorHelloTestName,
                                              {PrinterDecoratorInstanceName}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CallGlobalFunction(AggregatorPrinterTestName,
                                              {PrinterAggregatorInstanceName}),
    ErrorCode::kSuccess);

  // Access instances of known type
  IPrinter* print_service = nullptr;
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
                 HelloPrinterName, PrinterDecoratorFactoryFunction), std::runtime_error);
  EXPECT_TRUE(object_manager.RegisterFactoryFunction(
                PrinterDecoratorName, PrinterDecoratorFactoryFunction));

  // Duplicate name for instance creation
  EXPECT_EQ(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}),
    ErrorCode::kSuccess);
  EXPECT_EQ(object_manager.CreateInstance(PrinterDecoratorName, HelloPrinterInstanceName,
                                          {HelloPrinterInstanceName}),
    ErrorCode::kInvalidInstanceName);
  EXPECT_EQ(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                          {HelloPrinterInstanceName}),
    ErrorCode::kSuccess);

  // Retrieve unknown instance
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service = object_manager.GetInstance<IPrinter*>(HelloPrinterInstanceName));
  EXPECT_NO_THROW(print_service =
                    object_manager.GetInstance<IPrinter*>(PrinterDecoratorInstanceName));
  EXPECT_THROW(print_service = object_manager.GetInstance<IPrinter*>(PrinterAggregatorInstanceName),
               std::runtime_error);

  // Create unknown instance
  EXPECT_EQ(object_manager.CreateInstance(PrinterAggregatorName, PrinterAggregatorInstanceName,
                {HelloPrinterInstanceName, PrinterDecoratorInstanceName}),
    ErrorCode::kFactoryFunctionNotFound);

  // Duplicate name for global function registration
  EXPECT_TRUE(object_manager.RegisterGlobalFunction(HelloTestName, TestHelloPrinter));
  EXPECT_THROW(object_manager.RegisterGlobalFunction(HelloTestName, TestDecoratedHelloPrinter),
               std::runtime_error);

  // Call unknown global function
  EXPECT_EQ(object_manager.CallGlobalFunction(DecoratorHelloTestName, {}),
    ErrorCode::kGlobalFunctionNotFound);

  // Call global function with wrong list of parameters
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {}),
    ErrorCode::kWrongNumberOfDependencies);

  // Call global function with wrong type of parameters
  EXPECT_TRUE(object_manager.RegisterInstance(std::unique_ptr<int>{new int{1}}, IntInstanceName));
  EXPECT_EQ(object_manager.CallGlobalFunction(HelloTestName, {IntInstanceName}),
    ErrorCode::kDependencyNotFound);
}

ObjectManagerTest::ObjectManagerTest()
{
}

ObjectManagerTest::~ObjectManagerTest() = default;
