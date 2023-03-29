from enum import Enum
import pygame

class EntityType(Enum):
    PLAYER = 0
    ENEMY = 1
    ROCK = 2

class Entity:

    def __init__(self, name: str, type: EntityType, rect: pygame.Rect):
        self.name = name
        self.entityType = type
        self.rect:pygame.Rect = rect


    def getRect(self) -> pygame.Rect:
        return self.rect

    def updateRectX(self, change: int):
        self.rect.x += change

    def updateRectY(self, change: int):
        self.rect.x += change

