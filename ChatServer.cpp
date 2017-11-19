#include "stdafx.h"
#include "ChatServer.h"

ChatServer* ChatServer::instance = NULL;

std::string ChatServer::GetTimeString()
{
	std::stringstream ss;
	boost::posix_time::ptime d = boost::posix_time::microsec_clock::local_time();;
	boost::posix_time::time_facet* dfacet = new boost::posix_time::time_facet("%Y年%m月%d日 %H:%M:%S");
	
	ss.imbue(std::locale(ss.getloc(), dfacet));
	ss << d;
	return ss.str();
}

void ChatServer::PostMsg(ClientUser * origin_user, const_buffers_1 msg)
{
	for (unordered_client_set::iterator it = m_client_set.begin(); it != m_client_set.end(); ++it)
	{
		ClientUser* user = dynamic_cast<ClientUser*>(*it);
		
		if (user != origin_user) 
			user->SendMsg(msg);
	}
}

void ChatServer::PostMsg(ClientUser * origin_user, mutable_buffers_1 msg)
{
	for (unordered_client_set::iterator it = m_client_set.begin(); it != m_client_set.end(); ++it)
	{
		ClientUser* user = dynamic_cast<ClientUser*>(*it);
		if (user != origin_user) 
			user->SendMsg(msg);
	}
}

void ChatServer::Start()
{
	try
	{
		for (;;)
		{
			tcp::socket* socket = new tcp::socket(*m_io);

			m_acceptor.accept(*socket);

			std::string msg = ChatServer::GetTimeString();

			//boost::system::error_code ec;
			//write(*socket, buffer(msg), ec);

			// 数组存入新User
			ClientUser* user = new ClientUser(socket);
			m_client_set.insert(user);

			tcp::endpoint endpoint = socket->remote_endpoint();
			std::cout << "New:" << endpoint.address().to_string() << ":" << endpoint.port() << std::endl;

			boost::thread th(boost::bind(&ClientUser::Worker, user));

		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void ChatServer::RemoveClient(ClientUser * user)
{
	m_client_set.erase(user);
}

ChatServer::ChatServer(io_service * io)
	: m_acceptor(*io, tcp::endpoint(tcp::v4(), LISTEN_PORT))
{
	m_io = io;
	instance = this;
}

ChatServer::~ChatServer()
{
}
