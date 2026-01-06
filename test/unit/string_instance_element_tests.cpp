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

#include "global_test_objects.h"

#include <sup/di-composer-core/constants.h>
#include <sup/di-composer-core/element_constructor_map.h>
#include <sup/di-composer-core/exceptions.h>
#include <sup/di-composer-core/string_instance_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string STRING_INSTANCE_NAME = "Test_StringInstance_Name";
const std::string STRING_INSTANCE_VALUE = "Test_StringInstance_Value";

class StringInstanceElementTest : public ::testing::Test
{
protected:
  StringInstanceElementTest();
  virtual ~StringInstanceElementTest();

  sup::xml::TreeData m_string_instance_tree;
};

sup::xml::TreeData CreateStringInstanceTree(const std::string& name, const std::string& value);

TEST_F(StringInstanceElementTest, Construction)
{
  EXPECT_NO_THROW(StringInstanceElement inst_elem{m_string_instance_tree});
  auto constr_it = ElementConstructorMap().find(constants::STRING_INSTANCE_TAG);
  EXPECT_NO_THROW(constr_it->second(m_string_instance_tree));
}

TEST_F(StringInstanceElementTest, Validation)
{
  {
    sup::xml::TreeData string_instance_tree{constants::STRING_INSTANCE_TAG};
    EXPECT_THROW(ValidateLiteralInstanceTree(string_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData string_instance_tree{constants::STRING_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("func_name");
    string_instance_tree.AddChild(name_tree);
    sup::xml::TreeData type_tree{constants::VALUE_TAG};
    type_tree.SetContent("str_value");
    string_instance_tree.AddChild(type_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(string_instance_tree));
    string_instance_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(string_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData string_instance_tree{constants::STRING_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("func_name");
    string_instance_tree.AddChild(name_tree);
    sup::xml::TreeData type_tree{constants::VALUE_TAG};
    type_tree.SetContent("str_value");
    string_instance_tree.AddChild(type_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(string_instance_tree));
    string_instance_tree.AddAttribute("name", "not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(string_instance_tree), sup::xml::ValidationException);
  }
}

TEST_F(StringInstanceElementTest, Execution)
{
  StringInstanceElement inst_elem{m_string_instance_tree};
  EXPECT_NO_THROW(inst_elem.Execute());

  StringInstanceElement inst_elem_fail{
    CreateStringInstanceTree(STRING_INSTANCE_NAME, "this_name_was_already_registered")};
  EXPECT_THROW(inst_elem_fail.Execute(), RuntimeException);
}

StringInstanceElementTest::StringInstanceElementTest()
  : m_string_instance_tree{CreateStringInstanceTree(STRING_INSTANCE_NAME, STRING_INSTANCE_VALUE)}
{}

StringInstanceElementTest::~StringInstanceElementTest() = default;

sup::xml::TreeData CreateStringInstanceTree(const std::string& name, const std::string& value)
{
  sup::xml::TreeData string_instance_tree{constants::STRING_INSTANCE_TAG};
  sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
  name_tree.SetContent(name);
  string_instance_tree.AddChild(name_tree);
  sup::xml::TreeData val_tree{constants::VALUE_TAG};
  val_tree.SetContent(value);
  string_instance_tree.AddChild(val_tree);
  return string_instance_tree;
}