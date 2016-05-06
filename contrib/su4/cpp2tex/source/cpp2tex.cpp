/*
 * Copyright (c) 2007-2008 Oleg Davydov, Yury Petrov
 * This file [utilities/burlib_cpp2html.cpp] is part of the burlib library
 * For copying information see license file or license.html
 * in burlib documentation. Briefly, GNU GPL version 2.0 or
 * version 3.0 can be used.
 */

#include "../include/basic/string.h"
#include "../include/main/set.h"
#include "../include/main/tree_rbst.h"
#include "../include/io/file.h"
#include "../include/io/printer.h"
#include "../include/io/scanner.h"

using tamias::File;
using tamias::Printer;
using tamias::RBSTree;
using tamias::Scanner;
using tamias::Set;
using tamias::String;

File file_stdout = File::stdout;
File file_stderr = File::stderr;
Printer stdout = Printer(file_stdout);
Printer stderr = Printer(file_stderr);
//Printer stdout = Printer(File::stdout);
//Printer stderr = Printer(File::stderr);

void usage()
{
  stdout._printf("usage: makedoc [-o <output-file>] [<input-file>]\n");
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

int main( int argc, char *argv[] )
{
  String inputFileName, outputFileName, screenName;
  bool isInputFileName = false;// isOutputFileName = false;
  bool wasDoubleDash = false, isExit = false;
  Printer stderr = Printer(File::stderr);
  
  for (int i = 1; i < argc; i++)
    if (argv[i][0] == '-' && !wasDoubleDash)
      if (argv[i][1] == '-')
      {
        stderr._printf("makedoc: unknown switch: %s\n", argv[i]), isExit = true;
      }
      else
      {
        for (int j = 1; argv[i][j]; j++)
          if (argv[i][j] == 'h')
            usage(), isExit = true;
          else if (argv[i][j] == 'o')
          {
            //isOutputFileName = true;
            if (argv[i][++j])
              outputFileName = argv[i] + j;
            else
              outputFileName = argv[++i];
            break;
          }
          else if (argv[i][j] == 's')
          {
            if (argv[i][++j])
              screenName = argv[i] + j;
            else
              screenName = argv[++i];
            break;
          }
          else
            stderr._printf("makedoc: unknown switch: -%c\n", argv[i][j]), isExit = true;
      }
    else if (isInputFileName == false)
      isInputFileName = true, inputFileName = argv[i];
    else
      stderr._printf("makedoc: file ignored: %s\n", argv[i]);

  if (isExit)
    return 0;

  File inputFile = File::openRead(inputFileName.toUtf8());
  File outputFile = File::openWrite(outputFileName.toUtf8());
  Scanner input = Scanner(inputFile);
  Printer output = Printer(outputFile);
//   FILE *inputFile = isInputFileName ? fopen(inputFileName.cStr(), "r") : stdin;
//   if (inputFile == NULL)
//     perror("makedoc");
//   FILE *outputFile = isOutputFileName ? fopen(outputFileName.cStr(), "w") : stdout;
//   if (outputFile == NULL)
//     perror("makedoc");

//   output.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
//   output.println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\""
//                  " \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
//   output.println("<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">");
//   output.println("<head>");
//   output.println("  <title>" + inputFileName + "</title>");
//   output.println("</head>");
//   output.println("<body>");
//   output.println("<pre>");
//  output.println("\\renewcommand{\\curfile}{" + screenName + "}");
  output.println("\\texttt{ ***" + screenName + " \\newline");
  Set <RBSTree, String> reserved, type;
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
  type.insert("ll");
  type.insert("ld");
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
  String identifier = "", comment = "";
  bool stringBackslash = false;
  bool oneFlag = true;
  bool mboxNext = false;
  bool mboxCur = false;
  int linePos = 0;
  output.print("{\\color[rgb]{0.8,0.8,0.8}");
  while (true)
  {
    int lastc = c;
    c = input.nextByte();
    if (c != ' ' && oneFlag)
      oneFlag = false, output.print("}");
    if (c == '\n')
      oneFlag = true, linePos = 0;
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9')) && state == ST_IDENTIFIER)
    {
      if (reserved.count(identifier))
        output.print("{\\color[rgb]{0.4,0.4,0.0}" + identifier + "}");
      else if (type.count(identifier))
        output.print("{\\color[rgb]{0.5,0.0,0.0}" + identifier + "}");
      else
        output.print(identifier);
      identifier = "";
      state = ST_NORMAL;
    }
    if (state == ST_COMMENT0)
    {
      comment += c;
      if (comment == "//")
        output.print("{\\color[rgb]{0.7,0.7,0.7}"), state = ST_COMMENT1;
      else if (comment == "/*")
        output.print("{\\color[rgb]{0.7,0.7,0.7}"), state = ST_COMMENT2;
      else
        state = ST_NORMAL;
      output.print("/");
      comment = "";
    }
    if (!((c >= '0' && c <= '9') || c == '.' || c == 'e') && state == ST_NUMBER)
      output.print("}"), state = ST_NORMAL;
    if (c == '\n' && state == ST_DIRECTIVE)
      output.print("}"), state = ST_NORMAL;
    if (c == '\n' && state == ST_COMMENT1)
      output.print("}"), state = ST_NORMAL;
    if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') && state == ST_NORMAL)
      state = ST_IDENTIFIER;
    if (c == '/' && state == ST_NORMAL)
      state = ST_COMMENT0;
    if (c >= '0' && c <= '9' && state == ST_NORMAL)
      output.print("{\\color[rgb]{0.0,0.0,0.5}"), state = ST_NUMBER;
    if (c == '#' && state == ST_NORMAL)
      output.print("{\\color[rgb]{0.0,0.5,0.0}\\"), state = ST_DIRECTIVE;
    if (c == -1)
      break;
    if (c == '{')
      output.print("\\{");
    else if (c == '}')
      output.print("\\}");
    else if (c == '^')
      output.print("\\symbol{94}");
    else if (c == '_' && state != ST_IDENTIFIER)
      output.print("\\_");
    else if (c == '&')
      output.print("\\&");
    else if (c == '-')
      output.print("{-}");
    /* No nested comments!// */
    else if (c == '/' && lastc == '*' && state == ST_COMMENT2)
      output.print("/}"), state = ST_NORMAL;
    else if (c == '\"')
    {
      if (state == ST_NORMAL)
        output.print("{\\color[rgb]{0.5,0.0,0.0}\""), state = ST_STRING;
      else if (state == ST_STRING && !stringBackslash)
        output.print("\\textquotedbl}"), state = ST_NORMAL;
      else
        output.print("\\textquotedbl ");
    }
    else if (c == '\'')
    {
      if (state == ST_NORMAL)
        output.print("{\\color[rgb]{0.5,0.0,0.5}\'"), state = ST_CHARACTER;
      else if (state == ST_CHARACTER && !stringBackslash)
        output.print("\'}"), state = ST_NORMAL;
      else
        output.print("'");
    }
    else if (state == ST_IDENTIFIER){
      if (c == '_')
      	identifier += "\\_";
      else
        identifier += c;
    }
    else if (state == ST_COMMENT0)
      comment += c;
    else if (c == '\n')
    {
      if (mboxCur) {
      	output.print("}");
      	mboxCur = false;
      }
      output.println("\\newline");
      if (mboxNext){
      	output.print("\\mbox{");
      	mboxNext = false;
      	mboxCur = true;
      }
            	
      output.print("{\\color[rgb]{0.8,0.8,0.8}");
    }
    else if (c == '<' || c == '>')
      output.printf(String(c) + "{}");
    else if (c == '%')
      output.print("\\%");
    else if (c == ' ' && oneFlag && linePos % 2 == 0)
      output.print("|");
    else if (c == '\\')
      output.print("$\\backslash$");
	else if (c == char(2)){
      // special for mboxnext;
      mboxNext = true;
    }
	else if (c == char(3)){
      // special for bf;
      output.printf("{\\color{red} ");
    }
	else if (c == char(4)){
      // special for bf end;
      output.printf("}");
    }
    else
      output.print(c);
    if ((state == ST_STRING || state == ST_CHARACTER) && c == '\\' && !stringBackslash)
      stringBackslash = true;
    else if ((state == ST_STRING || state == ST_CHARACTER) && stringBackslash)
      stringBackslash = false;
    if (c != '\n')
      linePos++;
  }
  output.println("}");
//  output.println("\\clearpage");
//   output.println("</pre>");
//   output.println("</body>");
//   output.println("</html>\n");

  input.close();
  output.close();

  return 0;
}
