/*
 * This file [sql/result.cpp] is part of the “libtamias” library
 * Copyright (c) 2007-2009 Oleg Davydov, Yury Petrov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Our contacts:
 *   mailto: burunduk3@gmail.com (Oleg Davydov)
 *   mailto: jpsbur@gmail.com (Yury Petrov)
 */

#include "../../include/sql/result.h"

using tamias::String;
using tamias::sql::Driver;
using tamias::sql::Result;
using tamias::sql::SQLException;

Result::Result() : driver(NULL), result((sizetype)-1)
{
}

Result::Result( Driver *newDriver, uinttype32 newResult) : driver(newDriver), result(newResult)
{
}

Result::Result( const Result &res ) : driver(res.driver), result(res.result)
{
}

Result& Result::operator = ( const Result &res )
{
  driver = res.driver;
  result = res.result;
  return *this;
}

Result::~Result()
{
  if (driver == NULL)
    return;
  if ((error = driver->resultFree(result)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  driver = NULL;
  result = (sizetype)-1;
}

bool Result::next()
{
// TODO: we shouldn't be too laconical
  if (driver == NULL)
    throw SQLException(SQLException::RESULT_EMPTY, "");
  if ((error = driver->resultNext(result)) != 0)
  {
    driver->errorFree(error);
    return false;
  }
  return true;
}

String Result::get( sizetype column )
{
  if (driver == NULL)
    throw SQLException(SQLException::RESULT_EMPTY, "");
  String res;
  if ((error = driver->resultGet(result, column, &res)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  return res;
}

String Result::get( const String& column )
{
  if (driver == NULL)
    throw SQLException(SQLException::RESULT_EMPTY, "");
  String res;
  if ((error = driver->resultGet(result, column, &res)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  return res;
}

