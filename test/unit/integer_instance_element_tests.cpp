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
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "global_test_objects.h"

#include <sup/di-composer-core/constants.h>
#include <sup/di-composer-core/element_constructor_map.h>
#include <sup/di-composer-core/exceptions.h>
#include <sup/di-composer-core/integer_instance_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string INTEGER_INSTANCE_NAME = "Test_IntegerInstance_Name";
const std::string INTEGER_INSTANCE_VALUE = "337";

class IntegerInstanceElementTest : public ::testing::Test
{
protected:
  IntegerInstanceElementTest();
  virtual ~IntegerInstanceElementTest();

  sup::xml::TreeData m_integer_instance_tree;
};

sup::xml::TreeData CreateIntegerInstanceTree(const std::string& name, const std::string& value);

TEST_F(IntegerInstanceElementTest, Construction)
{
  EXPECT_NO_THROW(IntegerInstanceElement inst_elem{m_integer_instance_tree});
  auto constr_it = ElementConstructorMap().find(constants::INTEGER_INSTANCE_TAG);
  EXPECT_NO_THROW(constr_it->second(m_integer_instance_tree));
}

TEST_F(IntegerInstanceElementTest, Validation)
{
  {
    sup::xml::TreeData integer_instance_tree{constants::INTEGER_INSTANCE_TAG};
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData integer_instance_tree{constants::INTEGER_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("int_name");
    integer_instance_tree.AddChild(name_tree);
    sup::xml::TreeData val_tree{constants::VALUE_TAG};
    val_tree.SetContent("-17");
    integer_instance_tree.AddChild(val_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(integer_instance_tree));
    integer_instance_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData integer_instance_tree{constants::INTEGER_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("int_name");
    integer_instance_tree.AddChild(name_tree);
    sup::xml::TreeData val_tree{constants::VALUE_TAG};
    val_tree.SetContent("1260");
    integer_instance_tree.AddChild(val_tree);
    EXPECT_NO_THROW(ValidateLiteralInstanceTree(integer_instance_tree));
    integer_instance_tree.AddAttribute("name", "not_allowed");
    EXPECT_THROW(ValidateLiteralInstanceTree(integer_instance_tree), sup::xml::ValidationException);
  }
}

TEST_F(IntegerInstanceElementTest, Execution)
{
  IntegerInstanceElement inst_elem{m_integer_instance_tree};
  EXPECT_NO_THROW(inst_elem.Execute());

  IntegerInstanceElement inst_elem_fail{
    CreateIntegerInstanceTree(INTEGER_INSTANCE_NAME, "33")};
  EXPECT_THROW(inst_elem_fail.Execute(), RuntimeException);
}

IntegerInstanceElementTest::IntegerInstanceElementTest()
  : m_integer_instance_tree{CreateIntegerInstanceTree(INTEGER_INSTANCE_NAME, INTEGER_INSTANCE_VALUE)}
{}

IntegerInstanceElementTest::~IntegerInstanceElementTest() = default;

sup::xml::TreeData CreateIntegerInstanceTree(const std::string& name, const std::string& value)
{
  sup::xml::TreeData integer_instance_tree{constants::INTEGER_INSTANCE_TAG};
  sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
  name_tree.SetContent(name);
  integer_instance_tree.AddChild(name_tree);
  sup::xml::TreeData val_tree{constants::VALUE_TAG};
  val_tree.SetContent(value);
  integer_instance_tree.AddChild(val_tree);
  return integer_instance_tree;
}