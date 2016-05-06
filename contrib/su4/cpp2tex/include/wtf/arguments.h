/*
 * tamias/wtf/arguments.h — package for parsing commad-line parameters
 */

#pragma once

// TODO: locale support. WTF?

#include "../basic/string.h"
#include "../basic/types.h"
#include "../data/pair.h"
#include "../io/file.h"
#include "../io/printer.h"
#include "../main/map.h"
#include "../main/tree_rbst.h"
#include "../main/vector.h"

namespace tamias
{
  namespace wtf
  {
    class ArgumentOption
    {
      public:
        enum ParameterType
        {
          PARAMETER_ERROR, PARAMETER_DISABLE, PARAMETER_ENABLE, PARAMETER_BLINK
        };
      public:
        ArgumentOption( const tamias::String &longName, tamias::chartype shortName, ParameterType parameter, int result);
        ArgumentOption( const ArgumentOption &option );
        ArgumentOption& operator = ( const ArgumentOption &option );

        ~ArgumentOption();
      private:
        String mLongName;
        chartype mShortName;
        ParameterType mParameter;
        int mResult;
      friend class ArgumentParser;
    };

    class ArgumentParser
    {
      public:
        ArgumentParser( int defaultOption = 0 );
        ArgumentParser( const ArgumentParser &parser );
        ArgumentParser& operator = ( const ArgumentParser &parser );
        ~ArgumentParser();

        void addOption( const ArgumentOption &option );
        tamias::Vector <tamias::Pair <int, tamias::String> > parse( int argc, char **argv );
        bool error();
      private:
        int mDefaultOption;
        tamias::Vector <ArgumentOption> mOptions;
        bool mError;
        tamias::Printer out; // +1 to WTF
    };
  }
}

