# importing libraries
import pygame
from PIL import Image
import os
import time
import numpy as np






# importing keys for ease of use
from pygame.locals import (
	K_UP, # up arrow
	K_DOWN, # down arrow
	K_LEFT, # left arrow
	K_RIGHT, # right arrow
	K_ESCAPE, # escape
	KEYDOWN, # key pressed down
	QUIT, # window close
)





### GAME PARAMETERS ###

# directory contiaining the source files
GAME_DIR = "/home/brindza/Desktop/personal_projects/Games/Space_Invaders/" 
# FPS (frames per second) sets the 
FPS = 25
# the dimensions of the original game window are 224 and 256 pixels
SCALE_FACTOR_X, SCALE_FACTOR_Y = 2, 2
SCALE_FACTOR = ([SCALE_FACTOR_X, SCALE_FACTOR_Y])
WINDOW_SIZE = (224*SCALE_FACTOR_X, 256*SCALE_FACTOR_Y)
# caption of the window
WINDOW_CAPTION = "-----|Space Invaders|-----"
# speed of moving objects
objSpeed = {"alien1" : 1, "alien2" : 1, "alien3" : 1, "player" : 2, "projectile" : 3}
# dimensions of moving objects
objDimension = {
	"alien1" : [5*SCALE_FACTOR_X, 5*SCALE_FACTOR_Y], 
	"alien2" : [5*SCALE_FACTOR_X, 5*SCALE_FACTOR_Y], 
	"alien3" : [5*SCALE_FACTOR_X, 5*SCALE_FACTOR_Y], 
	"player" : [10*SCALE_FACTOR_X, 10*SCALE_FACTOR_Y], 
	"projectile" : [3*SCALE_FACTOR_X, 10*SCALE_FACTOR_Y],
	"bunker" : [30*SCALE_FACTOR_X, 10*SCALE_FACTOR_Y]}







BUTTON_TEXT_COLOR = (0,255,0)
BUTTON_BACKGROUND_COLOR = (255,0,0)
FONT_TYPE = 'freesansbold.ttf'
FONT_SIZE = 24*SCALE_FACTOR_Y
BUTTON_SPACING = 25*SCALE_FACTOR_Y

TEXT_PARAMS = {"BUTTON_TEXT_COLOR" 		: BUTTON_TEXT_COLOR, 
		"BUTTON_BACKGROUND_COLOR" 	: BUTTON_BACKGROUND_COLOR, 
		"FONT_TYPE" 			: FONT_TYPE, 
		"FONT_SIZE" 			: FONT_SIZE, 
		"BUTTON_SPACING" 		: BUTTON_SPACING}




### INITIALIZING MAP ###

# initializing pygame environment
pygame.init()
# setting screen size
screen = pygame.display.set_mode(WINDOW_SIZE)
# setting window caption
pygame.display.set_caption(WINDOW_CAPTION)
