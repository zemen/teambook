#pragma once

#include "../basic/byte_array.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../io/printer.h"
#include "../io/scanner.h"
#include "../main/map.h"
#include "../main/tree_rbst.h"
#include "../main/vector.h"
#include "../wtf/utilities.h"
#include "../wtf/web_cookies.h"
#include "../wtf/web_utilities.h"

namespace tamias
{
  namespace wtf
  {
    namespace web
    {
      class HttpResponse
      {
        public:
          HttpResponse();
          HttpResponse( const HttpResponse &response );
          HttpResponse& operator = ( const HttpResponse &response );
          ~HttpResponse();
    
          void addCookie( const Cookie &cookie );
          void setContent( const String &content );
    
          void output( Printer &out );
        private:
          Vector <Cookie> mCookies;
          String mContent;
      };
    
      class HttpRequest
      {
        public:
          HttpRequest();
          HttpRequest( int argc, char **argv, char **env, Scanner &input );
          HttpRequest( const HttpRequest &request );
          HttpRequest& operator = ( const HttpRequest &request );
          ~HttpRequest();
    
          const Map <RBSTree, String, String>& cookies() const;
          const Map <RBSTree, String, String>& enviropment() const;
          const Map <RBSTree, String, String>& getParameters() const;
          const Map <RBSTree, String, String>& postParameters() const;
        private:
          Map <RBSTree, String, String> mCookies; // TODO: Map -> HashMap
          Map <RBSTree, String, String> mEnviropment;
          Map <RBSTree, String, String> mGetParameters;
          Map <RBSTree, String, String> mPostParameters;
      };
    
      class HttpServer
      {
        public:
          HttpServer();
          HttpServer( const HttpServer &server );
          HttpServer& operator = ( const HttpServer &server );
          virtual ~HttpServer();
    
          void make( int argc, char **argv, char **env, Scanner &input, Printer &out );
        protected:
          virtual HttpResponse action( const HttpRequest &request ) = 0;
      };
    }
  }
}

