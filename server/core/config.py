from functools import lru_cache
from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    speed: float = 60.0
    sprint_multiplier: float = 2.0
    tick_rate: int = 20

    model_config = {
        "env_file": ".env",
        "env_file_encoding": "utf-8",
    }


@lru_cache(maxsize=1)
def get_settings() -> Settings:
    return Settings()