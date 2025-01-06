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

#include <sup/di-composer-core/exceptions.h>
#include <sup/di-composer-core/tree_extract.h>

#include <sup/xml/tree_data.h>

#include <gtest/gtest.h>

using namespace sup::di;

const std::string TREE_NODE_NAME = "ContentNode";
const std::string TREE_NODE_CONTENT = "Some node content";

class TreeExtractTest : public ::testing::Test
{
protected:
  TreeExtractTest();
  virtual ~TreeExtractTest();
};

sup::xml::TreeData CreateNodeWithContent(const std::string& content);

TEST_F(TreeExtractTest, SetFromTreeNodeContent)
{
  std::string destination;
  auto content_tree = CreateNodeWithContent(TREE_NODE_CONTENT);
  EXPECT_NO_THROW(utils::SetFromTreeNodeContent(destination, content_tree));
  EXPECT_EQ(destination, TREE_NODE_CONTENT);

  sup::xml::TreeData empty_tree{TREE_NODE_NAME};
  EXPECT_THROW(utils::SetFromTreeNodeContent(destination, empty_tree), ParseException);
  EXPECT_EQ(destination, TREE_NODE_CONTENT);
}

TEST_F(TreeExtractTest, AppendFromTreeNodeContent)
{
  std::vector<std::string> destination;
  auto content_tree = CreateNodeWithContent(TREE_NODE_CONTENT);
  EXPECT_EQ(destination.size(), 0);
  EXPECT_NO_THROW(utils::AppendFromTreeNodeContent(destination, content_tree));
  EXPECT_EQ(destination.size(), 1);
  EXPECT_EQ(destination.back(), TREE_NODE_CONTENT);

  sup::xml::TreeData empty_tree{TREE_NODE_NAME};
  EXPECT_THROW(utils::AppendFromTreeNodeContent(destination, empty_tree), ParseException);
  EXPECT_EQ(destination.size(), 1);
  EXPECT_EQ(destination.back(), TREE_NODE_CONTENT);
}

TreeExtractTest::TreeExtractTest() = default;

TreeExtractTest::~TreeExtractTest() = default;

sup::xml::TreeData CreateNodeWithContent(const std::string& content)
{
  sup::xml::TreeData content_node{TREE_NODE_NAME};
  content_node.SetContent(content);
  return content_node;
}
