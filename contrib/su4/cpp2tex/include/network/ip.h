/*
 * This file [network/ip.h] is part of the “libtamias” library
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

#ifndef _libtamias_network_ip_h_
#define _libtamias_network_ip_h_

#include "../basic/types.h"
#include "../basic/string.h"

namespace tamias
{
  class IpAddress
  {
    public:
      IpAddress( uinttype32 ip = 0 );
      IpAddress( const IpAddress &address );
      IpAddress& operator = ( const IpAddress &address );
      ~IpAddress();

      uinttype32 ip() const;
      void setIp( uinttype32 ip );
      String toString() const; // TODO: may be move this somewhere
    private:
      uinttype32 ipAddress;
  };
}

#endif // _libtamias_network_socket_h_

