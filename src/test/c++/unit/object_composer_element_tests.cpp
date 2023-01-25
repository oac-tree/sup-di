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

#include "global_test_objects.h"

#include <sup/di-composer-core/constants.h>
#include <sup/di-composer-core/element_constructor_map.h>
#include <sup/di-composer-core/exceptions.h>
#include <sup/di-composer-core/object_composer_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string STRING_INSTANCE_NAME = "Test_StringInstanceName";
const std::string STRING_INSTANCE_VALUE = "Test_StringValue";

class ObjectComposerElementTest : public ::testing::Test
{
protected:
  ObjectComposerElementTest();
  virtual ~ObjectComposerElementTest();

  sup::xml::TreeData m_composer_tree;
};

sup::xml::TreeData CreateComposerTree(const std::string& str_dep_name);

TEST_F(ObjectComposerElementTest, Construction)
{
  EXPECT_NO_THROW(ObjectComposerElement composer_elem{m_composer_tree});
}

TEST_F(ObjectComposerElementTest, Validation)
{
  {
    sup::xml::TreeData composer_tree{constants::OBJECT_COMPOSER_TAG};
    EXPECT_NO_THROW(ValidateComposerTree(composer_tree));
    composer_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateComposerTree(composer_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData composer_tree{constants::OBJECT_COMPOSER_TAG};
    EXPECT_NO_THROW(ValidateComposerTree(composer_tree));
    sup::xml::TreeData name_tree{constants::INSTANCE_NAME_TAG};
    composer_tree.AddChild(name_tree);
    EXPECT_THROW(ValidateComposerTree(composer_tree), sup::xml::ValidationException);
  }
}

TEST_F(ObjectComposerElementTest, Execution)
{
  ObjectComposerElement inst_elem{m_composer_tree};
  EXPECT_NO_THROW(inst_elem.Execute());

  ObjectComposerElement inst_elem_fail{CreateComposerTree("this_dependency_does_not_exist")};
  EXPECT_THROW(inst_elem_fail.Execute(), RuntimeException);
}

TEST_F(ObjectComposerElementTest, CreateComposerElement)
{
  // CreateComposerElement only handles child nodes of a composer tree and throws otherwise.
  sup::xml::TreeData composer_tree{constants::OBJECT_COMPOSER_TAG};
  EXPECT_THROW(CreateComposerElement(composer_tree), ParseException);
}

ObjectComposerElementTest::ObjectComposerElementTest()
  : m_composer_tree{CreateComposerTree(STRING_INSTANCE_NAME)}
{}

ObjectComposerElementTest::~ObjectComposerElementTest() = default;

sup::xml::TreeData CreateComposerTree(const std::string& str_dep_name)
{
  sup::xml::TreeData composer_tree{constants::OBJECT_COMPOSER_TAG};
  composer_tree.AddAttribute("someAttribute", "does_not_matter");

  // String instance
  sup::xml::TreeData string_instance_tree{constants::STRING_INSTANCE_TAG};
  sup::xml::TreeData str_name_tree{constants::INSTANCE_NAME_TAG};
  str_name_tree.SetContent(STRING_INSTANCE_NAME);
  string_instance_tree.AddChild(str_name_tree);
  sup::xml::TreeData val_tree{constants::VALUE_TAG};
  val_tree.SetContent(STRING_INSTANCE_VALUE);
  string_instance_tree.AddChild(val_tree);
  composer_tree.AddChild(string_instance_tree);

  // Call function tree
  sup::xml::TreeData function_tree{constants::CALL_FUNCTION_TAG};
  sup::xml::TreeData func_name_tree{constants::FUNCTION_NAME_TAG};
  func_name_tree.SetContent(test::Test_CheckStringNotNull_Name);
  function_tree.AddChild(func_name_tree);
  sup::xml::TreeData dep_tree{constants::DEPENDENCY_TAG};
  dep_tree.SetContent(str_dep_name);
  function_tree.AddChild(dep_tree);
  composer_tree.AddChild(function_tree);

  return composer_tree;
}