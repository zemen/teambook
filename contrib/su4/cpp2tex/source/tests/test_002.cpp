#include "../../include/basic/exception.h"
#include "../../include/io/event_poll.h"
#include "../../include/main/vector.h"
#include "../../include/network/socket.h"

using tamias::sizetype;
using tamias::EventPoll;
using tamias::Exception;
using tamias::TcpClientSocket;
using tamias::Vector;

int main()
{
  try
  {
    TcpClientSocket socket = TcpClientSocket();
    socket.connect("127.0.0.1", 80);
    socket.write("GET / HTTP/1.0\r\n\r\n");
    EventPoll poll = EventPoll();
    poll.addEvent(socket, EventPoll::EVENT_IN);
    Vector <sizetype> pollResult = poll.poll();
    for (sizetype i = 0; i < pollResult.size(); i++)
      socket.read();
  }
  catch (Exception &e)
  {
    return 1;
  }
  return 0;
}

