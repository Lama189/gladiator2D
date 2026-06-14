import asyncio
import socket
from core.protocol import unpack, pack, PacketType
from core.game_loop import GameLoop


class Server:
    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.game_loop = GameLoop()
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


    async def start(self) -> None:
        self.sock.bind((self.host, self.port))
        self.sock.setblocking(False)

        loop = asyncio.get_event_loop()

        loop.add_reader(self.sock, self._on_packet)

        print(f"Server started on {self.host}:{self.port}")

        await self.game_loop.start(self.sock)


    def _on_packet(self) -> None:
        data, addr = self.sock.recvfrom(1024)
        packet = unpack(data)
        packet_type = packet.get("type")

        if packet_type == PacketType.CONNECT:
            self.game_loop.on_connect(addr)

        elif packet_type == PacketType.DISCONNECT:
            self.game_loop.on_disconnect(addr)

        elif packet_type == PacketType.INPUT:
            self.game_loop.on_input(addr, packet.get("keys", {}))


    def stop(self) -> None:
        self.sock.close()