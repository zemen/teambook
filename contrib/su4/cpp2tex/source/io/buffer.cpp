#include "../../include/io/buffer.h"

using tamias::sizetype;
using tamias::Buffer;
using tamias::ByteArray;
using tamias::IODevice;
using tamias::utilities::memoryCopy;

Buffer::Buffer() : bufferData(0), bufferStart(0), bufferSize(0)
{
}

Buffer::Buffer( const Buffer &buffer ) : bufferData(buffer.bufferSize), bufferStart(0), bufferSize(buffer.bufferSize)
{
  memoryCopy(bufferData.getData(), (char*)buffer.bufferData.getData() + buffer.bufferStart, bufferSize);
}

Buffer::~Buffer()
{
  bufferStart = bufferSize = 0;
}

Buffer& Buffer::operator = ( const Buffer &buffer )
{
  bufferData.manualReserve(buffer.bufferSize);
  bufferStart = 0, bufferSize = buffer.bufferSize;
  memoryCopy(bufferData.getData(), (char*)buffer.bufferData.getData() + buffer.bufferStart, bufferSize);
  return *this;
}

IODevice* Buffer::clone() const
{
  return new Buffer(*this);
}

bool Buffer::canRead() const
{
  return true;
}

bool Buffer::canWrite() const
{
  return true;
}

bool Buffer::canSeek() const
{
  return false;
}

void Buffer::close()
{
}

bool Buffer::eof()
{
  return bufferSize == 0;
}

bool Buffer::waitForRead()
{
  return bufferSize != 0;
}

ByteArray Buffer::read( sizetype maxSize )
{
  if (maxSize > bufferSize)
    maxSize = bufferSize;
  ByteArray result = ByteArray((char*)bufferData.getData() + bufferStart, maxSize);
  bufferStart += maxSize, bufferSize -= maxSize;
  if (bufferStart > bufferSize)
  {
    memoryCopy(bufferData.getData(), (char*)bufferData.getData() + bufferStart, bufferSize);
    bufferStart = 0;
    bufferData.manualReserve(bufferSize);
  }
  return result;
}

sizetype Buffer::write( const ByteArray &data )
{
  bufferData.autoReserveUp(bufferStart + bufferSize + data.size());
  memoryCopy((char*)bufferData.getData() + bufferStart + bufferSize, data.cString(), data.size());
  bufferSize += data.size();
  return data.size();
}

void Buffer::seek( sizetype index )
{
}

sizetype Buffer::size()
{
  return bufferSize;
}

ByteArray Buffer::preview( sizetype viewSize )
{
  if (viewSize > bufferSize)
    viewSize = bufferSize;
  return ByteArray((char*)bufferData.getData() + bufferStart, viewSize);
}

