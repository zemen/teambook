/*
 * This file [network/ip.cpp] is part of the “libtamias” library
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

#include "../../include/network/ip.h"

using tamias::uinttype32;
using tamias::IpAddress;
using tamias::String;

IpAddress::IpAddress( uinttype32 ip ) : ipAddress(ip)
{
}

IpAddress::IpAddress( const IpAddress &address ) : ipAddress(address.ipAddress)
{
}

IpAddress& IpAddress::operator = ( const IpAddress &address )
{
  ipAddress = address.ipAddress;
  return *this;
}

IpAddress::~IpAddress()
{
}

uinttype32 IpAddress::ip() const
{
  return ipAddress;
}

void IpAddress::setIp( uinttype32 ip )
{
  ipAddress = ip;
}

String IpAddress::toString() const
{
  String result = "";
  for (int i = 0; i < 4; i++)
  {
    int byte = ((ipAddress >> (8 * (3 - i))) & 0xff);
    if (i != 0)
      result = "." + result;
    if (byte == 0)
      result = "0" + result;
    while (byte != 0)
    {
      result = (chartype)(byte % 10 + '0') + result;
      byte /= 10;
    }
  }
  return result;
}

