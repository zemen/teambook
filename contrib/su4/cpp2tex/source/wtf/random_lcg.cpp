#include "../../include/wtf/random_lcg.h"

using tamias::wtf::LCGRandom;

LCGRandom::LCGRandom( uinttype64 seed ) : lcg(seed)
{
}

LCGRandom::~LCGRandom()
{
}

void LCGRandom::setSeed( uinttype64 seed )
{
  lcg = seed;
}

tamias::uinttype32 LCGRandom::next()
{
  lcg = lcg * 239017 + 997;
  return (tamias::uinttype32)(lcg >> 16);
}

tamias::String LCGRandom::nextToken( sizetype length )
{
  String s = "", chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (sizetype i = 0; i < length; i++)
    s += chars[next() % chars.length()];
  return s;
}

