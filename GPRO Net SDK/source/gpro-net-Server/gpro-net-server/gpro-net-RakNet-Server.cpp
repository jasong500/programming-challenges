/*
   Copyright 2021 Daniel S. Buckstein

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	GPRO Net SDK: Networking framework.
	By Daniel S. Buckstein

	gpro-net-RakNet-Server.cpp
	Source for RakNet server management.
*/

#include "gpro-net/gpro-net-server/gpro-net-RakNet-Server.hpp"


namespace gproNet
{
	cRakNetServer::cRakNetServer()
	{
		RakNet::SocketDescriptor sd(SET_GPRO_SERVER_PORT, 0);
		unsigned short MAX_CLIENTS = 10;

		peer->Startup(MAX_CLIENTS, &sd, 1);
		peer->SetMaximumIncomingConnections(MAX_CLIENTS);
	}

	cRakNetServer::~cRakNetServer()
	{
		peer->Shutdown(0);
	}

	bool cRakNetServer::ProcessMessage(RakNet::BitStream& bitstream, RakNet::SystemAddress const sender, RakNet::Time const dtSendToReceive, RakNet::MessageID const msgID)
	{
		if (cRakNetManager::ProcessMessage(bitstream, sender, dtSendToReceive, msgID))
			return true;

		// server-specific messages
		switch (msgID)
		{
		case ID_NEW_INCOMING_CONNECTION:
			//printf("A connection is incoming.\n");

			//store the new user in a list of all connected users
			//send the user a list of all available rooms to join and their ping in terms of that particular player

			return true;

		case ID_ROOMS_JOIN:
		{
			//send the room the ID of the player that just attempted to join the room
			//make sure there is space for the player and if there is actually join the room
			//add that player to the list of users in said room
			//broadcast that said player just joined the room

		}
		case ID_ROOMS_LEAVE:
		{
			//remove the user from the list of users in the specified room
			//return the player to the lobby and send the player the list of available game rooms
			//broadcast that said player just left the room

		}
		case ID_ROOM_CREATE:
		{
			//ask the user for a room name and will check to see if the room exists
			//if the room exists return and error telling the player that a room with said name already exists
			//otherwise create the room and automatically join the room
		}
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			//printf("The server is full.\n");
			return true;
		case ID_DISCONNECTION_NOTIFICATION:
			//printf("A client has disconnected.\n");
			return true;
		case ID_CONNECTION_LOST:
			//printf("A client lost the connection.\n");
			return true;

			// test message
		case ID_GPRO_MESSAGE_COMMON_BEGIN:
		{
			// server receives greeting, print it and send one back
			RakNet::BitStream bitstream_w;
			ReadTest(bitstream);
			WriteTest(bitstream_w, "Hello client from server");
			peer->Send(&bitstream_w, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, sender, false);
		}	return true;

		}
		return false;
	}
}