/*
 * Copyright (C) Roland Jax 2012-2016 <roland.jax@liwest.at>
 *
 * This file is part of ebusgate.
 *
 * ebusgate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusgate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusgate. If not, see http://www.gnu.org/licenses/.
 */

#ifndef LIBNETWORK_TCPSERVER_H
#define LIBNETWORK_TCPSERVER_H

#include "TCPSocket.h"

class TCPServer
{

public:
	TCPServer(const int port, const string address);
	~TCPServer();

	int start();

	TCPSocket* newSocket();

	int getFD() const;

private:
	int m_lfd = 0;

	int m_port;

	string m_address;

	bool m_listening = false;

};

#endif // LIBNETWORK_TCPSERVER_H
