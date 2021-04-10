from snake_level1 import Snake
from snake_level1 import Direction
import logging
import sys

if __name__ == "__main__":  
    logging.basicConfig(stream=sys.stderr, level=logging.DEBUG)
    snake = Snake()
    snake.print_body()
    snake.move(snake.head_dir)
    snake.print_body()
    snake.move(Direction.RIGHT)
    snake.print_body()
    snake.move(Direction.UP)
    snake.print_body()
    snake.move(Direction.LEFT)
    snake.print_body()
    snake.move(Direction.LEFT)
    snake.print_body()




