/*
 * libtamias/wtf/debug.h — package for debug output
 */

#pragma once

/*
 * About debug levels.
 * Normally debug levels are numbered from 0 (no output) to n-1 (full output) for some n.
 * So if output device accept level x it would receive all debug with level less or equal to x.
 * Nothing cat stop you to use negative levels ^_~
 * Example debug levels (from testsys):
 *   0 NOLOGGING
 *   1 FATAL
 *   2 ERROR
 *   3 WARNING
 *   4 INFO
 *   5 DIAG
 *   6 DEBUG
 *   7 EXTRADEBUG
 *   8 NEVER
 */

#include <cstdarg>
#include "../basic/string.h"
#include "../data/pair.h"
#include "../io/iodevice.h"
#include "../io/printer.h"
#include "../main/vector.h"

namespace tamias
{
  namespace wtf
  {
    class DebugOutput
    {
      public:
        DebugOutput();
        DebugOutput( const DebugOutput &output );
        DebugOutput& operator = ( const DebugOutput &output );
        ~DebugOutput();

        void addOutput( IODevice &output, int debugLevel );
        void output( int debugLevel, const String &format, ... );
      private:
        Vector <Pair <int, Printer*> > mPrinters;
    };
  }
}

