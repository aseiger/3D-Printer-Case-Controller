/*
 * Communications.h
 *
 *  Created on: Apr 5, 2020
 *      Author: awsei
 *
 *      A wrapper around packetSerial for handling the various system messages
 */

#ifndef COMMUNICATIONS_H_
#define COMMUNICATIONS_H_

namespace CommunicationsHandler
{
	enum messageTypes
	{
		NO_MSG = 0,
		HEARTBEAT = 1,
		STATUS_REQUEST = 2,
		SET_VALVE_POSITION = 3
	};


	void onPacketReceived(const uint8_t* buffer, size_t size);
}



#endif /* COMMUNICATIONS_H_ */
