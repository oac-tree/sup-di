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

#include <sup/di-composer-core/composition_root.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string COMPOSITION_ROOT_XML =
R"RAW(<?xml version="1.0" encoding="UTF-8"?>
<ObjectComposer xmlns="http://codac.iter.org/sup/di" version="1.0"
           name="Test configuration file for the SUP dependency injection framework"
           xmlns:xs="http://www.w3.org/2001/XMLSchema-instance"
           xs:schemaLocation="http://codac.iter.org/sup/di sup-di.xsd">
    <StringInstance>
        <InstanceName>Test_Name</InstanceName>
        <Value>Non-empty value</Value>
    </StringInstance>
    <CallFunction>
        <FunctionName>test_check_string_not_null</FunctionName>
        <Dependency>Test_Name</Dependency>
    </CallFunction>
</ObjectComposer>
)RAW";

class CompositionRootTest : public ::testing::Test
{
protected:
  CompositionRootTest();
  virtual ~CompositionRootTest();
};

TEST_F(CompositionRootTest, FromString)
{
  EXPECT_NO_THROW(ExecuteObjectTreeFromString(COMPOSITION_ROOT_XML));
}

CompositionRootTest::CompositionRootTest() = default;

CompositionRootTest::~CompositionRootTest() = default;
