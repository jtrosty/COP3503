import pygame
import entities
from sys import exit

pygame.init()
screen = pygame.display.set_mode((800, 400))
pygame.display.set_caption('Trosty Cakes')
clock = pygame.time.Clock()

test_font = pygame.font.Font(None, 50)


player = entities.Entity('Player', entities.EntityType.PLAYER, (50, 50, 30, 30))
entitiesList = [player]   
background = pygame.image.load('graphics/background.png').convert()
enemy_surf = pygame.image.load('graphics/Enemy/basic_enemy.png').convert_alpha()
enemy_rect = enemy_surf.get_rect(midbottom = (80, 200))
enemy_x_pos = 0

#player_surf = pygame.image.load('graphics/Player/player_craft.png').convert_alpha()
#player_rect = player_surf.get_rect(midbottom = (80, 200))


#test_surf = pygame.Surface((100, 200))
#test_surf.fill('Red')
text_surf = test_font.render("Trost Game", True, 'Yellow')


score_surf = test_font.render('My game', True, 'Black')
score_rect = score_surf.get_rect(center = (500, 50))



while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        if event.type == pygame.KEYDOWN:
            print('Key Down')
            if event.key == pygame.K_w:
                entitiesList[0].updateRectY(3)
        if event.type == pygame.KEYUP:
            print('Key UP')
        #if event.type == pygame.MOUSEMOTION:
        #    print(event.pos)
    #Draw our elements
    #Update everything

    #keys = pygame.key.get_pressed()
    #if keys[pygame.K_w]:
    #    print('forward') 

    screen.blit(background,(0,0))
    #screen.blit(test_surf, (200, 100))
    screen.blit(text_surf,(300, 50))
    pygame.draw.rect(screen, 'Red', entitiesList[0].getRect())
    pygame.draw.line(screen, 'Pink', (0, 0), (800, 400))
    enemy_rect.x -= 3
    if enemy_rect.right <= 0: enemy_rect.left = 800
    #$screen.blit(enemy_surf, enemy_rect)
    #$screen.blit(player_surf, player_rect)

    mouse_pos = pygame.mouse.get_pos()

    #if player_rect.collidepoint((mouse_pos)):
        #print(pygame.mouse.get_pressed())

#    if player_rect.colliderect(enemy_rect): 
#        print('Collision')

    pygame.display.update()
    clock.tick(60) #Don't run faster than 60 times a second