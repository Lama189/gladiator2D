#pragma once
#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace Protocol {

struct PlayerState {
    float x = 0.f;
    float y = 0.f;
};

struct ServerState {
    std::map<std::string, PlayerState> players;
};

std::vector<uint8_t> encodeConnect();
std::vector<uint8_t> encodeInput(bool up, bool down, bool left, bool right, bool sprint);
bool decodePacket(const uint8_t* data, size_t len, ServerState& state, std::string& player_id);

}
