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

#include "external_test_services.h"

#include <sup/di/object_manager.h>

namespace sup
{
namespace di
{
namespace test
{
namespace external
{

static const std::string HelloWorld = "Hello, world!";
static const std::string DecoratedPrefix = "Decorated:";
static const std::string OwnedPrinterPrefix = "Owned printer:";

static const std::string HelloPrinterName = "HelloPrinter";
static const std::string PrinterDecoratorName = "PrinterDecorator";
static const std::string PrinterOwnerName = "PrinterOwner";
static const std::string PrinterAggregatorName = "PrinterAggregator";

static const std::string HelloTestName = "HelloTest";
static const std::string DecoratedHelloTestName = "DecoratoredHelloTest";
static const std::string OwnedPrinterTestName = "OwnedPrinterTest";
static const std::string AggregatedPrinterTestName = "AggregatedPrinterTest";
static const std::string DiscardPrinterName = "DiscardPrinter";

// Factory function registration
static bool HelloPrinter_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(HelloPrinterName,
    sup::di::ForwardingInstanceFactoryFunction<IPrinter, HelloPrinter>);
static bool PrinterDecorator_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(PrinterDecoratorName,
    sup::di::ForwardingInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter*>);
static bool OwnedPrinter_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(PrinterOwnerName,
    sup::di::ForwardingInstanceFactoryFunction<IPrinter, PrinterOwner, std::unique_ptr<IPrinter>&&>);
static bool PrinterAggregator_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(PrinterAggregatorName,
    sup::di::ForwardingInstanceFactoryFunction<IPrinter, PrinterAggregator, IPrinter*, IPrinter*>);

// Global function registration
static bool HelloTest_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterGlobalFunction(HelloTestName, TestHelloPrinter);
static bool DecoratedHelloTest_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterGlobalFunction(DecoratedHelloTestName,
                                                        TestDecoratedHelloPrinter);
static bool OwnedPrinterTest_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterGlobalFunction(OwnedPrinterTestName,
                                                        TestOwnedPrinter);
static bool AggregatedPrinterTest_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterGlobalFunction(AggregatedPrinterTestName,
                                                        TestAggregatedPrinter);
static bool DiscardPrinter_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterGlobalFunction(DiscardPrinterName, DiscardPrinter);

IPrinter::~IPrinter() = default;

HelloPrinter::HelloPrinter() = default;
HelloPrinter::~HelloPrinter() = default;

std::string HelloPrinter::Print() const
{
  return HelloWorld;
}

PrinterDecorator::PrinterDecorator(IPrinter* printer_)
  : printer{printer_}
{}

PrinterDecorator::~PrinterDecorator() = default;

std::string PrinterDecorator::Print() const
{
 return DecoratedPrefix + printer->Print();
}

PrinterOwner::PrinterOwner(std::unique_ptr<IPrinter>&& printer_)
  : printer{std::move(printer_)}
{}

PrinterOwner::~PrinterOwner() = default;

std::string PrinterOwner::Print() const
{
 return OwnedPrinterPrefix + printer->Print();
}

PrinterAggregator::PrinterAggregator(IPrinter* printer_1_, IPrinter* printer_2_)
  : printer_1{printer_1_}, printer_2{printer_2_}
{}

PrinterAggregator::~PrinterAggregator() = default;

std::string PrinterAggregator::Print() const
{
  return printer_1->Print() + printer_2->Print();
}

bool TestHelloPrinter(const IPrinter& printer)
{
  return printer.Print() == HelloWorld;
}

bool TestDecoratedHelloPrinter(IPrinter* printer)
{
  return printer->Print() == DecoratedPrefix + HelloWorld;
}

bool TestOwnedPrinter(IPrinter& printer)
{
  return printer.Print() == OwnedPrinterPrefix + HelloWorld;
}

bool TestAggregatedPrinter(IPrinter* printer)
{
  return printer->Print() == HelloWorld + DecoratedPrefix + HelloWorld;
}

bool DiscardPrinter(std::unique_ptr<IPrinter>&& printer)
{
  return !printer->Print().empty();
}

}  // namespace external

}  // namespace test

}  // namespace di

}  // namespace sup
