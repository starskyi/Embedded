import pygame

# 初始化pygame
pygame.init()

# 创建窗口
screen = pygame.display.set_mode(size=(640, 480))

# 窗口标题
pygame.display.set_caption("plane")

# 背景色
color = (0, 150, 0)

# 图标
icon = pygame.image.load("picture/icon.png")
pygame.display.set_icon(icon)

# 添加图片
plane_picutre = pygame.image.load("res/hero2.png")

# 旋转
plane_picutre = pygame.transform.rotate(plane_picutre, 90)

# 时钟
clock = pygame.time.Clock()

while True:
    # 获取用户触发事件列表
    event_list = pygame.event.get()

    for event in event_list:
        if event.type == pygame.QUIT:
            print("关闭窗口")
            pygame.display.quit()
            exit(0)
        elif event.type == pygame.KEYDOWN:
            print("key:", event.key)

    screen.fill(color)
    screen.blit(plane_picutre, (300, 100))
    pygame.display.flip()

    clock.tick(10)  # 设置fps帧率
    print("fps: ", clock.get_fps())