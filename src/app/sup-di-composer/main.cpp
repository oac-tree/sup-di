/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Dependency injection
 *
 * Description   : The definition of the dependency injection executable in SUP.
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

#include <sup/di-composer-core/composition_root.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void print_usage(const std::string& prog_name)
{
  std::cout << "Usage: " << prog_name << " <options>" << std::endl;
  std::cout << "Options: -h|--help: Print usage." << std::endl;
  std::cout << "         -f|--file <filename>: Load, parse and execute <filename>." << std::endl;
  std::cout << std::endl;
  std::cout << "The program loads <filename>, parses it, creates objects with dependency "
               "injection and calls functions on those instances."
            << std::endl;
  std::cout << std::endl;
}

bool HasHelpOption(const std::vector<std::string>& arguments);
std::string GetFileName(const std::vector<std::string>& arguments);

int main(int argc, char* argv[])
{
  std::vector<std::string> arguments;
  std::for_each(argv, argv + argc, [&](const char* c_str) { arguments.emplace_back(c_str); });

  auto filename = GetFileName(arguments);

  if (HasHelpOption(arguments) || filename.empty())
  {
    print_usage(arguments.at(0));
    return 0;
  }
  sup::di::ExecuteObjectTreeFromFile(filename);
  return 0;
}

//! Returns true if -h or --help option is present.

bool HasHelpOption(const std::vector<std::string>& arguments)
{
  auto on_argument = [](const std::string& str) { return str == "--help" || str == "-h"; };
  return std::find_if(arguments.begin(), arguments.end(), on_argument) != arguments.end();
}

//! Returns filename, which is the parameter after --file or -f option.

std::string GetFileName(const std::vector<std::string>& arguments)
{
  // find position of file argument
  auto on_argument = [](const std::string& str) { return str == "--file" || str == "-f"; };
  auto it = std::find_if(arguments.begin(), arguments.end(), on_argument);

  // taking the next after as a file name
  std::string filename = std::next(it) < arguments.end() ? *std::next(it) : "";
  return filename.find_first_of("-") == 0 ? "" : filename;
}
