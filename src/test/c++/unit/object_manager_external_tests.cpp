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

#include "sup/di/object_manager.h"

#include <test_config.h>

#include <gtest/gtest.h>

#include <dlfcn.h>

#include <string>
#include <iostream>

namespace
{
bool LoadLibrary(const std::string& libname);
}  // unnamed namespace

using namespace sup::di;

static const std::string HelloPrinterName = "HelloPrinter";
static const std::string PrinterDecoratorName = "PrinterDecorator";
static const std::string PrinterOwnerName = "PrinterOwner";
static const std::string PrinterAggregatorName = "PrinterAggregator";

static const std::string HelloTestName = "HelloTest";
static const std::string DecoratedHelloTestName = "DecoratoredHelloTest";
static const std::string OwnedPrinterTestName = "OwnedPrinterTest";
static const std::string AggregatedPrinterTestName = "AggregatedPrinterTest";
static const std::string DiscardPrinterName = "DiscardPrinter";

class ObjectManagerExternalTest : public ::testing::Test
{
protected:
  ObjectManagerExternalTest();
  virtual ~ObjectManagerExternalTest();

  static void SetUpTestCase();
  static void TearDownTestCase();

  ObjectManager& global_object_manager;
  static bool library_loaded;
};

bool ObjectManagerExternalTest::library_loaded = false;

const std::string HelloPrinterInstanceName = "HelloPrinterInstance";
const std::string HelloPrinterInstanceName2 = "HelloPrinterInstance2";
const std::string PrinterDecoratorInstanceName = "PrinterDecoratorInstance";
const std::string PrinterDecoratorInstanceName2 = "PrinterDecoratorInstance2";
const std::string PrinterOwnerInstanceName = "PrinterOwnerInstance";
const std::string PrinterAggregatorInstanceName = "PrinterAggregatorInstance";

TEST_F(ObjectManagerExternalTest, CreateInstances)
{
  // Load external library at runtime
  EXPECT_TRUE(library_loaded);

  // Create instances of externally registered types
  EXPECT_NO_THROW(global_object_manager.CreateInstance(HelloPrinterName,
                                                       HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(HelloPrinterName,
                                                       HelloPrinterInstanceName2, {}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(
    PrinterDecoratorName, PrinterDecoratorInstanceName, {HelloPrinterInstanceName}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(
    PrinterOwnerName, PrinterOwnerInstanceName, {HelloPrinterInstanceName2}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(
    PrinterAggregatorName, PrinterAggregatorInstanceName,
    {HelloPrinterInstanceName, PrinterDecoratorInstanceName}));
  // Second instance of HelloPrinter is no longer in the registry
  EXPECT_THROW(global_object_manager.CreateInstance(
    PrinterDecoratorName, PrinterDecoratorInstanceName2, {HelloPrinterInstanceName2}),
    std::runtime_error);

  // Call global functions
  EXPECT_TRUE(global_object_manager.CallGlobalFunction(HelloTestName, {HelloPrinterInstanceName}));
  EXPECT_TRUE(global_object_manager.CallGlobalFunction(DecoratedHelloTestName,
                                                       {PrinterDecoratorInstanceName}));
  EXPECT_TRUE(global_object_manager.CallGlobalFunction(OwnedPrinterTestName,
                                                       {PrinterOwnerInstanceName}));
  EXPECT_TRUE(global_object_manager.CallGlobalFunction(AggregatedPrinterTestName,
                                                       {PrinterAggregatorInstanceName}));

  // Discard instance through global function
  EXPECT_TRUE(global_object_manager.CallGlobalFunction(DiscardPrinterName,
                                                       {PrinterOwnerInstanceName}));
  EXPECT_THROW(global_object_manager.CreateInstance(
    PrinterDecoratorName, PrinterDecoratorInstanceName2, {PrinterOwnerInstanceName}),
    std::runtime_error);
}

ObjectManagerExternalTest::ObjectManagerExternalTest()
  : global_object_manager{GlobalObjectManager()}
{}

ObjectManagerExternalTest::~ObjectManagerExternalTest() = default;

void ObjectManagerExternalTest::SetUpTestCase()
{
  std::string library_name = testconfig::CMakeLibraryInstallDir() + "/libsup-di-testservices.so";
  library_loaded = LoadLibrary(library_name);
}

void ObjectManagerExternalTest::TearDownTestCase()
{}

namespace
{
bool LoadLibrary(const std::string& libname)
{
  void* lib_handle = dlopen(libname.c_str(), RTLD_NOW);
  return lib_handle != nullptr;
}
}  // unnamed namespace
