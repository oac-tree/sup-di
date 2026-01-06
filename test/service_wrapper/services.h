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
 * Copyright (c) : 2010-2026 ITER Organization,
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

#include <memory>
#include <string>

class IService
{
public:
  virtual ~IService() = default;

  virtual std::string GetServiceType() const = 0;
};

class Client
{
public:
  Client(const std::string& name, std::unique_ptr<IService>&& service);
  ~Client() = default;

  void Launch();

private:
  std::string m_name;
  std::unique_ptr<IService> m_service;
};

class Service : public IService
{
public:
  Service();
  ~Service() = default;

  std::string GetServiceType() const override;
};
