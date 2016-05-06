/*
 * This file [main/xml.h] is part of the “libtamias” library
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

#ifndef _libtamias_main_xml_h_
#define _libtamias_main_xml_h_

#include "../basic/exception.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../io/iodevice.h"
#include "../io/printer.h"
#include "../io/scanner.h"
#include "../main/map.h"
#include "../main/tree_rbst.h"
#include "../main/vector.h"

namespace tamias
{
  class XMLData;
  class XMLEntity;

  class XMLParseException : public Exception
  {
    public:
      XMLParseException();
      XMLParseException( const XMLParseException &exception );
      ~XMLParseException();
      XMLParseException& operator=( const XMLParseException &exception );
      const char* type() const;
      const String& report() const;
  };

  class XMLTag // nya?
  {
    public:
      enum TagType
      {
        TAG_ERROR, TAG_OPEN, TAG_CLOSE, TAG_EMPTY,
        TAG_PI, TAG_SPECIAL
      };
    private:
      String tagName;
      TagType tagType;
      Map <RBSTree, String, String> tagParameters;
    public:
      XMLTag();
      XMLTag( const XMLTag &tag );
      ~XMLTag();
      XMLTag& operator = ( const XMLTag &tag );

      const String& name() const;
      String& name();
      void setName( const String &name );
      TagType type() const;
      TagType& type();
      void setType( TagType type );
      const Map <RBSTree, String, String>& parameters() const;
      Map <RBSTree, String, String>& parameters();
      void setParameter( const String &parameterName, const String &parameterValue );
      void setParameters( const Map <RBSTree, String, String> &parameters );
  };

  class XMLParser
  {
    private:
      Scanner *scanner;
      int nextByte;
      void readByte();
      void skipSpace();
      bool isNameChar( chartype ch );
      String readToken();
    public:
      XMLParser( Scanner &scanner );
      XMLParser( const XMLParser &parser ); //  [TODO] const?
      ~XMLParser();
      XMLParser& operator = ( const XMLParser &parser );

      String getText();
      XMLTag nextTag();
  };

  class XMLEntity
  {
    private:
      String xmlName;
      Map <RBSTree, String, String> xmlParameters;
      String xmlText;
      Vector <XMLEntity> xmlEntities;
      void entityOutput( Printer &printer, int indentation );
      void entityRead( XMLParser &parser, const XMLTag &tag );
    public:
      XMLEntity();
      XMLEntity( const XMLEntity &entity );
      XMLEntity( const String &newName );
      ~XMLEntity();

      XMLEntity& operator = ( const XMLEntity &entity );

      const String& name() const;
      const String& getParameter( const String &parameterName ) const;
      String& getParameter( const String &parameterName );
      const Map <RBSTree, String, String>& parameters() const;
      const String& text() const;
      const XMLEntity getEntity( sizetype index ) const;
      const Vector <XMLEntity>& entities() const;
      String& name();
      Map <RBSTree, String, String>& parameters();
      String& text();
      Vector <XMLEntity>& entities();
      void setName( const String &newName );
      void setParameter( const String &parameterName, const String &parameterValue );
      void setParameters( const Map <RBSTree, String, String> &parameters );
      void setText( const String &newText );
      void setEntity( sizetype index, const XMLEntity &newEntity );
      void addEntity( const XMLEntity &newEntity );
      void setEntities( const Vector <XMLEntity> newEntities );

    friend class XMLData;
  };

  class XMLData
  {
    private:
      String xmlVersion;
      String xmlEncoding;
      XMLEntity xmlRootEntity;
    public:
      XMLData();
      XMLData( const XMLData &data );
      ~XMLData();

      XMLData& operator = ( const XMLData &data );

      static XMLData read( IODevice &file );
      void write( IODevice &file );

      const String& version() const;
      const String& encoding() const;
      const XMLEntity& rootEntity() const;
      String& version();
      String& encoding();
      XMLEntity& rootEntity();
      void setVersion( const String &newVersion );
      void setEncoding( const String &newEncoding );
      void setRootEntity( const XMLEntity &newRootEntity );
  };
}

#endif /* _libtamias_main_xml_h_ */
