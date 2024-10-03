"""
    贪吃蛇游戏
"""


import pygame
import random

SCREEN_WIDTH = 640
SCREEN_HIGHT = 480
BLOCK_SIZE = 20
grid_color = (100, 100, 100)
snake_block_color = (255, 255, 255)
food_color = (0, 0, 150)
color_red = (255, 0, 0)
MAX_X = SCREEN_WIDTH // BLOCK_SIZE
MAX_Y = SCREEN_HIGHT // BLOCK_SIZE

DIRECTION_DICT = {
    pygame.K_UP: (0, -BLOCK_SIZE),
    pygame.K_LEFT: (-BLOCK_SIZE, 0),
    pygame.K_DOWN: (0, BLOCK_SIZE),
    pygame.K_RIGHT: (BLOCK_SIZE, 0)

}

HEAD_DICT = {
    pygame.K_LEFT: 0,
    pygame.K_DOWN: 90,
    pygame.K_RIGHT: 180,
    pygame.K_UP: 270
}



class Snake:
    def __init__(self):
        self.FPS = 10
        self.direction = pygame.K_LEFT
        self.score = 0
        head = pygame.image.load("picture/head-red.png")
        head = pygame.transform.scale(head, (BLOCK_SIZE, BLOCK_SIZE))
        self.head_pic = pygame.transform.rotate(head, 270)

        # 蛇的身体
        self.snake_body = [
            pygame.Rect(10 * BLOCK_SIZE, 3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE), 
            pygame.Rect(11 * BLOCK_SIZE, 3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE),
            pygame.Rect(12 * BLOCK_SIZE, 3 * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
        ]

    
    def draw(self, screen):
        for block in self.snake_body[1:]:
            pygame.draw.rect(screen, snake_block_color, block, border_radius=3)

        head_coord = self.snake_body[0]
        head_pic = pygame.transform.rotate(self.head_pic, HEAD_DICT[self.direction])
        screen.blit(head_pic, (head_coord.x, head_coord.y))

    def move(self):
        new_node = self.snake_body[0].copy()
        
        new_move = DIRECTION_DICT[self.direction]
        new_node.x += new_move[0]
        new_node.y += new_move[1] 

        self.snake_body.insert(0, new_node)
        self.snake_body.pop()

    def UpdateDirection(self, new_direction):
        UD = (pygame.K_UP, pygame.K_DOWN)
        LR = (pygame.K_LEFT, pygame.K_RIGHT)

        if (self.direction in UD and new_direction in UD) or (self.direction in LR and new_direction in LR):
            return
        self.direction = new_direction
    
    def grow(self):
        self.snake_body.append(self.snake_body[-1].copy())
        self.score += 1
        if(self.score % 5 == 0):
            self.FPS += 1

class Food:
    def __init__(self, node):
        self.node = node

    def draw(self, screen):
        if self.node is not None:
            pygame.draw.rect(screen, food_color, self.node, border_radius=3)

    @staticmethod
    def get_snake_position(snake: Snake) -> pygame.Rect:

        while True:
            x = random.randint(0, MAX_X - 1)
            y = random.randint(0, MAX_Y - 1)
            food_rect = pygame.Rect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)
            if food_rect not in snake.snake_body:
                return pygame.Rect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE)

class Game:
    def __init__(self):
        pygame.init()

        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HIGHT))

        pygame.display.set_caption("Gluttonous Snake")

        icon = pygame.image.load("picture/icon.png")
        pygame.display.set_icon(icon)

        back_picture = pygame.image.load("picture/bg.png")
        self.back_picture = pygame.transform.scale(back_picture, (SCREEN_WIDTH, SCREEN_HIGHT))

    def key_listener(self):
        event_list = pygame.event.get()
            
        for event in event_list:
            if event.type == pygame.QUIT:
                self.quit_game()
            elif event.type == pygame.KEYDOWN:
                self.is_now_render = True
                if event.key != pygame.K_q and self.is_game_over:
                    #从新游戏
                    self.restart_game()
                if event.key == pygame.K_UP:
                    self.snake.UpdateDirection(pygame.K_UP)
                elif event.key == pygame.K_LEFT:
                    self.snake.UpdateDirection(pygame.K_LEFT)
                elif event.key == pygame.K_DOWN:
                    self.snake.UpdateDirection(pygame.K_DOWN)
                elif event.key == pygame.K_RIGHT:
                    self.snake.UpdateDirection(pygame.K_RIGHT)
                elif event.key == pygame.K_ESCAPE:
                    self.quit_game()

    def quit_game(self):
        pygame.display.quit()
        exit(0)

    def restart_game(self):
        self.snake = Snake()
        self.food = Food(Food.get_snake_position(self.snake))
        self.is_game_over = False

    def show_text(self, text, font_size, x, y):
        font = pygame.font.SysFont("SimHei", font_size)
        text = font.render(text, True, color_red)
        self.screen.blit(text, (x, y))

    def start(self):
        
        self.snake = Snake()
        self.food = Food(Food.get_snake_position(self.snake))
        self.is_game_over = False
        clock = pygame.time.Clock()

        count = 0
        while True:
             # 键盘监听
            self.is_now_render = False
            self.key_listener()

            # 判断游戏是否结束
            if self.snake.snake_body[0] in self.snake.snake_body[1:] or \
                (self.snake.snake_body[0].x < 0 or self.snake.snake_body[0].x >= SCREEN_WIDTH) or \
                    (self.snake.snake_body[0].y < 0 or self.snake.snake_body[0].y >= SCREEN_HIGHT):
                self.is_game_over = True

            if not self.is_game_over:
                self.snake.move()

                # 判断是否吃到食物
                if self.snake.snake_body[0] == self.food.node:
                    self.food = Food(Food.get_snake_position(self.snake))
                    self.snake.grow()

            # 绘制背景和网格
            self.screen.blit(self.back_picture, (0, 0))
            for x in range(0, SCREEN_WIDTH, 20):
                pygame.draw.line(self.screen, grid_color, (x, 0), (x, SCREEN_HIGHT))
            for y in range(0, SCREEN_HIGHT, 20):
                pygame.draw.line(self.screen, grid_color, (0, y), (SCREEN_WIDTH, y))

            # 绘制蛇
            self.snake.draw(self.screen)

            # 绘制食物
            self.food.draw(self.screen)

            # 根据游戏是否结束绘制文字
            if self.is_game_over:
                self.show_text("游戏结束", 50, SCREEN_WIDTH / 4, SCREEN_HIGHT / 4)
                self.show_text(f"得分: {self.snake.score}", 30, SCREEN_WIDTH / 4, SCREEN_HIGHT / 4 + 60)
                self.show_text("按Q退出", 30, SCREEN_WIDTH / 4, SCREEN_HIGHT / 4 + 100)
                self.show_text("按任意键重新开始", 30, SCREEN_WIDTH / 4, SCREEN_HIGHT / 4 + 140)

            self.show_text(f"Score: {self.snake.score}", 20, 10, 10)
            self.show_text("FPS: {:.2f}".format(clock.get_fps()), 20, SCREEN_WIDTH - 100, 10)
            count += 1
      
            pygame.display.flip() #渲染
            if not self.is_now_render:
                clock.tick(self.snake.FPS)

game = Game()
game.start()
