/*
 * This file [system/socket.h] is part of the “libtamias” library
 * Copyright (c) 2007-2010 Oleg Davydov, Yury Petrov
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

namespace tamias {
  class Socket;
  class TcpClientSocket;
  class TcpServerSocket;
}

#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "../basic/byte_array.h"
#include "../basic/types.h"
#include "../basic/utilities.h"
#include "../system/event_poll.h"
#include "../system/ip.h"

class tamias::Socket : public EventFd {
  public:
    enum SocketState {
      STATE_NOSOCKET, STATE_ERROR, STATE_CONNECTED, STATE_CLOSED, STATE_FINISHED
    };

  public:
    Socket();
    ~Socket();

    ByteArray read( sizetype maxSize = (sizetype)-1 );
    void write( ByteArray const &data );
    sizetype tryWrite( ByteArray const &data ); // added for testing once
    void close();

    SocketState state() const;
    IpAddress foreignIp() const;

  private:
    SocketState mState;
    int mHandle;

    Socket( int newHandle );
    int handle();

    Socket( Socket const &socket );
    Socket& operator = ( Socket const &socket );

  friend class TcpClientSocket;
  friend class TcpServerSocket;
};

class tamias::TcpClientSocket : public Socket {
  public:
    TcpClientSocket();
    ~TcpClientSocket();

    void connect( ByteArray const &host, uinttype16 port );
    void disconnect();

  private:
    TcpClientSocket( TcpClientSocket const &socket );
    TcpClientSocket& operator = ( TcpClientSocket const &socket );
};

class tamias::TcpServerSocket : public Socket { // TODO: this public is only for EventFd::handle()
  public:
    TcpServerSocket();
    ~TcpServerSocket();

    void bind( uinttype16 port );
    Socket* accept();
    // TODO: where is disconnect?

  private:
    TcpServerSocket( TcpServerSocket const &socket );
    TcpServerSocket& operator = ( TcpServerSocket const &socket );
};

