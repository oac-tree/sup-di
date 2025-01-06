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
#include <sup/di-composer-core/function_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

class FunctionElementTest : public ::testing::Test
{
protected:
  FunctionElementTest();
  virtual ~FunctionElementTest();

  sup::xml::TreeData m_function_tree;
};

sup::xml::TreeData CreateFunctionTree(const std::string& str_dep_name);

TEST_F(FunctionElementTest, Construction)
{
  EXPECT_NO_THROW(FunctionElement func_elem{m_function_tree});
  auto constr_it = ElementConstructorMap().find(constants::CALL_FUNCTION_TAG);
  EXPECT_NO_THROW(constr_it->second(m_function_tree));
}

TEST_F(FunctionElementTest, Validation)
{
  {
    sup::xml::TreeData function_tree{constants::CALL_FUNCTION_TAG};
    EXPECT_THROW(ValidateFunctionTree(function_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData function_tree{constants::CALL_FUNCTION_TAG};
    sup::xml::TreeData name_tree{constants::FUNCTION_NAME_TAG};
    name_tree.SetContent("func_name");
    function_tree.AddChild(name_tree);
    EXPECT_NO_THROW(ValidateFunctionTree(function_tree));
    function_tree.SetContent("not_allowed");
    EXPECT_THROW(ValidateFunctionTree(function_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData function_tree{constants::CALL_FUNCTION_TAG};
    sup::xml::TreeData name_tree{constants::FUNCTION_NAME_TAG};
    name_tree.SetContent("func_name");
    function_tree.AddChild(name_tree);
    EXPECT_NO_THROW(ValidateFunctionTree(function_tree));
    function_tree.AddAttribute("name", "not_allowed");
    EXPECT_THROW(ValidateFunctionTree(function_tree), sup::xml::ValidationException);
  }
}

TEST_F(FunctionElementTest, Execution)
{
  FunctionElement func_elem{m_function_tree};
  EXPECT_NO_THROW(func_elem.Execute());

  FunctionElement func_elem_fail{CreateFunctionTree("this_name_does_not_exist")};
  EXPECT_THROW(func_elem_fail.Execute(), RuntimeException);
}

FunctionElementTest::FunctionElementTest()
  : m_function_tree{CreateFunctionTree(test::Test_String_Name)}
{}

FunctionElementTest::~FunctionElementTest() = default;

sup::xml::TreeData CreateFunctionTree(const std::string& str_dep_name)
{
  sup::xml::TreeData function_tree{constants::CALL_FUNCTION_TAG};
  sup::xml::TreeData name_tree{constants::FUNCTION_NAME_TAG};
  name_tree.SetContent(test::Test_CheckStringNotNull_Name);
  function_tree.AddChild(name_tree);
  sup::xml::TreeData dep_tree{constants::DEPENDENCY_TAG};
  dep_tree.SetContent(str_dep_name);
  function_tree.AddChild(dep_tree);
  return function_tree;
}