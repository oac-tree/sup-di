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

class IPrinter
{
public:
  virtual ~IPrinter() = default;

  virtual std::string Print() const = 0;
};

const std::string HelloWorld = "Hello, world!";
const std::string DecoratedPrefix = "Decorated:";
const std::string OwnedPrinterPrefix = "Owned printer:";

const std::string HelloPrinterName = "HelloPrinter";
const std::string PrinterDecoratorName = "PrinterDecorator";
const std::string PrinterOwnerName = "PrinterOwner";
const std::string PrinterAggregatorName = "PrinterAggregator";

class HelloPrinter : public IPrinter
{
public:
  HelloPrinter() = default;
  ~HelloPrinter() = default;

  std::string Print() const override
  {
    return HelloWorld;
  }
};

class PrinterDecorator : public IPrinter
{
public:
  PrinterDecorator(const IPrinter* printer_) : printer{printer_} {}
  ~PrinterDecorator() = default;

  std::string Print() const override
  {
    return DecoratedPrefix + printer->Print();
  }
private:
  const IPrinter* printer;
};

class PrinterOwner : public IPrinter
{
public:
  PrinterOwner(std::unique_ptr<IPrinter>&& printer_) : printer{std::move(printer_)} {}
  ~PrinterOwner() = default;

  std::string Print() const override
  {
    return OwnedPrinterPrefix + printer->Print();
  }
private:
  std::unique_ptr<IPrinter> printer;
};

class PrinterAggregator : public IPrinter
{
public:
  PrinterAggregator(IPrinter* printer_1_, IPrinter* printer_2_)
    : printer_1{printer_1_}, printer_2{printer_2_} {}
  ~PrinterAggregator() = default;

  std::string Print() const override
  {
    return printer_1->Print() + printer_2->Print();
  }
private:
  IPrinter* printer_1;
  IPrinter* printer_2;
};

std::unique_ptr<IPrinter> HelloPrinterFactoryFunction()
{
  return std::unique_ptr<IPrinter>(new HelloPrinter());
}

std::unique_ptr<IPrinter> PrinterDecoratorFactoryFunction(const IPrinter* printer)
{
  return std::unique_ptr<IPrinter>(new PrinterDecorator(printer));
}

bool TestHelloPrinter(const IPrinter* printer)
{
  return printer->Print() == HelloWorld;
}

bool TestDecoratedHelloPrinter(IPrinter* printer)
{
  return printer->Print() == DecoratedPrefix + HelloWorld;
}

bool TestOwnedPrinter(IPrinter* printer)
{
  return printer->Print() == OwnedPrinterPrefix + HelloWorld;
}

bool TestAggregatedPrinter(IPrinter* printer)
{
  return printer->Print() == HelloWorld + DecoratedPrefix + HelloWorld;
}

bool TestString(const std::string* str)
{
  if (str->size() == 0)
  {
    return false;
  }
  return true;
}