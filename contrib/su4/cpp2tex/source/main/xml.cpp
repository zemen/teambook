/*
 * This file [main/xml.cpp] is part of the “libtamias” library
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

#include "../../include/main/xml.h"

using tamias::chartype;
using tamias::Map;
using tamias::Printer;
using tamias::RBSTree;
using tamias::Scanner;
using tamias::String;
using tamias::Vector;
using tamias::XMLData;
using tamias::XMLEntity;
using tamias::XMLParseException;
using tamias::XMLParser;
using tamias::XMLTag;

char xmlParseExceptionType[] = "XMLParseException";
tamias::String xmlParseExceptionMessage = "fatal error in parsing XML";

XMLParseException::XMLParseException() : Exception()
{
}

XMLParseException::XMLParseException( const XMLParseException& ) : Exception()
{
}

XMLParseException::~XMLParseException()
{
}

XMLParseException& XMLParseException::operator = ( const XMLParseException &exception )
{
  Exception::operator = (exception);
  return *this;
}

const char* XMLParseException::type() const
{
  return xmlParseExceptionType;
}

const tamias::String& XMLParseException::report() const
{
  return xmlParseExceptionMessage;
}

XMLTag::XMLTag() : tagName(""), tagType(TAG_ERROR)
{
}

XMLTag::XMLTag( const XMLTag &tag ) : tagName(tag.tagName), tagType(tag.tagType), tagParameters(tag.tagParameters)
{
}

XMLTag::~XMLTag()
{
}

XMLTag& XMLTag::operator = ( const XMLTag &tag )
{
  tagName = tag.tagName;
  tagType = tag.tagType;
  tagParameters = tag.tagParameters;
  return *this;
}

const String& XMLTag::name() const
{
  return tagName;
}

String& XMLTag::name()
{
  return tagName;
}

void XMLTag::setName( const String &name )
{
  tagName = name;
}

XMLTag::TagType XMLTag::type() const
{
  return tagType;
}

XMLTag::TagType& XMLTag::type()
{
  return tagType;
}

void XMLTag::setType( TagType type )
{
  tagType = type;
}

const Map <RBSTree, String, String>& XMLTag::parameters() const
{
  return tagParameters;
}

Map <RBSTree, String, String>& XMLTag::parameters()
{
  return tagParameters;
}

void XMLTag::setParameter( const String &name, const String &value )
{
  tagParameters[name] = value;
}

void XMLTag::setParameters( const Map <RBSTree, String, String> &parameters )
{
  tagParameters = parameters;
}

void XMLParser::readByte()
{
  nextByte = scanner->nextByte();
}

void XMLParser::skipSpace()
{
  while (nextByte == ' ' || nextByte == '\n' || nextByte == '\t' || nextByte == '\r')
    readByte();
}

bool XMLParser::isNameChar( chartype ch )
{
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
          ch == '.' || ch == '-' || ch == '_' || ch == ':';
}

String XMLParser::readToken()
{
  skipSpace();
  String result = "";
  while (isNameChar(nextByte))
    result += (char)nextByte, readByte();
  skipSpace();
  return result;
}

XMLParser::XMLParser( Scanner &newScanner ) : scanner(&newScanner)
{
  readByte();
}

XMLParser::XMLParser( const XMLParser &parser ) : scanner(parser.scanner), nextByte(parser.nextByte)
{
}

XMLParser::~XMLParser()
{
}

XMLParser& XMLParser::operator = ( const XMLParser &parser )
{
  scanner = parser.scanner;
  nextByte = parser.nextByte;
  return *this;
}

String XMLParser::getText()
{
  ByteArray result;
  while (nextByte != -1 && nextByte != '<')
  {
    result += (char)nextByte;
    readByte();
  }
  return String::fromUtf8(result);
}

XMLTag XMLParser::nextTag()
{
  skipSpace();
  if (nextByte != '<') return XMLTag();
  readByte(), skipSpace();
  XMLTag tag;
  if (nextByte == '/')
    tag.setType(XMLTag::TAG_CLOSE), readByte();
  else if (nextByte == '?')
    tag.setType(XMLTag::TAG_PI), readByte();
  else
    tag.setType(XMLTag::TAG_OPEN);
  tag.setName(readToken());
  if (nextByte == '/')
    tag.setType(XMLTag::TAG_EMPTY), readByte(), skipSpace();
  while (nextByte != '>')
  {
    if (nextByte == -1 || (tag.type() != XMLTag::TAG_OPEN && tag.type() != XMLTag::TAG_PI))
      return XMLTag();
    String parameterName = readToken();
    skipSpace();
    if (nextByte != '=')
      return XMLTag();
    readByte(), skipSpace();
    if (nextByte != '\"' && nextByte != '\'')
      return XMLTag();
    char quot = nextByte;
    readByte();
    ByteArray parameterValue;
    while (nextByte != quot)
    {
      parameterValue += (char)nextByte;
      readByte();
      if (nextByte == -1)
        return XMLTag();
    }
    readByte(), skipSpace();
    tag.setParameter(parameterName, String::fromUtf8(parameterValue));
    if (tag.type() == XMLTag::TAG_PI && nextByte == '?')
    {
      readByte();
      if (nextByte != '>')
        return XMLTag();
      break;
    }
  }
  readByte();
  return tag;
}

void XMLEntity::entityOutput( Printer &printer, int indentation )
{
  printer.printf("%*s<%s") << indentation << "" << xmlName;
  for (Map<RBSTree, String, String>::Iterator it = xmlParameters.begin(); it != xmlParameters.end(); it++)
    printer.printf(" %s=\"%s\"") << it->first << it->second;
  printer.print(">");
  bool twoLines = false;
  if (xmlEntities.size() > 0)
    printer.println(""), twoLines = true;
  for (sizetype i = 0; i < xmlEntities.size(); i++)
    xmlEntities[i].entityOutput(printer, indentation + 2);
  if (xmlText != "")
  {
    bool isLine = false, lastLine = false;
    for (sizetype i = 0; i < xmlText.length(); i++)
      if (xmlText[i] == '\n')
        isLine = true, lastLine = true, twoLines = true;
      else
        lastLine = false;
    if (isLine)
      printer.printf("%*s%s") << indentation + 2 << "" << xmlText;
    else
      printer.printf("%s") << xmlText;
    if (isLine && !lastLine)
      printer.println("");
  }
  if (twoLines)
    printer.printf("%*s") << indentation << "";
  printer.printf("</%s>\n") << xmlName;
}

void XMLEntity::entityRead( XMLParser &parser, const XMLTag &tag )
{
  if (tag.type() != XMLTag::TAG_OPEN && tag.type() != XMLTag::TAG_EMPTY) throw XMLParseException();
  xmlName = tag.name();
  xmlParameters = tag.parameters();
  xmlText = "";
  if (tag.type() == XMLTag::TAG_EMPTY)
    return;
  while (true)
  {
    xmlText += parser.getText();
    XMLTag nextTag = parser.nextTag();
    if (nextTag.type() == XMLTag::TAG_CLOSE)
    {
      if (nextTag.name() != xmlName) throw XMLParseException();
      return;
    }
    XMLEntity newEntity;
    newEntity.entityRead(parser, nextTag);
    xmlEntities.pushBack(newEntity);
  }
}

XMLEntity::XMLEntity()
{
}

XMLEntity::XMLEntity( const XMLEntity &entity ) : xmlName(entity.xmlName), xmlParameters(entity.xmlParameters),
                                                  xmlText(entity.xmlText), xmlEntities(entity.xmlEntities)
{
}

XMLEntity::XMLEntity( const String &newName ) : xmlName(newName)
{
}

XMLEntity::~XMLEntity()
{
}

XMLEntity& XMLEntity::operator = ( const XMLEntity &entity )
{
  xmlName = entity.xmlName;
  xmlParameters = entity.xmlParameters;
  xmlText = entity.xmlText;
  xmlEntities = entity.xmlEntities;
  return *this;
}

const String& XMLEntity::name() const
{
  return xmlName;
}

const String& XMLEntity::text() const
{
  return xmlText;
}

const String& XMLEntity::getParameter( const String &name ) const
{
  return xmlParameters[name];
}

String& XMLEntity::getParameter( const String &name )
{
  return xmlParameters[name];
}

const Map<RBSTree, String, String>& XMLEntity::parameters() const
{
  return xmlParameters;
}

const Vector <XMLEntity>& XMLEntity::entities() const
{
  return xmlEntities;
}

String& XMLEntity::name()
{
  return xmlName;
}

String& XMLEntity::text()
{
  return xmlText;
}

Map<RBSTree, String, String>& XMLEntity::parameters()
{
  return xmlParameters;
}

Vector <XMLEntity>& XMLEntity::entities()
{
  return xmlEntities;
}

void XMLEntity::setParameter( const String &name, const String &value )
{
  xmlParameters[name] = value;
}

void XMLEntity::setText( const String &newText )
{
  xmlText = newText;
}

void XMLEntity::addEntity( const XMLEntity &entity )
{
  xmlEntities.pushBack(entity);
}

XMLData::XMLData() : xmlVersion("1.0"), xmlEncoding("UTF-8")
{
}

XMLData::XMLData( const XMLData &data ) : xmlVersion(data.xmlVersion), xmlEncoding(data.xmlEncoding),
                                          xmlRootEntity(data.xmlRootEntity)
{
}

XMLData::~XMLData()
{
}

XMLData XMLData::read( IODevice &file )
{
  XMLData data;
  Scanner scanner(file);
  XMLParser parser(scanner);
  XMLTag tag = parser.nextTag();
  if (tag.type() != XMLTag::TAG_PI) throw XMLParseException();
  if (tag.name() != "xml") throw XMLParseException();
  if (tag.parameters()["version"] != "1.0") throw XMLParseException();
  if (tag.parameters()["encoding"] != "UTF-8") throw XMLParseException();
  data.rootEntity().entityRead(parser, parser.nextTag());
  return data;
}

void XMLData::write( IODevice &file )
{
  Printer printer(file);
  printer.printf("<?xml version=\"%s\" encoding=\"%s\"?>\n") << xmlVersion << xmlEncoding;
  xmlRootEntity.entityOutput(printer, 0);
}

const XMLEntity& XMLData::rootEntity() const
{
  return xmlRootEntity;
}

XMLEntity& XMLData::rootEntity()
{
  return xmlRootEntity;
}

void XMLData::setRootEntity( const XMLEntity &newRootEntity )
{
  xmlRootEntity = newRootEntity;
}
