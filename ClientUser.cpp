#include "stdafx.h"
#include "ClientUser.h"


void ClientUser::Worker()
{
	boost::array<char, 256> buf;
	boost::system::error_code ec;
	for (;;)
	{

		size_t len = m_socket->read_some(buffer(buf), ec);
		if (ec == boost::asio::error::eof)
		{
			ChatServer::getInstance()->RemoveClient(this);
			break;
		}
		else if (ec)
		{
			std::cout << ec.message() << std::endl;
			ChatServer::getInstance()->RemoveClient(this);
			// throw boost::system::system_error(ec);
			break;
		}

		if (len > 0)
		{
			// 第一条消息为昵称
			if (m_strName.length() == 0)
			{
				m_strName = std::string(buf.data(), len);
				std::string str = "=============" + m_strName + TO_UTF8(" 上线了！===========\r\n", "GBK");
				ChatServer::getInstance()->PostMsg(NULL, buffer(str));
				continue;
			}

			std::string strTime = TO_UTF8(ChatServer::GetTimeString(), "GBK");
			std::string str = "{ " + m_strName + "} - [" + strTime + "]\r\n    " + std::string(buf.data(), len);
			ChatServer::getInstance()->PostMsg(NULL, buffer(str));

		}
	}
}

void ClientUser::SendMsg(const_buffers_1 & msg)
{
	boost::system::error_code ec;

	write(*m_socket, msg, ec);
	if (ec) throw boost::system::system_error(ec);
}

void ClientUser::SendMsg(mutable_buffers_1 & msg)
{
	boost::system::error_code ec;

	write(*m_socket, msg, ec);
	if (ec) throw boost::system::system_error(ec);
}

ClientUser::ClientUser(tcp::socket * socket)
{
	this->m_socket = socket;
}

ClientUser::~ClientUser()
{

}
