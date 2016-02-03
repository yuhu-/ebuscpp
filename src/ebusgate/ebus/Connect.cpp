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

#include "Connect.h"
#include "Idle.h"
#include "Listen.h"
#include "Logger.h"

#include <sstream>

#include <unistd.h>

using std::ostringstream;

extern Logger& L;

Connect Connect::m_connect;

int Connect::run(EbusHandler* h)
{
	int result = DEV_OK;

	if (h->m_device->isOpen() == false)
	{
		result = h->m_device->open();

		if (h->m_device->isOpen() == true && result == DEV_OK)
		{
			L.log(info, "ebus connected");
		}
		else
		{
			L.log(error, "%s",
				h->m_device->errorText(h->m_lastResult).c_str());
			sleep(1);
			m_reopenTime++;

			if (m_reopenTime > h->m_reopenTime)
				h->changeState(Idle::getInstance());

			return (result);
		}
	}

	reset(h);

	if (h->m_active == true)
	{
		EbusSequence eSeq;
		eSeq.createMaster(h->m_address, BROADCAST,
			"07040a7a454741544501010101");

		if (eSeq.getMasterState() == EBUS_OK)
			h->addMessage(new EbusMessage(eSeq));
	}

	h->changeState(Listen::getInstance());
	return (result);
}

Connect::Connect()
{
}

const char* Connect::toString() const
{
	return ("Connect");
}
