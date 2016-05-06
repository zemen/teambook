/*
 * wtf/debug.cpp — package for debug output
 */

#include "../../include/wtf/debug.h"

using tamias::sizetype;
using tamias::makePair;
using tamias::IODevice;
using tamias::Printer;
using tamias::String;
using tamias::wtf::DebugOutput;

DebugOutput::DebugOutput() : mPrinters()
{
}

DebugOutput::DebugOutput( const DebugOutput &output ) : mPrinters(output.mPrinters.size())
{
  for (sizetype i = 0; i < output.mPrinters.size(); i++)
  {
    mPrinters[i].first = output.mPrinters[i].first;
    mPrinters[i].second = new Printer(*output.mPrinters[i].second);
  }
}

DebugOutput& DebugOutput::operator = ( const DebugOutput &output )
{
  for (sizetype i = 0; i < mPrinters.size(); i++)
    delete mPrinters[i].second;
  mPrinters.resize(output.mPrinters.size());
  for (sizetype i = 0; i < output.mPrinters.size(); i++)
  {
    mPrinters[i].first = output.mPrinters[i].first;
    mPrinters[i].second = new Printer(*output.mPrinters[i].second);
  }
  return *this;
}

DebugOutput::~DebugOutput()
{
  for (sizetype i = 0; i < mPrinters.size(); i++)
    delete mPrinters[i].second;
}

void DebugOutput::addOutput( IODevice &device, int debugLevel )
{
  mPrinters.pushBack(makePair(debugLevel, new Printer(device)));
}

void DebugOutput::output( int debugLevel, const String &format, ... )
{
  va_list ap;
  va_start(ap, format);
  for (sizetype i = 0; i < mPrinters.size(); i++)
  {
    if (debugLevel > mPrinters[i].first)
      continue;
    Printer &printer = *mPrinters[i].second;
    printer._printf("[debug|level:%d] ", debugLevel);
    printer.vprintf(format, ap);
    printer.println("");
  }
  va_end(ap);
}

