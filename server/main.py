import asyncio
from core.server import Server
from core.config import get_settings

settings = get_settings()


async def main() -> None:
    server = Server(host="0.0.0.0", port=7777)
    try:
        await server.start()
    except KeyboardInterrupt:
        server.stop()


asyncio.run(main())