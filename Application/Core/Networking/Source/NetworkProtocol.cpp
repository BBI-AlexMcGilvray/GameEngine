#include "Core/Networking/Headers/NetworkProtocol.h"

namespace Core
{
	namespace Networking
	{
	// Network Protocol
		NetworkProtocol::NetworkProtocol()
		{}

		NetworkProtocol::~NetworkProtocol()
		{
			// don't call virtual method as object state (type) is uncertain
		}

	// TCP Protocol
		void TCPProtocol::Initialize()
		{

		}

		void TCPProtocol::Run()
		{

		}

		void TCPProtocol::Destroy()
		{

		}

	// UDP Protocol
		void UDPProtocol::Initialize()
		{

		}

		void UDPProtocol::Run()
		{

		}

		void UDPProtocol::Destroy()
		{

		}
	}
}