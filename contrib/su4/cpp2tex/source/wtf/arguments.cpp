/*
 * wtf/arguments.cpp — package for parsing command-line parameters
 * current file version: 0.01-alpha1-000 (39-254/2009-07-12)
 */

#include "../../include/wtf/arguments.h"

using tamias::chartype;
using tamias::sizetype;
using tamias::makePair;
using tamias::File;
using tamias::Map;
using tamias::Pair;
using tamias::Printer;
using tamias::RBSTree;
using tamias::String;
using tamias::Vector;
using tamias::wtf::ArgumentOption;
using tamias::wtf::ArgumentParser;

ArgumentOption::ArgumentOption( const String &longName, chartype shortName, ParameterType parameter, int result )
              : mLongName(longName), mShortName(shortName), mParameter(parameter), mResult(result)
{
}

ArgumentOption::ArgumentOption( const ArgumentOption &option ) : mLongName(option.mLongName), mShortName(option.mShortName),
                                                                 mParameter(option.mParameter), mResult(option.mResult)
{
}

ArgumentOption& ArgumentOption::operator = ( const ArgumentOption &option )
{
  mLongName = option.mLongName;
  mShortName = option.mShortName;
  mParameter = option.mParameter;
  mResult = option.mResult;
  return *this;
}

ArgumentOption::~ArgumentOption()
{
}

ArgumentParser::ArgumentParser( int defaultOption ) : mDefaultOption(defaultOption), mError(false), out(File::stdout)
{
}

ArgumentParser::ArgumentParser( const ArgumentParser &parser ) : mDefaultOption(parser.mDefaultOption),
                                                                 mOptions(parser.mOptions),
                                                                 mError(parser.mError),
                                                                 out(parser.out)
{
}

ArgumentParser& ArgumentParser::operator = ( const ArgumentParser &parser )
{
  mDefaultOption = parser.mDefaultOption;
  mOptions = parser.mOptions;
  mError = parser.mError;
  out = parser.out;
  return *this;
}

ArgumentParser::~ArgumentParser()
{
}

void ArgumentParser::addOption( const ArgumentOption &option )
{
  mOptions.pushBack(option);
}

Vector <Pair <int, String> > ArgumentParser::parse( int argc, char **argv )
{
  Map <RBSTree, String, sizetype> longNames;
  Map <RBSTree, chartype, sizetype> shortNames;
  for (sizetype i = 0; i < mOptions.size(); i++)
  {
    longNames[mOptions[i].mLongName] = i;
    if (mOptions[i].mShortName != (chartype)-1)
      shortNames[mOptions[i].mShortName] = i;
  }
  Vector <Pair <int, String> > result;
  bool endOfArguments = false;
  for (int i = 1; i < argc; i++)
  {
    String argument = argv[i];
    if (argument.length() > 0 && argument[0] == '-' && !endOfArguments)
      if (argument.length() > 1 && argument[1] == '-')
      {
        if (argument == "--")
        {
          endOfArguments = true;
          continue;
        }
        sizetype equal = argument.find('=');
        String option = argument.subString(2, equal - 2);
        String parameter = equal == argument.length() ? "" : argument.subString(equal + 1, argument.length() - 1 - equal);
        if (longNames.count(option) == 0)
          out._printf("unknown option: --%$S\n", &option);
        else
          result.pushBack(makePair(mOptions[longNames[option]].mResult, parameter));
      }
      else
        for (sizetype j = 1; j < argument.length(); j++)
          if (shortNames.count(argument[j]) == 0)
            out._printf("unknown option: -%c\n", argument[j]);
          else
          {
            sizetype index = shortNames[argument[j]];
            String parameter = "";
            if (mOptions[index].mParameter == ArgumentOption::PARAMETER_ENABLE ||
               (mOptions[index].mParameter == ArgumentOption::PARAMETER_BLINK && j < argument.length() - 1))
            {
              if (j < argument.length() - 1)
                parameter = argument.subString(j + 1, argument.length() - 1 - j), j = argument.length();
              else
                parameter = String(argv[++i]);
            }
            result.pushBack(makePair(mOptions[index].mResult, parameter));
          }
    else
      result.pushBack(makePair(mDefaultOption, argument));
  }
  return result;
}

bool ArgumentParser::error()
{
  return mError;
}

