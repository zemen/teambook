#include "../../include/wtf/web_utilities.h"

using tamias::sizetype;
using tamias::ByteArray;
using tamias::String;

int hexToInt( char ch )
{
  if (ch >= '0' && ch <= '9')
    return ch - '0';
  if (ch >= 'A' && ch <= 'F')
    return 10 + ch - 'A';
  if (ch >= 'a' && ch <= 'f')
    return 10 + ch - 'a';
  return -1;
}

String tamias::wtf::web::utilities::decodeURIString( const ByteArray &source )
{
  ByteArray res;
  for (sizetype i = 0; i < source.length(); i++)
    if (source[i] == '%')
    {
      char tmp = 0;
      for (int j = 0; j < 2; j++)
        tmp = tmp * 16 + hexToInt(source[++i]);
      res += tmp;
    }
    else if (source[i] == '+')
      res += ' ';
    else
      res += source[i];
  return res;
}

String tamias::wtf::web::utilities::encodeHTTPParameter( const String &source )
{
  bool token = source.length() > 0;
  for (sizetype i = 0; i < source.length(); i++)
    if (source[i] <= ' ' || source[i] >= 127 || source[i] == '(' || source[i] == ')' ||
        source[i] == '<' || source[i] == '>' || source[i] == '@' || source[i] == ',' ||
        source[i] == ';' || source[i] == ':' || source[i] == '\\' || source[i] == '/' ||
        source[i] /* WTF?*/ == '[' || source[i] == ']' || source[i] == '?' ||
        source[i] == '=' || source[i] == '"' || source[i] == '{' || source[i] == '}')
      token = false, i = source.length();
  if (token)
    return source;
  String result = "\"";
  for (sizetype i = 0; i < source.length(); i++)
    if (source[i] == '"' || (source[i] >= 0 && source[i] <= ' ') || source[i] == 127 || source[i] == '\\')
      result += "\\" + source[i];
    else
      result += source[i];
  result += "\"";
  return result;
}

