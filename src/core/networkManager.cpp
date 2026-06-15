#include "core/networkManager.hpp"
#include "game/player.hpp"

static constexpr const char* SERVER_HOST = "127.0.0.1";
static constexpr int SERVER_PORT = 7777;

void NetworkManager::init()
{
    client = std::make_unique<UDPClient>();

    if (client->connect(SERVER_HOST, SERVER_PORT))
    {
        auto connectPacket = Protocol::encodeConnect();
        client->send(connectPacket);
    }
}

void NetworkManager::cleanup()
{
    client->disconnect();
}

void NetworkManager::update(float dt, Player& player)
{
    sendInput(IsKeyDown(KEY_W),
        IsKeyDown(KEY_S),
        IsKeyDown(KEY_A),
        IsKeyDown(KEY_D),
        IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT),
        false);
    
    std::vector<uint8_t> recvBuf;
    std::string lastPlayerId;

    while (client->receive(recvBuf))
    {
        if (Protocol::decodePacket(recvBuf.data(), recvBuf.size(), lastState, lastPlayerId))
        {
            if (!connected && !lastPlayerId.empty())
            {
                playerId = lastPlayerId;
                player.setPlayerId(playerId);
                connected = true;
            }
        }
    }

    if (connected)
    {
        auto it = lastState.players.find(playerId);
        if (it != lastState.players.end())
        {
            player.setServerPosition({it->second.x, it->second.y});
        }
    }
}

void NetworkManager::sendInput(
    bool up, bool down,
    bool left, bool right,
    bool sprint, bool attack)
{
    auto inputPacket = Protocol::encodeInput(
        up,
        down,
        left,
        right,
        sprint,
        attack
    );

    client->send(inputPacket);
}

const std::string& NetworkManager::getPlayerId() const
{
    return playerId;
}

const Protocol::ServerState& NetworkManager::getLastState() const
{
    return lastState;
}