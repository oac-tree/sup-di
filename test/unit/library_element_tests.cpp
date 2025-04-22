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

#include "service_wrapper_config.h"

#include <sup/di-composer-core/constants.h>
#include <sup/di-composer-core/element_constructor_map.h>
#include <sup/di-composer-core/exceptions.h>
#include <sup/di-composer-core/library_element.h>

#include <sup/di/object_manager.h>

#include <sup/xml/exceptions.h>
#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

class LibraryElementTest : public ::testing::Test
{
protected:
  LibraryElementTest();
  virtual ~LibraryElementTest();

  sup::xml::TreeData m_library_tree;
};

sup::xml::TreeData CreateLibraryTree(const std::string& str_dep_name);

std::string GetWrapperLibraryName();

TEST_F(LibraryElementTest, Construction)
{
  EXPECT_NO_THROW(LibraryElement library_elem{m_library_tree});
  auto constr_it = ElementConstructorMap().find(constants::LOAD_LIBRARY_TAG);
  EXPECT_NO_THROW(constr_it->second(m_library_tree));
}

TEST_F(LibraryElementTest, Validation)
{
  {
    sup::xml::TreeData library_tree{constants::LOAD_LIBRARY_TAG};
    library_tree.SetContent("does_not_matter.so");
    EXPECT_NO_THROW(ValidateLibraryTree(library_tree));
    library_tree.AddAttribute("some_attribute", "not_allowed");
    EXPECT_THROW(ValidateLibraryTree(library_tree), sup::xml::ValidationException);
  }
  {
    sup::xml::TreeData library_tree{constants::LOAD_LIBRARY_TAG};
    library_tree.SetContent("does_not_matter.so");
    EXPECT_NO_THROW(ValidateLibraryTree(library_tree));
    sup::xml::TreeData name_tree{constants::FUNCTION_NAME_TAG};
    name_tree.SetContent("some_name");
    library_tree.AddChild(name_tree);
    EXPECT_THROW(ValidateLibraryTree(library_tree), sup::xml::ValidationException);
  }
}

TEST_F(LibraryElementTest, Execution)
{
  LibraryElement library_elem{m_library_tree};
  EXPECT_NO_THROW(library_elem.Execute());

  LibraryElement library_elem_fail{CreateLibraryTree("this_name_does_not_exist")};
  EXPECT_THROW(library_elem_fail.Execute(), RuntimeException);
}

LibraryElementTest::LibraryElementTest()
  : m_library_tree{CreateLibraryTree(GetWrapperLibraryName())}
{}

LibraryElementTest::~LibraryElementTest() = default;

sup::xml::TreeData CreateLibraryTree(const std::string& library_name)
{
  sup::xml::TreeData library_tree{constants::LOAD_LIBRARY_TAG};
  library_tree.SetContent(library_name);
  return library_tree;
}

std::string GetWrapperLibraryName()
{
  return service_wrapper_config::CMakeLibraryInstallDir() + "/libservice-wrapper.so";
}