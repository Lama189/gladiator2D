from core.config import get_settings


settings = get_settings()


class Player:
    def __init__(self, player_id: int, x: float, y: float) -> None:
        self.player_id = player_id
        self.x = x
        self.y = y

    def apply_input(self, keys: dict, dt: float) -> None:
        current_speed = settings.speed
        if keys.get("sprint"):
            current_speed *= settings.sprint_multiplier

        if keys.get("up"):
            self.y -= current_speed * dt
        if keys.get("down"):
            self.y += current_speed * dt
        if keys.get("left"):
            self.x -= current_speed * dt
        if keys.get("right"):
            self.x += current_speed * dt

    
    def to_dict(self) -> dict:
        return {"x": self.x, "y": self.y}