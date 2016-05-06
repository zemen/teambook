/*
 * This file [sql/connection.cpp] is part of the “libtamias” library
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

#include "../../include/sql/connection.h"

using tamias::sql::Connection;
using tamias::sql::Driver;
using tamias::sql::Result;
using tamias::sql::SQLException;

Connection::Connection( Driver *newDriver ) : driver(newDriver), error(0)
{
}

Connection::Connection( const Connection &connection ) : driver(connection.driver), error(connection.error)
{
}

Connection::~Connection()
{
  delete driver;
  driver = NULL;
}

Connection& Connection::operator = ( const Connection &connection )
{
  driver = connection.driver;
  error = connection.error;
  return *this;
}

void Connection::connect( const String &host, const String &user, const String &password, const String &database )
{
  if ((error = driver->setHost(host)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  if ((error = driver->setUser(user, password)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  if ((error = driver->setDatabase(database)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  if ((error = driver->connect()) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
}

void Connection::close()
{
  if ((error = driver->disconnect()) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
}

Result Connection::query( const String &str )
{
  uinttype32 result;
  if ((error = driver->query(str, &result)) != 0)
    throw SQLException(SQLException::DRIVER_EXCEPTION, driver->errorString(error));
  return Result(driver, result);
}

