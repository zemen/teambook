#include "../../include/wtf/web_server.h"

using tamias::sizetype;
using tamias::ByteArray;
using tamias::Map;
using tamias::Printer;
using tamias::RBSTree;
using tamias::Scanner;
using tamias::String;
using tamias::Vector;
using tamias::wtf::utilities::splitString;
using tamias::wtf::web::HttpResponse;
using tamias::wtf::web::HttpRequest;
using tamias::wtf::web::HttpServer;
using tamias::wtf::web::utilities::decodeURIString;

HttpResponse::HttpResponse()
{
}

HttpResponse::HttpResponse( const HttpResponse &response ) : mCookies(response.mCookies), mContent(response.mContent)
{
}

HttpResponse& HttpResponse::operator = ( const HttpResponse &response )
{
  mCookies = response.mCookies;
  mContent = response.mContent;
  return *this;
}

HttpResponse::~HttpResponse()
{
}

void HttpResponse::addCookie( const Cookie &cookie )
{
  mCookies.pushBack(cookie);
}

void HttpResponse::setContent( const String &content )
{
  mContent = content;
}

void HttpResponse::output( Printer &out )
{
  for (sizetype i = 0; i < mCookies.size(); i++)
  {
    String cookie = mCookies[i].output();
    out._printf("%$S\n", &cookie);
  }
  out.println("Content-type: text/html");
  out.println("");
  out._printf("%$S\n", &mContent);
}

HttpRequest::HttpRequest( int argc, char **argv, char **env, Scanner &input )
{
  for (sizetype i = 0; env[i]; i++)
  {
    String variable = env[i];
    sizetype eq = variable.find('=');
    mEnviropment[variable.subString(0, eq)] = variable.subString(eq + 1, variable.length() - 1 - eq);
  }

  String getQuery = mEnviropment["QUERY_STRING"];
  Vector <String> queryParameters = splitString(getQuery, '&');
  for (sizetype i = 0; i < queryParameters.size(); i++)
  {
    sizetype eq = queryParameters[i].find('=');
    mGetParameters[queryParameters[i].subString(0, eq)] =
      decodeURIString(queryParameters[i].subString(eq + 1, queryParameters[i].length() - 1 - eq).toUtf8());
  }

  String cookie = mEnviropment["HTTP_COOKIE"];
  Vector <String> cookies = splitString(cookie, "; ");
  for (sizetype i = 0; i < cookies.size(); i++)
  {
    sizetype eq = cookies[i].find('=');
    mCookies[cookies[i].subString(0, eq)] = decodeURIString(cookies[i].subString(eq + 1, cookies[i].length() - 1 - eq).toUtf8());
  }

  int c;
  ByteArray t = "";
  while ((c = input.nextByte()) != -1)
    if (c == '&')
    {
      int j = t.find('=');
      if (j != (int)t.length())
        mPostParameters[t.subString(0, j)] = decodeURIString(t.subString(j + 1, t.length() - 1 - j));
      t = "";
    }
    else if (c < 0 || c > 32)
      t += c;
  if (t != "")
  {
    int j = t.find('=');
    if (j != (int)t.length())
      mPostParameters[t.subString(0, j)] = decodeURIString(t.subString(j + 1, t.length() - 1 - j));
  }
}

HttpRequest::HttpRequest()
{
}

HttpRequest::HttpRequest( const HttpRequest &request ) : mCookies(request.mCookies),
                                                         mEnviropment(request.mEnviropment),
                                                         mGetParameters(request.mGetParameters),
                                                         mPostParameters(request.mPostParameters)
{
}

HttpRequest& HttpRequest::operator = ( const HttpRequest &request )
{
  mCookies = request.mCookies;
  mEnviropment = request.mEnviropment;
  mGetParameters = request.mGetParameters;
  mPostParameters = request.mPostParameters;
  return *this;
}

HttpRequest::~HttpRequest()
{
}

const Map<RBSTree, String, String>& HttpRequest::enviropment() const
{
  return mEnviropment;
}

const Map<RBSTree, String, String>& HttpRequest::cookies() const
{
  return mCookies;
}

const Map<RBSTree, String, String>& HttpRequest::getParameters() const
{
  return mGetParameters;
}

const Map<RBSTree, String, String>& HttpRequest::postParameters() const
{
  return mPostParameters;
}

HttpServer::HttpServer()
{
}

HttpServer::HttpServer( const HttpServer& )
{
}

HttpServer& HttpServer::operator = ( const HttpServer& )
{
  return *this;
}

HttpServer::~HttpServer()
{
}

void HttpServer::make( int argc, char **argv, char **env, Scanner &input, Printer &out )
{
  HttpResponse response = action(HttpRequest(argc, argv, env, input));
  response.output(out);
}

