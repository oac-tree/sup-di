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

#ifndef SUP_DI_COMPOSER_EXCEPTIONS_H_
#define SUP_DI_COMPOSER_EXCEPTIONS_H_

#include <sup/xml/tree_data.h>

#include <exception>
#include <string>

namespace sup
{
namespace di
{

  /**
 * @brief Base Exception class with message.
 */
class MessageException : public std::exception
{
public:
  MessageException(std::string message);
  const char* what() const noexcept override;
private:
  std::string m_message;
};

/**
 * @brief Exception thrown when parsing to an object failed.
 */
class ParseException : public MessageException
{
public:
  ParseException(const std::string& message);
};

/**
 * @brief Generic exception thrown when an operation fails without clear reason, e.g. during a call
 * to a library method that is not under control.
 */
class RuntimeException : public MessageException
{
public:
  RuntimeException(const std::string& message);
};

}  // namespace di

}  // namespace sup

#endif  // SUP_DI_COMPOSER_EXCEPTIONS_H_
