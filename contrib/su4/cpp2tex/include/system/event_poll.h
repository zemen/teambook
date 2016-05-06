/*
 * This file [system/event_poll.h] is part of the “libtamias” library
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
  class EventFd;
  class EventPoll;
}

#include <poll.h> // POXIS support for polling
#include "../data/pair.h"
#include "../data/vector.h"

class tamias::EventFd {
  protected:
    EventFd();
    virtual ~EventFd();
    virtual int handle() = 0;

  private:
    EventFd( EventFd const &fd );
    EventFd& operator = ( EventFd const &fd );

  friend class EventPoll;
};

class tamias::EventPoll {
  public:
    enum EventType {
      EVENT_IN
    };

    EventPoll();
    EventPoll( EventPoll const &poll );
    EventPoll& operator = ( EventPoll const &poll );
    virtual ~EventPoll();

    sizetype addEvent( EventFd &fd, EventType type );
    // TODO: support of deleting events.
    Vector <sizetype> poll();

  private:
    Vector <Pair <int, EventType> > events;
};

