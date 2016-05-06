/*
 * This file [io/event_poll.cpp] is part of the “libtamias” library
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

#include "../../include/io/event_poll.h"

using tamias::sizetype;
using tamias::EventFd;
using tamias::EventPoll;
using tamias::Vector;

EventFd::EventFd()
{
}

EventFd::~EventFd()
{
}

EventPoll::EventPoll() : events()
{
}

EventPoll::EventPoll( const EventPoll &poll ) : events(poll.events)
{
}

EventPoll& EventPoll::operator = ( const EventPoll &poll )
{
  events = poll.events;
  return *this;
}

EventPoll::~EventPoll()
{
}

sizetype EventPoll::addEvent( EventFd &fd, EventType type )
{
  sizetype result = events.size();
  events.pushBack(makePair(fd.handle(), type));
  return result;
}

Vector <sizetype> EventPoll::poll()
{
  pollfd *fds = new pollfd[events.size()];
  for (sizetype i = 0; i < events.size(); i++)
  {
    fds[i].fd = events[i].first;
    switch (events[i].second)
    {
      case EVENT_IN: fds[i].events = POLLIN; break;
      default: fds[i].events = 0;
    }
  }
  ::poll(fds, events.size(), -1);
  Vector <sizetype> result;
  for (sizetype i = 0; i < events.size(); i++)
    if (fds[i].revents != 0)
      result.pushBack(i);
  delete[] fds;
  return result;
}

