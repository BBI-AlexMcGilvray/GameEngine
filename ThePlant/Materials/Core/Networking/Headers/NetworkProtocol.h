#pragma once

namespace Core {
namespace Networking {
  class NetworkProtocol
  {
  public:
    NetworkProtocol();

    virtual ~NetworkProtocol();

    virtual void Initialize() = 0;
    virtual void Run() = 0;
    virtual void Destroy() = 0;
  };

  // https://www.thecrazyprogrammer.com/2017/06/socket-programming.html
  class TCPProtocol : NetworkProtocol
  {
  public:
    //~TCPProtocol();

    void Initialize() override;
    void Run() override;
    void Destroy() override;
  };

  // https://www.binarytides.com/udp-socket-programming-in-winsock/
  class UDPProtocol : NetworkProtocol
  {
  public:
    //~UDPProtocol();

    void Initialize() override;
    void Run() override;
    void Destroy() override;
  };
}// namespace Networking
}// namespace Core
