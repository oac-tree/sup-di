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

#include "temporary_file.h"

#include <sup/di-composer-core/composition_root.h>
#include <sup/di-composer-core/exceptions.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string TEST_FILE_NAME = "test_composition_root.xml";

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

const std::string COMPOSITION_ROOT_XML_FILE =
R"RAW(<?xml version="1.0" encoding="UTF-8"?>
<ObjectComposer xmlns="http://codac.iter.org/sup/di" version="1.0"
           name="Test configuration file for the SUP dependency injection framework"
           xmlns:xs="http://www.w3.org/2001/XMLSchema-instance"
           xs:schemaLocation="http://codac.iter.org/sup/di sup-di.xsd">
    <StringInstance>
        <InstanceName>Test_Name2</InstanceName>
        <Value>Non-empty value</Value>
    </StringInstance>
    <CallFunction>
        <FunctionName>test_check_string_not_null</FunctionName>
        <Dependency>Test_Name2</Dependency>
    </CallFunction>
</ObjectComposer>
)RAW";

const std::string COMPOSITION_FROM_LITERALS_XML =
R"RAW(<?xml version="1.0" encoding="UTF-8"?>
<ObjectComposer xmlns="http://codac.iter.org/sup/di" version="1.0"
           name="Test configuration file for the SUP dependency injection framework"
           xmlns:xs="http://www.w3.org/2001/XMLSchema-instance"
           xs:schemaLocation="http://codac.iter.org/sup/di sup-di.xsd">
    <StringInstance>
        <InstanceName>str_name</InstanceName>
        <Value>Hello</Value>
    </StringInstance>
    <IntegerInstance>
        <InstanceName>int_name</InstanceName>
        <Value>42</Value>
    </IntegerInstance>
    <DoubleInstance>
        <InstanceName>double_name</InstanceName>
        <Value>3.14e6</Value>
    </DoubleInstance>
    <CallFunction>
        <FunctionName>test_literals_positive</FunctionName>
        <Dependency>str_name</Dependency>
        <Dependency>int_name</Dependency>
        <Dependency>double_name</Dependency>
    </CallFunction>
</ObjectComposer>
)RAW";

const std::string COMPOSITION_FROM_LITERALS_FAIL_XML =
R"RAW(<?xml version="1.0" encoding="UTF-8"?>
<ObjectComposer xmlns="http://codac.iter.org/sup/di" version="1.0"
           name="Test configuration file for the SUP dependency injection framework"
           xmlns:xs="http://www.w3.org/2001/XMLSchema-instance"
           xs:schemaLocation="http://codac.iter.org/sup/di sup-di.xsd">
    <StringInstance>
        <InstanceName>str_name</InstanceName>
        <Value>Hello</Value>
    </StringInstance>
    <IntegerInstance>
        <InstanceName>int_name</InstanceName>
        <Value>42</Value>
    </IntegerInstance>
    <DoubleInstance>
        <InstanceName>double_name</InstanceName>
        <Value>-3.14e6</Value>
    </DoubleInstance>
    <CallFunction>
        <FunctionName>test_literals_positive</FunctionName>
        <Dependency>str_name</Dependency>
        <Dependency>int_name</Dependency>
        <Dependency>double_name</Dependency>
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

TEST_F(CompositionRootTest, FromFile)
{
  test::TemporaryTestFile file(TEST_FILE_NAME, COMPOSITION_ROOT_XML_FILE);
  EXPECT_NO_THROW(ExecuteObjectTreeFromFile(TEST_FILE_NAME));
}

TEST_F(CompositionRootTest, Literals)
{
  EXPECT_NO_THROW(ExecuteObjectTreeFromString(COMPOSITION_FROM_LITERALS_XML));
  EXPECT_THROW(ExecuteObjectTreeFromString(COMPOSITION_FROM_LITERALS_FAIL_XML),
               sup::di::RuntimeException);
}

CompositionRootTest::CompositionRootTest() = default;

CompositionRootTest::~CompositionRootTest() = default;
