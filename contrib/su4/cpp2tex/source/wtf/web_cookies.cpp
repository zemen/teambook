#include "../../include/wtf/web_cookies.h"

using tamias::sizetype;
using tamias::Date;
using tamias::String;
using tamias::Time;
//using tamias::Printable;
using tamias::wtf::web::Cookie;
using tamias::wtf::web::utilities::encodeHTTPParameter;

Cookie::Cookie() : mName(""), mValue(""), mTimeoutType(TIMEOUT_NONE)
{
}

Cookie::Cookie( String newName, String newValue ) : mName(newName), mValue(newValue), mTimeoutType(TIMEOUT_NONE)
{
}

Cookie::Cookie( const Cookie &cookie ) : mName(cookie.mName), mValue(cookie.mValue), mTimeoutType(cookie.mTimeoutType),
                                         mTimeoutExpires(cookie.mTimeoutExpires), mTimeoutMaxAge(cookie.mTimeoutMaxAge)
{
}

Cookie& Cookie::operator = ( const Cookie &cookie )
{
  mName = cookie.mName;
  mValue = cookie.mValue;
  mTimeoutType = cookie.mTimeoutType;
  mTimeoutExpires = cookie.mTimeoutExpires;
  mTimeoutMaxAge = cookie.mTimeoutMaxAge;
  return *this;
}

Cookie::~Cookie()
{
}

String Cookie::name() const
{
  return mName;
}

String Cookie::value() const
{
  return mValue;
}

void Cookie::setExpires( const Date &expires )
{
  mTimeoutType = TIMEOUT_EXPIRES;
  mTimeoutExpires = expires;
}

void Cookie::setMaxAge( const Time &maxAge )
{
  mTimeoutType = TIMEOUT_MAXAGE;
  mTimeoutMaxAge = maxAge;
}

String Cookie::output() const
{
  /* It is user's problem if cookieName isn't a token from rfc2068 */
  String result = "Set-Cookie: " + mName + '=' + encodeHTTPParameter(mValue);
  switch (mTimeoutType)
  {
    case TIMEOUT_EXPIRES: result += "; Expires=\"" + mTimeoutExpires.format("\"r\"") + "\""; break;
    case TIMEOUT_MAXAGE: result += "; Max-Age=" + Printer::intToString((long long)mTimeoutMaxAge.toSeconds()); break;
    default:;
  }
  return result;
}

