#include "stdafx.h"
#include "ChatServer.h"

using boost::asio::ip::tcp;
using namespace boost::asio;


int main()
{
	io_service* io = new io_service();
	ChatServer server(io);
	server.Start();

    return 0;
}
