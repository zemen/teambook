#include "../../include/wtf/web_captcha.h"

using tamias::ByteArray;
using tamias::String;
using tamias::wtf::web::Captcha;

Captcha::Captcha( const ByteArray &binaryName, const ByteArray &path )
       : mBinaryName(binaryName), mPath(path), mKey(), mValue()
{
}

Captcha::Captcha( const Captcha &captcha ) : mBinaryName(captcha.mBinaryName), mPath(captcha.mPath),
                                             mKey(captcha.mKey), mValue(captcha.mValue)
{
}

Captcha& Captcha::operator = ( const Captcha &captcha )
{
  mBinaryName = captcha.mBinaryName;
  mPath = captcha.mPath;
  mKey = captcha.mKey;
  mValue = captcha.mValue;
  return *this;
}

Captcha::~Captcha()
{
}

String Captcha::generate( const String &key )
{
  using tamias::chartype;
  ByteArray fileName = "captcha_" + key.toUtf8() + ".png";
  String captcha = "";
  for (int i = 0; i < 6; i++)
    captcha += (chartype)('0' + rand() % 10);
  ByteArray command = mBinaryName + ' ' + captcha.toUtf8() + ' ' + mPath + '/' + fileName;
  if (system(command.cString()) != 0)
    throw tamias::DefaultException();
  mKey = key;
  mValue = captcha;
  return fileName;
}

const String& Captcha::key() const
{
  return mKey;
}

const String& Captcha::value() const
{
  return mValue;
}

