/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition and implementation for dependency injection templates in SUP.
 *
 * Author        : Ricardo Torres (Ext)
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

#include "keep_alive.h"

#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include <atomic>

namespace sup
{
namespace di
{
namespace services
{

std::atomic<bool> signalReceived(false);

// Function to handle the interrupt signal
void interruptHandler(int signal)
{
  std::cout << "Terminating the execution with signal: " << signal << std::endl;
  signalReceived.store(true);
}

bool KeepAlive()
{
  signal(SIGINT, interruptHandler);
  while (!signalReceived.load())
  {
    // Sleep for a certain amount of time
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  return false;
}

}  // namespace services

}  // namespace di

}  // namespace sup
