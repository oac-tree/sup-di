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

TEST_F(ObjectManagerTest, Decorator)
{
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    HelloPrinterName, HelloPrinterFactoryFunction));
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    PrinterDecoratorName, PrinterDecoratorFactoryFunction));
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                                {HelloPrinterInstanceName}));
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
    object_manager.GetInstance<IPrinter>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, GenericFactoryFunction)
{
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    HelloPrinterName, GenericInstanceFactoryFunction<IPrinter, HelloPrinter>));
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    PrinterDecoratorName, GenericInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter>));
  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(PrinterDecoratorName, PrinterDecoratorInstanceName,
                                                {HelloPrinterInstanceName}));
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
    object_manager.GetInstance<IPrinter>(PrinterDecoratorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), DecoratedPrefix + HelloWorld);
}

TEST_F(ObjectManagerTest, ComplexObjectTree)
{
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    HelloPrinterName, GenericInstanceFactoryFunction<IPrinter, HelloPrinter>));
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(
    PrinterDecoratorName, GenericInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter>));
  EXPECT_NO_THROW(object_manager.RegisterFactoryFunction(PrinterAggregatorName,
    GenericInstanceFactoryFunction<IPrinter, PrinterAggregator, IPrinter, IPrinter>));

  EXPECT_NO_THROW(object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(object_manager.CreateInstance(
    PrinterDecoratorName, PrinterDecoratorInstanceName, {HelloPrinterInstanceName}));
  EXPECT_NO_THROW(object_manager.CreateInstance(
    PrinterAggregatorName, PrinterAggregatorInstanceName,
    {HelloPrinterInstanceName, PrinterDecoratorInstanceName}));
  IPrinter* print_service = nullptr;
  EXPECT_NO_THROW(print_service =
    object_manager.GetInstance<IPrinter>(PrinterAggregatorInstanceName));
  EXPECT_NE(print_service, nullptr);
  EXPECT_EQ(print_service->Print(), HelloWorld + DecoratedPrefix + HelloWorld);
}

ObjectManagerTest::ObjectManagerTest()
{}

ObjectManagerTest::~ObjectManagerTest() = default;
