/*
 * This file [basic/abstract_data.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_abstract_data_
#define _libtamias_basic_abstract_data_

#include <cstring>
#include <cstdlib>
#include "../basic/generic_exception.h"
#include "../basic/types.h"
#include "../basic/utilities.h"

namespace tamias
{
  namespace hidden
  {
    /* provides distensible data block */
    class AbstractData
    {
      protected:
        static const tamias::sizetype MAXSIZE = 0x80000000;
        void *data;
        tamias::sizetype dataSize;
      public:
        AbstractData( tamias::sizetype initialSize = 0 );
        AbstractData( const AbstractData &data );
        AbstractData& operator = ( const AbstractData &data );
        virtual ~AbstractData( void );

        void autoReserve( sizetype size );   /* Allocates between size and size*4 bytes */
        void autoReserveUp( sizetype size ); /* Allocates minimum size bytes */
        void manualReserve( sizetype size ); /* Allocates exactly size bytes */
        void* getData() const;
    };
  }
}

#endif /* _libtamias_basic_abstract_data_ */

