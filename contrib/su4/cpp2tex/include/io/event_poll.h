/*
 * This file [io/event_poll.h] is part of the “libtamias” library
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

#include <poll.h>
#include "../data/pair.h"
#include "../main/vector.h"

namespace tamias
{
  class EventPoll;

  class EventFd
  {
    protected:
      EventFd();
      virtual ~EventFd();
      virtual int handle() = 0;
    private:
      EventFd( const EventFd &fd );
      EventFd& operator = ( const EventFd &fd );
    friend class EventPoll;
  };

  class EventPoll
  {
    public:
      enum EventType
      {
        EVENT_IN
      };

      EventPoll();
      EventPoll( const EventPoll &poll );
      EventPoll& operator = ( const EventPoll &poll );
      virtual ~EventPoll();

      sizetype addEvent( EventFd &fd, EventType type );
      Vector <sizetype> poll();
    private:
      Vector <Pair <int, EventType> > events;
  };
}

