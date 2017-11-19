#pragma once

#ifndef __CLIENT_USER_H__
#define __CLIENT_USER_H__

#include "stdafx.h"
#include "ChatServer.h"

using boost::asio::ip::tcp;
using namespace boost::asio;

// 用户类
class ChatServer;

/*
客户端用户连接
*/
class ClientUser
{
public:

	/*处理用户线程运行的循环*/
	void Worker();

	/*向该用户发送消息*/
	void SendMsg(const_buffers_1& msg);

	/*向该用户发送消息*/
	void SendMsg(mutable_buffers_1& msg);

	/*构造方法。传入客户端用户的socket连接*/
	ClientUser(tcp::socket* socket);

	~ClientUser();

	/*获取该客户端Socket*/
	tcp::socket* getSocket() const
	{
		return this->m_socket;
	}

	/*获取客户端用户名称*/
	std::string getName() const
	{
		return this->m_strName;
	}

private:
	std::string m_strName;
	tcp::socket* m_socket;

};

#endif // !__CLIENT_USER_H__
