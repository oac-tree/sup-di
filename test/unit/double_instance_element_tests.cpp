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
 * Copyright (c) : 2010-2025 ITER Organization,
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
#include <sup/di-composer-core/double_instance_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string DOUBLE_INSTANCE_NAME = "Test_DoubleInstance_Name";
const std::string DOUBLE_INSTANCE_VALUE = "3.14e-7";

class DoubleInstanceElementTest : public ::testing::Test
{
protected:
  DoubleInstanceElementTest();
  virtual ~DoubleInstanceElementTest();

  sup::xml::TreeData m_double_instance_tree;
};

sup::xml::TreeData CreateDoubleInstanceTree(const std::string& name, const std::string& value);

TEST_F(DoubleInstanceElementTest, Construction)
{
  EXPECT_NO_THROW(DoubleInstanceElement inst_elem{m_double_instance_tree});
  auto constr_it = ElementConstructorMap().find(constants::DOUBLE_INSTANCE_TAG);
  EXPECT_NO_THROW(constr_it->second(m_double_instance_tree));
}

TEST_F(DoubleInstanceElementTest, Validation)
{
  {
    sup::xml::TreeData integer_instance_tree{constants::DOUBLE_INSTANCE_TAG};
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData integer_instance_tree{constants::DOUBLE_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("int_name");
    integer_instance_tree.AddChild(name_tree);
    sup::xml::TreeData val_tree{constants::VALUE_TAG};
    val_tree.SetContent("-1.7e3");
    integer_instance_tree.AddChild(val_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(integer_instance_tree));
    integer_instance_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData integer_instance_tree{constants::DOUBLE_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("int_name");
    integer_instance_tree.AddChild(name_tree);
    sup::xml::TreeData val_tree{constants::VALUE_TAG};
    val_tree.SetContent("12e14");
    integer_instance_tree.AddChild(val_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(integer_instance_tree));
    integer_instance_tree.AddAttribute("name", "not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
}

TEST_F(DoubleInstanceElementTest, Execution)
{
  DoubleInstanceElement inst_elem{m_double_instance_tree};
  EXPECT_NO_THROW(inst_elem.Execute());

  DoubleInstanceElement inst_elem_fail{
    CreateDoubleInstanceTree(DOUBLE_INSTANCE_NAME, "-3.14")};
  EXPECT_THROW(inst_elem_fail.Execute(), RuntimeException);
}

DoubleInstanceElementTest::DoubleInstanceElementTest()
  : m_double_instance_tree{CreateDoubleInstanceTree(DOUBLE_INSTANCE_NAME, DOUBLE_INSTANCE_VALUE)}
{}

DoubleInstanceElementTest::~DoubleInstanceElementTest() = default;

sup::xml::TreeData CreateDoubleInstanceTree(const std::string& name, const std::string& value)
{
  sup::xml::TreeData integer_instance_tree{constants::DOUBLE_INSTANCE_TAG};
  sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
  name_tree.SetContent(name);
  integer_instance_tree.AddChild(name_tree);
  sup::xml::TreeData val_tree{constants::VALUE_TAG};
  val_tree.SetContent(value);
  integer_instance_tree.AddChild(val_tree);
  return integer_instance_tree;
}