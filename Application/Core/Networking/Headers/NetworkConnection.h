#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Networking/Headers/NetworkProtocol.h"

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
		private:
			Core::UniquePtr<NetworkProtocol> _protocol;

			String _ipAddress;
			//#ifdef __WIN32__
			SOCKET _socket;
			//#else
				// struct sockaddr_in ipOfServer
			//#endif

			bool _connectionActive;

		public:
			void Connect();
			void Validate();
			void Send();
			void Receive();
			void Disconnect();
		};
	}
}