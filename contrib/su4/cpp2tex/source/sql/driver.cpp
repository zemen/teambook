/*
 * This file [sql/driver.cpp] is part of the “libtamias” library
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

#include "../../include/sql/driver.h"

using tamias::sql::Driver;
using tamias::sql::SQLException;
using tamias::sql::ExternalDriver;

Driver::Driver()
{
}

Driver::Driver( const Driver& )
{
}

Driver::~Driver()
{
}

Driver& Driver::operator = ( const Driver& )
{
  return *this;
}

ExternalDriver::ExternalDriver()
{
}

ExternalDriver::ExternalDriver( const ExternalDriver& )
{
}

ExternalDriver::~ExternalDriver()
{
}

ExternalDriver& ExternalDriver::operator = ( const ExternalDriver& )
{
  return *this;
}

Driver* ExternalDriver::loadDriver( const String &fileName )
{
  void *dlHandle = ::dlopen((char*)fileName.toUtf8().cString(), RTLD_LAZY);
  if (dlHandle == NULL)
    throw SQLException(SQLException::CANNOT_LOAD_DRIVER, String("cannot open driver library: ") + String(dlerror()));
  CreateFunction func;
  // TODO: using export "C"... rename function into some more readable. Swap “create” and “driver” words
  func = (CreateFunction)::dlsym(dlHandle, "libtamias_sql_driver_create");
  if (func == NULL)
    throw SQLException(SQLException::CANNOT_LOAD_DRIVER, String("cannot find create function: ") + String(dlerror()));
  return func();
}

