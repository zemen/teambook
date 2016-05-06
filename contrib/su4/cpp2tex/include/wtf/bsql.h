/*
 * libtamias/wtf/bsql.h — some improvements for sql api
 */

#pragma once

#include <cstdarg> // Hmmm... Wtf?
#include "../basic/exception.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../data/pair.h"
#include "../sql/connection.h"
#include "../sql/driver.h"
#include "../sql/result.h"
#include "../main/vector.h"
#include "../wtf/utilities.h"

/*
 * Format specification:
 *   %s — string, argument must be a pointer to tamias::String
 *   %d — 32-bit signed integer, argument must be an inttype32
 *   %u — 32-bit unsigned integer, argument must be an uinttype32
 *   %lld — 64-bit signed integer, argument must be an inttype64
 *   %llu — 64-bit unsigned integer, argument must be an inttype64
 * only %s & %u are implemented now
 */

namespace tamias
{
  namespace wtf
  {
    class BSqlConnection : public tamias::sql::Connection
    {
      public:
        enum LockType
        {
          LOCKTABLE_READ, LOCKTABLE_WRITE
        };
        BSqlConnection( tamias::sql::Driver *driver );
        BSqlConnection( const BSqlConnection &connection );
        ~BSqlConnection();
        BSqlConnection& operator = ( const BSqlConnection &connection );

        tamias::sql::Result query( const tamias::String &queryString, ... );
        void lockTables( const Vector <Pair <String, LockType> > &tables );
        void unlockTables();
        sizetype nextId( const String &tableName, const String &fieldName );
      private:
        String quoteString( const String &source ) const;
    };
  }
}

