import asyncio
import socket
from game.player import Player
from core.protocol import pack, PacketType
from core.config import get_settings

settings = get_settings()


class GameLoop:
    def __init__(self):
        self.players: dict[tuple, Player] = {}
        self.inputs: dict[tuple, dict] = {}
        self.tick_interval = 1.0 / settings.tick_rate


    async def start(self, sock: socket.socket) -> None:
        self.sock = sock
        while True:
            await asyncio.sleep(self.tick_interval)
            self._tick()

    def on_connect(self, addr: tuple) -> None:
        player_id = f"{addr[0]}:{addr[1]}"
        self.players[addr] = Player(player_id, x=400.0, y=300.0)
        self.inputs[addr] = {}

        response = pack({
            "type": PacketType.CONNECTED,
            "player_id": player_id
        })
        self.sock.sendto(response, addr)
        print(f"Player {player_id} connected")


    def on_disconnect(self, addr: tuple) -> None:
        if addr in self.players:
            print(f"Player {self.players[addr].player_id} disconnected")
            del self.players[addr]
            del self.inputs[addr]


    def on_input(self, addr: tuple, keys: dict) -> None:
        if addr in self.inputs:
            self.inputs[addr] = keys


    def _tick(self) -> None:
        dt = self.tick_interval

        for addr, player in self.players.items():
            player.apply_input(self.inputs.get(addr, {}), dt)

        state = pack({
            "type": PacketType.STATE,
            "players": {
                player.player_id: player.to_dict()
                for player in self.players.values()
            }
        })

        # print(f"Sending state: {state}")

        for addr in self.players:
            self.sock.sendto(state, addr)