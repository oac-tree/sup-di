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
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <string>

namespace sup
{
namespace di
{
namespace test
{
namespace external
{

class IPrinter
{
public:
  virtual ~IPrinter();

  virtual std::string Print() = 0;
};

class HelloPrinter : public IPrinter
{
public:
  HelloPrinter();
  ~HelloPrinter();

  std::string Print() override;
};

class PrinterDecorator : public IPrinter
{
public:
  PrinterDecorator(IPrinter* printer);
  ~PrinterDecorator();

  std::string Print() override;
private:
  IPrinter* printer;
};

class PrinterAggregator : public IPrinter
{
public:
  PrinterAggregator(IPrinter* printer_1, IPrinter* printer_2);
  ~PrinterAggregator();

  std::string Print() override;
private:
  IPrinter* printer_1;
  IPrinter* printer_2;
};

bool TestHelloPrinter(IPrinter* printer);

bool TestDecoratedHelloPrinter(IPrinter* printer);

bool TestAggregatedPrinter(IPrinter* printer);

}  // namespace external

}  // namespace test

}  // namespace di

}  // namespace sup
