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

#include <sup/di/index_sequence.h>

#include <gtest/gtest.h>

#include <type_traits>

using namespace sup::di;

class IndexSequenceTest : public ::testing::Test
{
protected:
  IndexSequenceTest() {};
  virtual ~IndexSequenceTest() {};
};

TEST_F(IndexSequenceTest, MakeIndexSequence)
{
  EXPECT_TRUE((std::is_same<internal::MakeIndexSequence<0>, internal::IndexSequence<>>::value));
  EXPECT_TRUE((std::is_same<internal::MakeIndexSequence<1>, internal::IndexSequence<0>>::value));
  EXPECT_TRUE((std::is_same<internal::MakeIndexSequence<5>, internal::IndexSequence<0, 1, 2, 3, 4>>::value));
}
