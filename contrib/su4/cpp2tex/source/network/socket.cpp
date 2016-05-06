/*
 * This file [network/socket.cpp] is part of the “libtamias” library
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

#include "../../include/network/socket.h"

using tamias::sizetype;
using tamias::utilities::min;
using tamias::ByteArray;
using tamias::IOException;
using tamias::IpAddress;
using tamias::Socket;
using tamias::TcpClientSocket;
using tamias::TcpServerSocket;

Socket::Socket( int newHandle ) : socketState(CONNECTED), socketHandle(newHandle)
{
}

Socket::Socket() : socketState(NOSOCKET), socketHandle(-1)
{
}

Socket::Socket( const Socket &socket ) : socketState(socket.socketState), socketHandle(socket.socketHandle)
{
}

Socket& Socket::operator = ( const Socket &socket )
{
  IODevice::operator = (socket);
  socketState = socket.socketState;
  socketHandle = socket.socketHandle;
  return *this;
}

Socket* Socket::clone() const
{
  return new Socket(*this);
}

Socket::~Socket()
{
  socketState = FINISHED;
}

bool Socket::canRead() const
{
  return true;
}

bool Socket::canWrite() const
{
  return true;
}

bool Socket::canSeek() const
{
  return false;
}

void Socket::close()
{
  if ((socketState != CONNECTED && socketState != CLOSED) || socketHandle == -1 || ::close(socketHandle) < 0)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to close invalid socket");
  socketHandle = -1;
  socketState = NOSOCKET;
}

bool Socket::eof()
{
  if (socketState != CLOSED && socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to test eof in unopened socket");
  return socketState == CLOSED;
}

bool Socket::waitForRead()
{
  if (socketState == CLOSED)
    return false;
  if (socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to wait for non-connected socket");
  struct pollfd fd;
  fd.fd = socketHandle;
  fd.events = POLLIN | POLLRDHUP;
  ::poll(&fd, 1, -1);
  if ((fd.revents & POLLIN) == 0)
    socketState = CLOSED;
  return (fd.revents & POLLIN) != 0;
}

ByteArray Socket::read( sizetype maxSize )
{
  if (socketState == CLOSED)
    return ByteArray();
  if (socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to read from socket without connection");
  ByteArray result;
  while (result.size() < maxSize)
  {
    sizetype currentSize = min(maxSize - result.size(), 1024lu);
    void *data = ::malloc(currentSize);
    int res = ::recv(socketHandle, data, currentSize, MSG_DONTWAIT);
    if (res < 0 && errno != EWOULDBLOCK)
    {
      ::free(data);
      throw IOException::fromErrno(errno);
    }
    if (res > 0)
      result += ByteArray(data, res);
    ::free(data);
    if (res == 0)
      socketState = CLOSED;
    if (res <= 0)
      break; // So it goes, I think...
  }
  return result;
}

sizetype Socket::write( const ByteArray &data )
{
  if (socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to write to socket without connection");
  sizetype position = 0;
  while (position < data.size())
  {
    int result = ::send(socketHandle, (char*)data.cString() + position, data.size(), 0);
    if (result < 0)
      throw IOException::fromErrno(errno);
    position += result;
  }
  return position;
}

void Socket::seek( sizetype index )
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to seek in socket");
}

Socket::SocketState Socket::state() const
{
  return socketState;
}

IpAddress Socket::foreignIp() const
{
  if (socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to ask for address from socket without connection");
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  if (::getpeername(socketHandle, (sockaddr*)&addr, &addr_len) != 0)
    throw IOException(IOException::ERROR_IO_UNKNOWN, "getpeername() failed");
  if (addr_len > sizeof(addr))
    throw IOException(IOException::ERROR_IO_UNKNOWN, "getpeername(): not an in?");
  return IpAddress(addr.sin_addr.s_addr);
}

int Socket::handle()
{
  if (socketState != CONNECTED)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to poll socket without connection");
  return socketHandle;
}

void TcpClientSocket::connect( const String &host, const uinttype16 port )
{
  if (socketState != NOSOCKET)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to connect already connected socket");
  socketHandle = ::socket(AF_INET, SOCK_STREAM, 0);
  if (socketHandle < 0)
    throw IOException::fromErrno(errno);
  struct hostent *hostVal = ::gethostbyname((char*)host.toUtf8().cString());
  if (hostVal == NULL)
    throw IOException::fromErrno(h_errno);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = *((int*)hostVal->h_addr);
  if (::connect(socketHandle, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    throw IOException::fromErrno(errno);
  socketState = CONNECTED;
}

void TcpClientSocket::disconnect()
{
  close();
}

void TcpServerSocket::bind( const uinttype16 port )
{
  if (socketState != NOSOCKET)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to bind already connected socket");
  socketHandle = ::socket(AF_INET, SOCK_STREAM, 0);
  if (socketHandle < 0)
    throw IOException::fromErrno(errno);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  // htons is a f**ing define T_T
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if (::bind(socketHandle, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    throw IOException::fromErrno(errno);
  if (::listen(socketHandle, 1) < 0)
    throw IOException::fromErrno(errno);
  socketState = CONNECTED;
}

Socket TcpServerSocket::accept()
{
  // TODO: check socket's state
  int sock = ::accept(socketHandle, NULL, NULL);
  if (sock < 0)
    throw IOException::fromErrno(errno);
  return Socket(sock);
}

