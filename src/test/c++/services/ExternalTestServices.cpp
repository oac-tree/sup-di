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

#include "ExternalTestServices.h"

#include "sup/di/ObjectManager.h"

using namespace sup::di::test::external;

static const std::string HelloWorld = "Hello, world!";
static const std::string DecoratedPrefix = "Decorated:";

static const std::string HelloPrinterName = "HelloPrinter";
static const std::string PrinterDecoratorName = "PrinterDecorator";
static const std::string PrinterAggregatorName = "PrinterAggregator";

// Factory function registration
static bool HelloPrinter_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(HelloPrinterName,
    sup::di::GenericInstanceFactoryFunction<IPrinter, HelloPrinter>);
static bool PrinterDecorator_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(PrinterDecoratorName,
    sup::di::GenericInstanceFactoryFunction<IPrinter, PrinterDecorator, IPrinter>);
static bool PrinterAggregator_Globally_Registered_ =
  sup::di::GlobalObjectManager().RegisterFactoryFunction(PrinterAggregatorName,
    sup::di::GenericInstanceFactoryFunction<IPrinter, PrinterAggregator, IPrinter, IPrinter>);

IPrinter::~IPrinter() = default;

HelloPrinter::HelloPrinter() = default;
HelloPrinter::~HelloPrinter() = default;

std::string HelloPrinter::Print()
{
  return HelloWorld;
}

PrinterDecorator::PrinterDecorator(IPrinter* printer_)
  : printer{printer_}
{}

PrinterDecorator::~PrinterDecorator() = default;

std::string PrinterDecorator::Print()
{
 return DecoratedPrefix + printer->Print();
}

PrinterAggregator::PrinterAggregator(IPrinter* printer_1_, IPrinter* printer_2_)
  : printer_1{printer_1_}, printer_2{printer_2_}
{}

PrinterAggregator::~PrinterAggregator() = default;

std::string PrinterAggregator::Print()
{
  return printer_1->Print() + printer_2->Print();
}
