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
#include "TestConfig.h"

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
static const std::string PrinterAggregatorName = "PrinterAggregator";

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
const std::string PrinterDecoratorInstanceName = "PrinterDecoratorInstance";
const std::string PrinterAggregatorInstanceName = "PrinterAggregatorInstance";

TEST_F(ObjectManagerExternalTest, CreateInstances)
{
  EXPECT_TRUE(library_loaded);
  EXPECT_NO_THROW(global_object_manager.CreateInstance(HelloPrinterName, HelloPrinterInstanceName, {}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(
    PrinterDecoratorName, PrinterDecoratorInstanceName, {HelloPrinterInstanceName}));
  EXPECT_NO_THROW(global_object_manager.CreateInstance(
    PrinterAggregatorName, PrinterAggregatorInstanceName,
    {HelloPrinterInstanceName, PrinterDecoratorInstanceName}));
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
