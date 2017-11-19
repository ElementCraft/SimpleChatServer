#pragma once

#ifndef __CLIENT_USER_H__
#define __CLIENT_USER_H__

#include "stdafx.h"
#include "ChatServer.h"

using boost::asio::ip::tcp;
using namespace boost::asio;

// �û���
class ChatServer;

/*
�ͻ����û�����
*/
class ClientUser
{
public:

	/*�����û��߳����е�ѭ��*/
	void Worker();

	/*����û�������Ϣ*/
	void SendMsg(const_buffers_1& msg);

	/*����û�������Ϣ*/
	void SendMsg(mutable_buffers_1& msg);

	/*���췽��������ͻ����û���socket����*/
	ClientUser(tcp::socket* socket);

	~ClientUser();

	/*��ȡ�ÿͻ���Socket*/
	tcp::socket* getSocket() const
	{
		return this->m_socket;
	}

	/*��ȡ�ͻ����û�����*/
	std::string getName() const
	{
		return this->m_strName;
	}

private:
	std::string m_strName;
	tcp::socket* m_socket;

};

#endif // !__CLIENT_USER_H__
