from enum import IntEnum
import msgpack


class PacketType(IntEnum):
    CONNECT = 1
    DISCONNECT = 2
    INPUT = 3
    CONNECTED = 4
    STATE = 5


def pack(data: dict) -> bytes | None:
    return msgpack.packb(data, use_bin_type=True)


def unpack(data: bytes) -> dict:
    return msgpack.unpackb(data, raw=False)