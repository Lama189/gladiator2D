#include "core/client/udpclient.hpp"
#include <unistd.h>
#include <fcntl.h>

UDPClient::UDPClient() { }

UDPClient::~UDPClient() { disconnect(); }

bool UDPClient::connect(const std::string& host, int port)
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return false;

    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &serverAddr.sin_addr);

    return true;
}

void UDPClient::disconnect()
{
    if (sock >= 0)
    {
        close(sock);
        sock = -1;
    }
}

bool UDPClient::send(const std::vector<uint8_t>& data)
{
    if (sock < 0)
        return false;

    size_t send = sendto(sock, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    return send > 0;
}

bool UDPClient::receive(std::vector<uint8_t>& data, size_t maxSize)
{
    if (sock < 0)
        return false;

    data.resize(maxSize);

    ssize_t received = recvfrom(sock, data.data(), data.size(), 0, nullptr, nullptr);

    if (received <= 0)
    {
        data.clear();
        return false;
    }

    data.resize(received);
    return true;
}