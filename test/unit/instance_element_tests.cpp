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
#include <sup/di-composer-core/instance_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string STRING_WRAPPER_INSTANCE_NAME = "Test_WrapperInstance";

class InstanceElementTest : public ::testing::Test
{
protected:
  InstanceElementTest();
  virtual ~InstanceElementTest();

  sup::xml::TreeData m_instance_tree;
};

sup::xml::TreeData CreateInstanceTree(const std::string& str_dep_name);

TEST_F(InstanceElementTest, Construction)
{
  EXPECT_NO_THROW(InstanceElement inst_elem{m_instance_tree});
  auto constr_it = ElementConstructorMap().find(constants::CREATE_INSTANCE_TAG);
  EXPECT_NO_THROW(constr_it->second(m_instance_tree));
}

TEST_F(InstanceElementTest, Validation)
{
  {
    sup::xml::TreeData instance_tree{constants::CREATE_INSTANCE_TAG};
    EXPECT_THROW(ValidateInstanceTree(instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData instance_tree{constants::CREATE_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("func_name");
    instance_tree.AddChild(name_tree);
    sup::xml::TreeData type_tree{constants::TYPE_NAME_TAG};
    type_tree.SetContent("type_name");
    instance_tree.AddChild(type_tree);
    EXPECT_NO_THROW(ValidateInstanceTree(instance_tree));
    instance_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateInstanceTree(instance_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData instance_tree{constants::CREATE_INSTANCE_TAG};
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    name_tree.SetContent("func_name");
    instance_tree.AddChild(name_tree);
    sup::xml::TreeData type_tree{constants::TYPE_NAME_TAG};
    type_tree.SetContent("type_name");
    instance_tree.AddChild(type_tree);
    EXPECT_NO_THROW(ValidateInstanceTree(instance_tree));
    instance_tree.AddAttribute("name", "not_allowed");
    EXPECT_THROW(ValidateInstanceTree(instance_tree), sup::xml::ValidationException);
  }
}

TEST_F(InstanceElementTest, Execution)
{
  InstanceElement inst_elem{m_instance_tree};
  EXPECT_NO_THROW(inst_elem.Execute());

  InstanceElement inst_elem_fail{CreateInstanceTree("this_name_does_not_exist")};
  EXPECT_THROW(inst_elem_fail.Execute(), RuntimeException);
}

InstanceElementTest::InstanceElementTest()
  : m_instance_tree{CreateInstanceTree(test::Test_String_Name)}
{}

InstanceElementTest::~InstanceElementTest() = default;

sup::xml::TreeData CreateInstanceTree(const std::string& str_dep_name)
{
  sup::xml::TreeData instance_tree{constants::CREATE_INSTANCE_TAG};
  sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
  name_tree.SetContent(STRING_WRAPPER_INSTANCE_NAME);
  instance_tree.AddChild(name_tree);
  sup::xml::TreeData type_tree{constants::TYPE_NAME_TAG};
  type_tree.SetContent(test::Test_StringWrapper_Name);
  instance_tree.AddChild(type_tree);
  sup::xml::TreeData dep_tree{constants::DEPENDENCY_TAG};
  dep_tree.SetContent(str_dep_name);
  instance_tree.AddChild(dep_tree);
  return instance_tree;
}