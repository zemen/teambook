/*
 * This file [utilities/tamias_cpp2html.cpp] is part of the “libtamias” library
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

#include "../../include/basic/byte_array.h"
#include "../../include/basic/string.h"
#include "../../include/basic/types.h"
#include "../../include/main/set.h"
#include "../../include/main/tree_rbst.h"
#include "../../include/io/file.h"
#include "../../include/io/printer.h"
#include "../../include/io/scanner.h"

using tamias::sizetype;
using tamias::ByteArray;
using tamias::File;
using tamias::Printer;
using tamias::RBSTree;
using tamias::Scanner;
using tamias::Set;
using tamias::String;

void usage()
{
  Printer stdout(File::stdout);
  stdout.println("usage: libtamias_cpp2html [-o <output-file>] [<input-file>]");
}

enum State
{
  ST_NORMAL,
  ST_CHARACTER,
  ST_DIRECTIVE,
  ST_STRING,
  ST_IDENTIFIER,
  ST_NUMBER,
  ST_COMMENT0,
  ST_COMMENT1,
  ST_COMMENT2
};

// TODO: write it better

int main( int argc, char *argv[] )
{
  Printer stdout(File::stdout);
  Printer stderr(File::stderr);

  ByteArray inputFileName, outputFileName;
  bool isInputFileName = false, isOutputFileName = false;
  bool wasDoubleDash = false, isExit = false;

  for (int i = 1; i < argc; i++)
    if (argv[i][0] == '-' && !wasDoubleDash)
      if (argv[i][1] == '-')
      {
        stderr.printf("libtamias_cpp2html: unknown switch: %s\n") << argv[i], isExit = true;
      }
      else
      {
        for (int j = 1; argv[i][j]; j++)
          if (argv[i][j] == 'h')
            usage(), isExit = true;
          else if (argv[i][j] == 'o')
          {
            isOutputFileName = true;
            if (argv[i][++j])
              outputFileName = argv[i] + j;
            else
              outputFileName = argv[++i];
            break;
          }
          else
            stderr.printf("libtamias_cpp2html: unknown switch: -%c\n") << argv[i][j], isExit = true;
      }
    else if (isInputFileName == false)
      isInputFileName = true, inputFileName = argv[i];
    else
      stderr.printf("libtamias_cpp2html: file ignored: %s\n") << argv[i];

  if (isExit)
    return 0;

  File inputFile = File::openRead(inputFileName);
  File outputFile = File::openWrite(outputFileName);
//   Scanner input = Scanner(inputFile);
  Printer output = Printer(outputFile);

  output.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
  output.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\""
                 " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
  output.println("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">");
  output.println("<head>");
  output.println("  <title>" + inputFileName + "</title>");
  output.println("</head>");
  output.println("<body>");
  output.println("<pre>");
  Set <RBSTree, ByteArray> reserved, type;
  reserved.insert("asm");
  reserved.insert("auto");
  reserved.insert("break");
  reserved.insert("case");
  reserved.insert("catch");
  reserved.insert("class");
  reserved.insert("const");
  reserved.insert("const_cast");
  reserved.insert("continue");
  reserved.insert("default");
  reserved.insert("delete");
  reserved.insert("do");
  reserved.insert("dynamic_cast");
  reserved.insert("else");
  reserved.insert("enum");
  reserved.insert("explicit");
  reserved.insert("extern");
  reserved.insert("ealse");//??
  reserved.insert("false");
  reserved.insert("for");
  reserved.insert("friend");
  reserved.insert("goto");
  reserved.insert("if");
  reserved.insert("inline");
  reserved.insert("mutable");
  reserved.insert("namespace");
  reserved.insert("new");
  reserved.insert("operator");
  reserved.insert("private");
  reserved.insert("protected");
  reserved.insert("public");
  reserved.insert("register");
  reserved.insert("reinterpret_cast");
  reserved.insert("return");
  reserved.insert("sizeof");
  reserved.insert("static");
  reserved.insert("static_cast");
  reserved.insert("struct");
  reserved.insert("switch");
  reserved.insert("template");
  reserved.insert("this");
  reserved.insert("throw");
  reserved.insert("true");
  reserved.insert("try");
  reserved.insert("typedef");
  reserved.insert("typeid");
  reserved.insert("typename");
  reserved.insert("union");
  reserved.insert("using");
  reserved.insert("virual");
  reserved.insert("volatile");
  reserved.insert("while");

  type.insert("bool");
  type.insert("char");
  type.insert("chartype");
  type.insert("double");
  type.insert("float");
  type.insert("int");
  type.insert("inttype16");
  type.insert("inttype32");
  type.insert("inttype64");
  type.insert("inttype8");
  type.insert("long");
  type.insert("short");
  type.insert("signed");
  type.insert("sizetype");
  type.insert("uinttype16");
  type.insert("uinttype32");
  type.insert("uinttype64");
  type.insert("uinttype8");
  type.insert("unsigned");
  type.insert("void");
  type.insert("wchar_t");
  State state = ST_NORMAL;
  int c = -1;
  sizetype position = 0;
  ByteArray identifier = "", comment = "";
  bool stringBackslash = false;
  String inputData = String(inputFile.read());
  while (true)
  {
    int lastc = c;
//     c = input.nextByte();
    c = position < inputData.length() ? inputData[position++] : -1;
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9')) && state == ST_IDENTIFIER)
    {
      if (reserved.count(identifier))
        output.print("<b>" + identifier + "</b>");
      else if (type.count(identifier))
        output.print("<font color=\"darkred\">" + identifier + "</font>");
      else
        output.print(identifier);
      identifier = "";
      state = ST_NORMAL;
    }
    if (state == ST_COMMENT0)
    {
      comment += c;
      if (comment == "//")
        output.print("<font color=\"gray\">"), state = ST_COMMENT1;
      else if (comment == "/*")
        output.print("<font color=\"gray\">"), state = ST_COMMENT2;
      else
        state = ST_NORMAL;
      output.print("/");
      comment = "";
    }
    if (!(c >= '0' && c <= '9') && state == ST_NUMBER)
      output.print("</font>"), state = ST_NORMAL;
    if (c == '\n' && state == ST_DIRECTIVE)
      output.print("</font>"), state = ST_NORMAL;
    if (c == '\n' && state == ST_COMMENT1)
      output.print("</font>"), state = ST_NORMAL;
    if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') && state == ST_NORMAL)
      state = ST_IDENTIFIER;
    if (c == '/' && state == ST_NORMAL)
      state = ST_COMMENT0;
    if (c >= '0' && c <= '9' && state == ST_NORMAL)
      output.print("<font color=\"darkblue\">"), state = ST_NUMBER;
    if (c == '#' && state == ST_NORMAL)
      output.print("<font color=\"green\">"), state = ST_DIRECTIVE;
    if (c == -1)
      break;
    if (c == '<')
      output.print("&lt;");
    else if (c == '>')
      output.print("&gt;");
    else if (c == '&')
      output.print("&amp;");
    /* No nested comments!// */
    else if (c == '/' && lastc == '*' && state == ST_COMMENT2)
      output.print("/</font>"), state = ST_NORMAL;
    else if (c == '\"')
    {
      if (state == ST_NORMAL)
        output.print("<font color=\"red\">&quot;"), state = ST_STRING;
      else if (state == ST_STRING && !stringBackslash)
        output.print("&quot;</font>"), state = ST_NORMAL;
      else
        output.print("&quot;");
    }
    else if (c == '\'')
    {
      if (state == ST_NORMAL)
        output.print("<font color=\"magenta\">'"), state = ST_CHARACTER;
      else if (state == ST_CHARACTER && !stringBackslash)
        output.print("'</font>"), state = ST_NORMAL;
      else
        output.print("'");
    }
    else if (state == ST_IDENTIFIER)
      identifier += c;
    else if (state == ST_COMMENT0)
      comment += c;
    else
      output.print(c);
    if ((state == ST_STRING || state == ST_CHARACTER) && c == '\\' && !stringBackslash)
      stringBackslash = true;
    else if ((state == ST_STRING || state == ST_CHARACTER) && stringBackslash)
      stringBackslash = false;
  }
  output.println("</pre>");
  output.println("</body>");
  output.println("</html>\n");

  inputFile.close();
  output.close();

  return 0;
}
