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

#include "services.h"

#include <sup/di/object_manager.h>

#include <iostream>

// Register Service:

static const bool Service_Registered =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(
    "Service", sup::di::ForwardingInstanceFactoryFunction<IService, Service>);

// Register Client

std::unique_ptr<Client> CreateClient(
  const std::string* name, std::unique_ptr<IService>&& service)
{
  return std::unique_ptr<Client>(new Client(*name, std::move(service)));
}

static const bool Client_Registered =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(
    "Client", CreateClient);

// Register global function with function name "LaunchClient"

bool LaunchClient(Client* client)
{
  client->Launch();
  return true;
}

static const bool Launch_Function_Registered =
  sup::di::GlobalObjectManager().RegisterGlobalFunction("LaunchClient", LaunchClient);

  // Register global function with function name "PrintString"

bool PrintString(const std::string* str)
{
  std::cout << "PrintString called with string [" << *str << "]" << std::endl;
  return true;
}

static const bool Print_String_Function_Registered =
  sup::di::GlobalObjectManager().RegisterGlobalFunction("PrintString", PrintString);
