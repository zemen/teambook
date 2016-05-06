/*
 * This file [system/thread.h] is part of the “libtamias” library
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
  class Thread;
  class FunctionThread;
  template <typename ClassType> class MethodThread;
}

#include <pthread.h>
#include <time.h>
#include "../basic/time.h"

class tamias::Thread {
  public:
    Thread();
    Thread( Thread const &thread );
    Thread& operator = ( Thread const &thread );
    virtual ~Thread();

    void create();
    void cancel();
    static void sleep( Time const &time );

  protected:
    virtual void* run();

  private:
    pthread_t mHandle;

  friend void* threadRun( void *thread );
};

class tamias::FunctionThread : public Thread {
  public:
    typedef void(*Function)(void);

  public:
    FunctionThread( Function function );
    FunctionThread( FunctionThread const &thread );
    FunctionThread& operator = ( FunctionThread const &thread );
    ~FunctionThread();

  private:
    Function mFunction;
    void* run();
};

template <typename ClassType>
  class tamias::MethodThread : public Thread {
    public:
      typedef void (ClassType::* Function)(void);

    public:
      MethodThread( ClassType &object, Function function );
      MethodThread( ClassType *object, Function function );
      MethodThread( MethodThread const &thread );
      MethodThread& operator = ( MethodThread const &thread );
      ~MethodThread();

    private:
      ClassType *mObject;
      Function mFunction;

      virtual void* run();
  };

#include "thread_implementation.h"

