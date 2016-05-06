/*
 * This file [io/ioexception.cpp] is part of the “libtamias” library
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

#include "../../include/io/ioexception.h"

//using tamias::ByteArray;
using tamias::IOException;

char ioExceptionType[] = "IOException";
// char unknownErrorMessage[] = "undefined i/o error";
// char unexpectedEndOfFileMessage[] = "end of file found while reading";
// char invalidOperationMessage[] = "operation isn't appiliable for this device";
// TODO ^^ what is it?

IOException::IOException( const IOExceptionType newType, const tamias::String &message ) : Exception(), errorType(newType),
                                                                                           errorMessage(message)
{
}

IOException::IOException( const IOException& exception )
           : Exception(exception), errorType(exception.errorType), errorMessage(exception.errorMessage)
{
}

IOException::~IOException()
{
}

IOException& IOException::operator = ( const IOException &exception )
{
  Exception::operator = (exception);
  errorType = exception.errorType;
  errorMessage = exception.errorMessage;
  return *this;
}

IOException IOException::fromErrno( int stdErrno )
{
  return IOException(ERROR_IO_ERRNO, "errno: " + tamias::String(::strerror(stdErrno)));
}

const char* IOException::type() const
{
  return ioExceptionType;
}

const tamias::String& IOException::report() const
{
  return errorMessage;
}

IOException::IOExceptionType IOException::getType() const
{
  return errorType;
}

