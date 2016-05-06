/*
 * This file [basic/thread.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_thread_h_
#define _libtamias_basic_thread_h_

#include <pthread.h>
#include <time.h>
#include "../basic/time.h"

namespace tamias
{
  class Thread
  {
    private:
      pthread_t threadHandle;
    protected:
      virtual void* run();
    public:
      Thread();
      Thread( const Thread &thread );
      Thread& operator = ( const Thread &thread );
      virtual ~Thread();

      void create();
      void cancel();
      static void sleep( const Time &time );
    friend void* threadRun( void* thread );
  };

  class FunctionThread : public Thread
  {
    public:
      typedef void(*Function)(void);
    private:
      Function threadFunction;
      virtual void* run();
    public:
      FunctionThread( Function function );
      FunctionThread( const FunctionThread &thread );
      FunctionThread& operator = ( const FunctionThread &thread );
      virtual ~FunctionThread();
  };

  template <typename ClassType>
    class MethodThread : public Thread
    {
      public:
        typedef void (ClassType::* Function)(void);
      private:
        ClassType *threadObject;
        Function threadFunction;
        virtual void* run();
      public:
        MethodThread( ClassType &object, Function function );
        MethodThread( ClassType *object, Function function );
        MethodThread( const MethodThread &thread );
        MethodThread& operator = ( const MethodThread &thread );
        virtual ~MethodThread();
    };
}

template <typename ClassType>
  void* tamias::MethodThread<ClassType>::run()
  {
    (threadObject->*threadFunction)();
    return NULL;
  }

template <typename ClassType>
  tamias::MethodThread<ClassType>::MethodThread( ClassType &object, Function function )
                                 : Thread(), threadObject(&object), threadFunction(function)
  {
  }

template <typename ClassType>
  tamias::MethodThread<ClassType>::MethodThread( ClassType *object, Function function )
                                 : Thread(), threadObject(object), threadFunction(function)
  {
  }

template <typename ClassType>
  tamias::MethodThread<ClassType>::MethodThread( const MethodThread &thread )
                                 : Thread(thread), threadObject(thread.threadObject), threadFunction(thread.threadFunction)
  {
  }

template <typename ClassType>
  tamias::MethodThread<ClassType>& tamias::MethodThread<ClassType>::operator = ( const MethodThread &thread )
  {
    Thread::operator = (thread);
    threadFunction = thread.threadFunction;
    threadObject = thread.threadObject;
    return *this;
  }

template <typename ClassType>
  tamias::MethodThread<ClassType>::~MethodThread()
  {
  }

#endif // _libtamias_basic_thread_h_

