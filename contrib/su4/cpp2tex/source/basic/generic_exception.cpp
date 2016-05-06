/*
 * This file [basic/generic_exception.cpp] is part of the “libtamias” library
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

#include "../../include/basic/generic_exception.h"

using tamias::GenericException;
using tamias::DefaultException;
using tamias::OutOfMemoryException;
using tamias::OutOfBoundsException;

char defaultExceptionType[] = "DefaultException";
char defaultExceptionMessage[] = "undefined exception";
char outOfMemoryExceptionType[] = "OutOfMemoryException";
char outOfMemoryExceptionMessage[] = "failed to allocate memory block";
char outOfBoundsExceptionType[] = "OutOfBoundsException";
char outOfBoundsExceptionMessage[] = "index out of range";

/* class Exception */

GenericException::GenericException()
{
}

GenericException::GenericException( const GenericException& )
{
}

GenericException& GenericException::operator = ( const GenericException& )
{
  return *this;
}

GenericException::~GenericException()
{
}


/* class DefaultException */

DefaultException::DefaultException() : GenericException()
{
}

DefaultException::DefaultException( const DefaultException &exception ) : GenericException(exception)
{
}

DefaultException& DefaultException::operator = ( const DefaultException &exception )
{
  GenericException::operator = (exception);
  return *this;
}

DefaultException::~DefaultException()
{
}

const char* DefaultException::type() const
{
  return defaultExceptionType;
}

const char* DefaultException::message() const
{
  return defaultExceptionMessage;
}


/* class OutOfMemoryException */

OutOfMemoryException::OutOfMemoryException() : GenericException()
{
}

OutOfMemoryException::OutOfMemoryException( const OutOfMemoryException &exception ) : GenericException(exception)
{
}

OutOfMemoryException& OutOfMemoryException::operator = ( const OutOfMemoryException &exception )
{
  GenericException::operator = (exception);
  return *this;
}

OutOfMemoryException::~OutOfMemoryException()
{
}

const char* OutOfMemoryException::type() const
{
  return outOfMemoryExceptionType;
}

const char* OutOfMemoryException::message() const
{
  return outOfMemoryExceptionMessage;
}


/* class OutOfBoundsException */

OutOfBoundsException::OutOfBoundsException() : GenericException()
{
}

OutOfBoundsException::OutOfBoundsException( const OutOfBoundsException &exception ) : GenericException(exception)
{
}

OutOfBoundsException& OutOfBoundsException::operator = ( const OutOfBoundsException &exception )
{
  GenericException::operator = (exception);
  return *this;
}

OutOfBoundsException::~OutOfBoundsException()
{
}

const char* OutOfBoundsException::type() const
{
  return outOfBoundsExceptionType;
}

const char* OutOfBoundsException::message() const
{
  return outOfBoundsExceptionMessage;
}

