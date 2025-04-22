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
 * SPDX-License-Identifier: MIT
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file LICENSE located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include <memory>
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

  virtual std::string Print() const = 0;
};

class HelloPrinter : public IPrinter
{
public:
  HelloPrinter();
  ~HelloPrinter();

  std::string Print() const override;
};

class PrinterDecorator : public IPrinter
{
public:
  PrinterDecorator(IPrinter* printer);
  ~PrinterDecorator();

  std::string Print() const override;
private:
  IPrinter* printer;
};

class PrinterOwner : public IPrinter
{
public:
  PrinterOwner(std::unique_ptr<IPrinter>&& printer);
  ~PrinterOwner();

  std::string Print() const override;
private:
  std::unique_ptr<IPrinter> printer;
};

class PrinterAggregator : public IPrinter
{
public:
  PrinterAggregator(IPrinter* printer_1, IPrinter* printer_2);
  ~PrinterAggregator();

  std::string Print() const override;
private:
  IPrinter* printer_1;
  IPrinter* printer_2;
};

bool TestHelloPrinter(const IPrinter& printer);

bool TestDecoratedHelloPrinter(IPrinter* printer);

bool TestOwnedPrinter(IPrinter& printer);

bool TestAggregatedPrinter(IPrinter* printer);

bool DiscardPrinter(std::unique_ptr<IPrinter>&& printer);

}  // namespace external

}  // namespace test

}  // namespace di

}  // namespace sup
