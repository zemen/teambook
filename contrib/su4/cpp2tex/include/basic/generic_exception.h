/*
 * This file [basic/generic_exception.h] is part of the “libtamias” library
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

#pragma once

namespace tamias
{
  /* base of all exceptions */
  class GenericException
  {
    public:
      GenericException();
      GenericException( const GenericException &exception );
      GenericException& operator = ( const GenericException &exception );
      virtual ~GenericException();

      virtual const char* type() const = 0;
      virtual const char* message() const = 0;
  };
 
  /* should be used in development, when more informative exception class is not written yet */
  class DefaultException : public GenericException
  {
    public:
      DefaultException();
      DefaultException( const DefaultException &exception );
      DefaultException& operator = ( const DefaultException &exception );
      virtual ~DefaultException();

      virtual const char* type() const;
      virtual const char* message() const;
  };

  /* some common exceptions */
  class OutOfMemoryException : public GenericException
  {
    public:
      OutOfMemoryException();
      OutOfMemoryException( const OutOfMemoryException &exception );
      virtual ~OutOfMemoryException();
      OutOfMemoryException& operator = ( const OutOfMemoryException &exception );

      virtual const char* type() const;
      virtual const char* message() const;
  };

  class OutOfBoundsException : public GenericException
  {
    public:
      OutOfBoundsException();
      OutOfBoundsException( const OutOfBoundsException &exception );
      OutOfBoundsException& operator = ( const OutOfBoundsException &exception );
      virtual ~OutOfBoundsException();

      virtual const char* type() const;
      virtual const char* message() const;
  };
};

