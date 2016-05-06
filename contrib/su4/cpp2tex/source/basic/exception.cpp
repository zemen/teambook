/*
 * This file [basic/exception.cpp] is part of the “libtamias” library
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

#include "../../include/basic/exception.h"

using tamias::Exception;
using tamias::CommonException;

char exceptionMessage[] = "use report() for details";
char commonExceptionType[] = "CommonException";

/* class Exception */

Exception::Exception() : GenericException()
{
}

Exception::Exception( const Exception &exception ) : GenericException(exception)
{
}

Exception& Exception::operator = ( const Exception &exception )
{
  GenericException::operator = (exception);
  return *this;
}

Exception::~Exception()
{
}

const char* Exception::message() const
{
  return exceptionMessage;
}


/* class CommonException */

CommonException::CommonException( const tamias::String &report ) : Exception(), mReport(report)
{
}

CommonException::CommonException( const CommonException &exception ) : Exception(), mReport(exception.mReport)
{
}

CommonException& CommonException::operator = ( const CommonException &exception )
{
  Exception::operator = (exception);
  mReport = exception.mReport;
  return *this;
}

CommonException::~CommonException()
{
}

const char* CommonException::type() const
{
  return commonExceptionType;
}

const tamias::String& CommonException::report() const
{
  return mReport;
}

