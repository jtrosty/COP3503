import pygame
from sys import exit

pygame.init()
screen = pygame.display.set_mode((800, 400))
pygame.display.set_caption('Trosty Cakes')
clock = pygame.time.Clock()

test_font = pygame.font.Font(None, 50)

background = pygame.image.load('graphics/background.png').convert()
enemy_surf = pygame.image.load('graphics/Enemy/basic_enemy.png').convert_alpha()
enemy_rect = enemy_surf.get_rect(midbottom = (80, 200))
enemy_x_pos = 0

player_surf = pygame.image.load('graphics/Player/player_craft.png').convert_alpha()
player_rect = player_surf.get_rect(midbottom = (80, 200))


test_surf = pygame.Surface((100, 200))
test_surf.fill('Red')
text_surf = test_font.render("Trost Game", True, 'Yellow')


score_surf = test_font.render('My game', True, 'Black')
score_rect = score_surf.get_rect(center = (500, 50))



while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        if event.type == pygame.MOUSEMOTION:
            print(event.pos)
    #Draw our elements
    #Update everything

    screen.blit(background,(0,0))
    screen.blit(test_surf, (200, 100))
    screen.blit(text_surf,(300, 50))
    enemy_rect.x -= 3
    if enemy_rect.right <= 0: enemy_rect.left = 800
    screen.blit(enemy_surf, enemy_rect)
    screen.blit(player_surf, player_rect)

    mouse_pos = pygame.mouse.get_pos()

    #if player_rect.collidepoint((mouse_pos)):
        #print(pygame.mouse.get_pressed())

#    if player_rect.colliderect(enemy_rect): 
#        print('Collision')

    pygame.display.update()
    clock.tick(60) #Don't run faster than 60 times a second