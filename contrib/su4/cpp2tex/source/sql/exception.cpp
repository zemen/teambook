/*
 * This file [sql/exception.cpp] is part of the “libtamias” library
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

#include "../../include/sql/exception.h"

using tamias::String;
using tamias::sql::SQLException;

char sqlExceptionType[] = "SQLException";
const String sqlExceptionMessage[] = {"undefined sql exception", "cannot load driver", "driver exception", "result isn't initialized"};

SQLException::SQLException() : Exception(), mType(UNKNOWN_EXCEPTION), mComment(sqlExceptionMessage[mType])
{
}

SQLException::SQLException( SQLExceptionType newType, const String &comment ) : Exception(), mType(newType), mComment(sqlExceptionMessage[mType] + ": " + comment)
{
}

SQLException::SQLException( const SQLException &exception ) : Exception(exception), mType(exception.mType), mComment(exception.mComment)
{
}

SQLException& SQLException::operator = ( const SQLException &exception )
{
  Exception::operator = (exception);
  mType = exception.mType;
  mComment = exception.mComment;
  return *this;
}

SQLException::~SQLException()
{
}

const char* SQLException::type() const
{
  return sqlExceptionType;
}

const String& SQLException::report() const
{
  return mComment;
}

