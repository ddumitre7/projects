
from enum import Enum, auto
import logging
import sys

logging.basicConfig(stream=sys.stderr, level=logging.DEBUG)


class Direction(Enum):
    UP = auto()
    DOWN = auto()
    LEFT = auto()
    RIGHT = auto()


class BodyCell:
    def __init__(self, x, y, direction):
        """Initialize name and age attributes."""
        self.x = x
        self.y = y
        self.direction = direction


class Snake:
    """The snake abstraction"""

    def __init__(self):
        """Initialize the 
        snake"""
        self.MAX_X = 100
        self.MAX_Y = 80
        self.INIT_LEN = 6
        self.body = [BodyCell(51, 40, Direction.RIGHT), BodyCell(50, 40, Direction.RIGHT),
                     BodyCell(52, 40, Direction.RIGHT), BodyCell(
                         53, 40, Direction.RIGHT),
                     BodyCell(50, 40, Direction.RIGHT), BodyCell(
                         54, 40, Direction.RIGHT),
                     BodyCell(55, 40, Direction.RIGHT), BodyCell(50, 40, Direction.RIGHT)]
        self.logger = logging.getLogger(self.__class__.__qualname__)
        self.logger.debug("__init__() - size board: (%r, %r)",
                          self.MAX_X, self.MAX_Y)
        self.head_dir = self.body[len(self.body) - 1].direction

    def print_body(self):
        """Print the snake cells."""
        self.logger.debug("The Snake is:")
        for e in self.body:
            self.logger.debug(f"\t({e.x}, {e.y}, {e.direction})")

    @staticmethod
    def new_head(head, direction):
        newhead = BodyCell(head.x, head.y, head.direction)

        if (head.direction == Direction.RIGHT and direction == Direction.LEFT) or \
            (head.direction == Direction.LEFT and direction == Direction.RIGHT) or \
            (head.direction == Direction.UP and direction == Direction.DOWN) or \
                (head.direction == Direction.DOWN and direction == Direction.UP):
            raise Exception('Invalid direction')

        if direction == Direction.RIGHT:
            newhead.x += 1
            newhead.direction = Direction.RIGHT
            return newhead

        if direction == Direction.UP:
            newhead.y += 1
            newhead.direction = Direction.UP
            return newhead

        if direction == Direction.DOWN:
            newhead.y -= 1
            newhead.direction = Direction.DOWN
            return newhead

        if direction == Direction.LEFT:
            newhead.x -= 1
            newhead.direction = Direction.LEFT
            return newhead

    def move(self, direction):
        assert len(self.body) > 0

        last_index = len(self.body) - 1
        self.body.append(Snake.new_head(self.body[last_index], direction))
        del self.body[0]
