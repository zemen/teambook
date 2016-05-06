/*
 * This file [network/socket.h] is part of the “libtamias” library
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

#ifndef _libtamias_network_socket_h_
#define _libtamias_network_socket_h_

#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "../basic/byte_array.h"
#include "../basic/types.h"
#include "../basic/string.h"
#include "../io/event_poll.h"
#include "../io/iodevice.h"
#include "../io/ioexception.h"
#include "../network/ip.h"

namespace tamias
{
  class Socket : public IODevice, public EventFd
  {
    public:
      enum SocketState
      {
        NOSOCKET, // TODO: rename to STATE_NOSOCKET etc...
        ERROR,
        CONNECTED,
        CLOSED,
        FINISHED
      };

      Socket();
      Socket( const Socket &socket );
      Socket& operator = ( const Socket &socket );
      ~Socket();
      Socket* clone() const;

      bool canRead() const;
      bool canWrite() const;
      bool canSeek() const;
      void close();
      bool eof();
      bool waitForRead();
      ByteArray read( sizetype maxSize = (sizetype)-1 );
      sizetype write( const ByteArray &data );
      void seek( sizetype index );
      friend class TcpClientSocket;
      friend class TcpServerSocket;

      SocketState state() const;
      IpAddress foreignIp() const;
    private:
      SocketState socketState;
      int socketHandle;
      Socket( int newHandle );

      int handle();
  };

  class TcpClientSocket : public Socket
  {
    // TODO: standart methods (constructors, destructor, copy)
    public:
      void connect( const String &host, const uinttype16 port );
      void disconnect();
  };

  class TcpServerSocket : public Socket // TODO: this public is only for EventFd::handle()
  {
    // TODO: standart methods (constructors, destructor, copy)
    public:
      void bind( const uinttype16 port );
      Socket accept();
  };
}

#endif // _libtamias_network_socket_h_

