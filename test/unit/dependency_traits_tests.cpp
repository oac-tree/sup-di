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

#include "sup/di/dependency_traits.h"

#include <gtest/gtest.h>

using namespace sup::di;

class DependencyTraitsTest : public ::testing::Test
{
protected:
  DependencyTraitsTest() = default;
  virtual ~DependencyTraitsTest() = default;
};

class TestClass {};

template <typename D, typename V>
struct IsDependencyValueTypePair : public std::is_same<internal::ValueType<D>, V>
{};

TEST_F(DependencyTraitsTest, LegalDependencyTypes)
{
  // Check legal dependency types
  EXPECT_TRUE((internal::IsLegalDependencyType<TestClass>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<TestClass&>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<TestClass*>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<const TestClass>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<const TestClass&>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<const TestClass*>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<std::unique_ptr<TestClass>>::value));
  EXPECT_TRUE((internal::IsLegalDependencyType<std::unique_ptr<TestClass>&&>::value));
  // Weird, but allowed. Note that its ValueType will be std::unique_ptr<TestClass> and
  // NOT TestClass
  EXPECT_TRUE((internal::IsLegalDependencyType<std::unique_ptr<TestClass>&>::value));

  // Illegal dependency types
  EXPECT_FALSE((internal::IsLegalDependencyType<TestClass&&>::value));
  EXPECT_FALSE((internal::IsLegalDependencyType<std::unique_ptr<const TestClass>>::value));
  EXPECT_FALSE((internal::IsLegalDependencyType<std::unique_ptr<TestClass*>>::value));
  EXPECT_FALSE((internal::IsLegalDependencyType<std::unique_ptr<TestClass&&>>::value));
}

TEST_F(DependencyTraitsTest, ValueTypes)
{
  // Common dependency types (by value, lvalue reference or pointer)
  EXPECT_TRUE((IsDependencyValueTypePair<int, int>::value));
  EXPECT_FALSE((IsDependencyValueTypePair<TestClass, int>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<TestClass, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<const TestClass, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<volatile TestClass, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<const volatile TestClass, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<const TestClass&, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<const TestClass*, TestClass>::value));

  // Dependency types of type unique_ptr
  EXPECT_TRUE((IsDependencyValueTypePair<std::unique_ptr<TestClass>, TestClass>::value));
  EXPECT_TRUE((IsDependencyValueTypePair<std::unique_ptr<TestClass>&&, TestClass>::value));
}
