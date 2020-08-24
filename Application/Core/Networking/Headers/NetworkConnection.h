#pragma once

#include "Core/Headers/CoreDefs.h"

//#ifdef __WIN32__
#include <WinSock2.h>
//#else
//#include <sys/socket.h>
//#endif

namespace Core
{
	namespace Networking
	{
		class NetworkConnection
		{
		public:
			String IpAddress;
		//#ifdef __WIN32__
			SOCKET Socket;
		//#else
			// struct sockaddr_in ipOfServer
		//#endif

			bool ConnectionActive;
		};
	}
}