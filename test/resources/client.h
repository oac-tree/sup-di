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

#include <string>
#include <iostream>

class Client
{
public:
  Client(const std::string& name, int id, double timecode)
    : m_name{name}, m_id{id}, m_timecode{timecode} {};
  ~Client() = default;

  std::string m_name;
  int m_id;
  double m_timecode;
};

inline bool PrintClient(const Client& client)
{
  std::cout << "Printing client information:" << std::endl;
  std::cout << "----------------------------" << std::endl;
  std::cout << "  Name:     " << client.m_name << std::endl;
  std::cout << "  Id:       " << client.m_id << std::endl;
  std::cout << "  Timecode: " << client.m_timecode << std::endl;
  return true;
}