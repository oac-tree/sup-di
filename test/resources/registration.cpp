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

#include <sup/di/object_manager.h>

#include "client.h"

// Register Client

static const bool Client_Registered =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(
    "Client", sup::di::ForwardingInstanceFactoryFunction<Client, Client, const std::string&, int, double>);

// Register global function with function name "LaunchClient"

static const bool Print_Client_Function_Registered =
  sup::di::GlobalObjectManager().RegisterGlobalFunction("PrintClient", PrintClient);
