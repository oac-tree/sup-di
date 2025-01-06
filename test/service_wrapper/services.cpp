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

#include "services.h"

#include <iostream>

Client::Client(const std::string& name, std::unique_ptr<IService>&& service)
  : m_name{name}
  , m_service{std::move(service)}
{}

void Client::Launch()
{
  std::cout << "Client with name [" << m_name << "] launched." << std::endl;
  std::cout << "  Injected service type: [" << m_service->GetServiceType() << "]" << std::endl;
}

Service::Service() = default;

std::string Service::GetServiceType() const
{
  return "CustomService";
}