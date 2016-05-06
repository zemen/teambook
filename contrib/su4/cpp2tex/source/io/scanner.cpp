/*
 * This file [io/scanner.cpp] is part of the “libtamias” library
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

#include "../../include/io/scanner.h"

using tamias::ByteArray;
using tamias::IODevice;
using tamias::Scanner;

void Scanner::readBuffer()
{
  if (bufferUsed)
    return;
  ByteArray data = device->read(1);
  if (data.size() == 1)
    bufferUsed = true, buffer = (unsigned char)data[0];
  else
    buffer = -1;
}

Scanner::Scanner( const IODevice &newDevice ) : device(newDevice.clone()), bufferUsed(false), buffer(-1)
{
}

Scanner::Scanner( const Scanner &scanner ) : device(scanner.device->clone()), bufferUsed(scanner.bufferUsed),
                                             buffer(scanner.buffer)
{
}

Scanner::~Scanner()
{
  delete device;
}

Scanner& Scanner::operator = ( const Scanner &scanner )
{
  device = scanner.device->clone();
  bufferUsed = scanner.bufferUsed;
  buffer = scanner.buffer;
  return *this;
}

void Scanner::close()
{
  device->close();
}

bool Scanner::eof()
{
  return device->eof();
}

int Scanner::scanByte()
{
  readBuffer();
  return buffer;
}

int Scanner::nextByte()
{
  int result = scanByte();
  bufferUsed = false, buffer = -1;
  return result;
}

void Scanner::skipSpace()
{
  int ch;
  while ((ch = scanByte()) != -1)
    if (ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ')
      bufferUsed = false;
    else
      break;
}

ByteArray Scanner::nextToken()
{
  skipSpace();
  ByteArray result;
  int ch;
  while ((ch = scanByte()) != -1)
    if (!(ch == '\n' || ch == '\r' || ch == '\t' || ch == ' '))
      result += (char)ch, bufferUsed = false;
    else
      break;
  return result;
}

ByteArray Scanner::nextLine()
{
  ByteArray result;
  int ch;
  while ((ch = nextByte()) != -1)
    if (ch == '\n')
      break;
    else
      result += (char)ch;
  return result;
}

