/*
 * wtf/bsql.cpp — some improvements for sql api
 */

#include "../../include/wtf/bsql.h"

using tamias::chartype;
using tamias::sizetype;
using tamias::uinttype32;
using tamias::Pair;
using tamias::String;
using tamias::Vector;
using tamias::sql::Connection;
using tamias::sql::Result;
using tamias::wtf::BSqlConnection;

String BSqlConnection::quoteString( const String &source ) const
{
  String result = "";
  for (sizetype i = 0; i < source.length(); i++)
    if (source[i] == '\n')
      result += "\\n";
    else if (source[i] == '\0')
      result += "\\0";
    else if (source[i] == '\r')
      result += "\\r";
    else if (source[i] == '\t')
      result += "\\t";
    else if (source[i] == '\'')
      result += "\\\'";
    else if (source[i] == '\"')
      result += "\\\"";
    else if (source[i] == '\\')
      result += "\\\\";
    else
      result += source[i];
  return result;
}

BSqlConnection::BSqlConnection( tamias::sql::Driver *driver ) : Connection(driver)
{
}

BSqlConnection::BSqlConnection( const BSqlConnection &connection ) : Connection(connection)
{
}

BSqlConnection& BSqlConnection::operator = ( const BSqlConnection &connection )
{
  Connection::operator = (connection);
  return *this;
}

BSqlConnection::~BSqlConnection()
{
}

Result BSqlConnection::query( const String &queryString, ... )
{
  String realQuery = "";
  va_list ap;
  va_start(ap, queryString);
  for (sizetype i = 0; i < queryString.length(); i++)
  {
    if (queryString[i] != '%')
    {
      realQuery += queryString[i];
      continue;
    }
    if (++i >= queryString.length())
      continue;
    chartype specification = queryString[i];
    if (specification == '%')
    {
      realQuery += specification;
      continue;
    }
    else if (specification == 's')
    {
      String &value = *(String*)va_arg(ap, String*);
      realQuery += '\'' + quoteString(value) + '\'';
    }
    else if (specification == 'u')
    {
      uinttype32 value = (uinttype32)va_arg(ap, uinttype32);
      String temp = "";
      while (value > 0)
        temp = (value % 10 + '0') + temp, value /= 10;
      if (temp == "")
        temp = "0";
      realQuery += '\'' + temp + '\'';
    }
  }
  va_end(ap);
  return Connection::query(realQuery);
}

void BSqlConnection::lockTables( const Vector <Pair <String, LockType> > &tables )
{
  char lock[2][6] = {"read", "write"};
  String queryString = "lock tables";
  for (sizetype i = 0; i < tables.size(); i++)
    queryString += " ,"[i > 0] + tables[i].first + " " + lock[tables[i].second];
  Connection::query(queryString);
}

void BSqlConnection::unlockTables()
{
  Connection::query("unlock tables");
}

tamias::sizetype BSqlConnection::nextId( const String &tableName, const String &fieldName )
{
  Result idResult = query("select max(" + fieldName + ") from " + tableName);
  if (!idResult.next())
    throw tamias::DefaultException(); // TODO: another exception
  if (idResult.get("max(" + fieldName + ")") == "")
    return 0;
  else
    return 1 + tamias::wtf::utilities::stringToInt(idResult.get("max(" + fieldName + ")"));
}

