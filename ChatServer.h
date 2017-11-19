#pragma once

#ifndef __CHAT_SERVER_H__
#define __CHAT_SERVER_H__

#include "stdafx.h"

#include "ClientUser.h"
class ClientUser;

using boost::asio::ip::tcp;
using namespace boost::asio;


typedef boost::unordered_set<ClientUser*> unordered_client_set;

/*�����ҷ��������*/
class ChatServer
{
public:

	/*��ȡ��ǰʱ��ĸ�ʽ����ʾ yyyy-MM-dd HH:mm:ss*/
	static std::string GetTimeString();

	/*���͸����пͻ�����Ϣ����origin_user֮�⡣*/
	void PostMsg(ClientUser* origin_user, const_buffers_1 msg);

	/*���͸����пͻ�����Ϣ����origin_user֮�⡣*/
	void PostMsg(ClientUser* origin_user, mutable_buffers_1 msg);

	/*���������ҷ����߼�*/
	void Start();

	/*�Ƴ��ͻ����û�*/
	void RemoveClient(ClientUser* user);

	/*���췽��������io_service*/
	ChatServer(io_service* io);

	~ChatServer();

	/*��ȡ����*/
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
