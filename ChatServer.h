#pragma once

#ifndef __CHAT_SERVER_H__
#define __CHAT_SERVER_H__

#include "stdafx.h"

#include "ClientUser.h"
class ClientUser;

using boost::asio::ip::tcp;
using namespace boost::asio;


typedef boost::unordered_set<ClientUser*> unordered_client_set;

/*聊天室服务管理类*/
class ChatServer
{
public:

	/*获取当前时间的格式化表示 yyyy-MM-dd HH:mm:ss*/
	static std::string GetTimeString();

	/*推送给所有客户端消息。除origin_user之外。*/
	void PostMsg(ClientUser* origin_user, const_buffers_1 msg);

	/*推送给所有客户端消息。除origin_user之外。*/
	void PostMsg(ClientUser* origin_user, mutable_buffers_1 msg);

	/*启动聊天室服务逻辑*/
	void Start();

	/*移除客户端用户*/
	void RemoveClient(ClientUser* user);

	/*构造方法。传入io_service*/
	ChatServer(io_service* io);

	~ChatServer();

	/*获取单例*/
	static ChatServer* getInstance()
	{
		return instance;
	}

private:
	unordered_client_set m_client_set;
	tcp::acceptor m_acceptor;
	io_service* m_io;
	static ChatServer* instance;
};


#endif // !__CHAT_SERVER_H__
