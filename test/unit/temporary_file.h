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

#ifndef SUP_DI_TEMPORARY_FILE_H_
#define SUP_DI_TEMPORARY_FILE_H_

#include <string>

namespace sup
{
namespace di
{
namespace test
{
class TemporaryTestFile
{
public:
  TemporaryTestFile(std::string filename, std::string contents);
  ~TemporaryTestFile();

private:
  std::string m_filename;
};

}  // namespace test

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_TEMPORARY_FILE_H_
