from parameters import *



# button
# static_box
# dynamic_box



# button object
class button:
	global WINDOW_SIZE, TEXT_PARAMS, screen
	def __init__(self, TEXT): # initializing object
				
		# location
		self.COORD = [0, 0]
		
		# text
		self.TEXT = TEXT
		
		# selection
		self.selected = False
		
	
	def select(self):
		self.selected = True
	def deselect(self):
		self.selected = False

	def appear(self):
		# create a text surface object,
		# on which text is drawn on it.
		font = pygame.font.Font(TEXT_PARAMS["FONT_TYPE"], TEXT_PARAMS["FONT_SIZE"])
		
		if self.selected == False :
			self.PYTEXT = font.render(self.TEXT, True, TEXT_PARAMS["BUTTON_TEXT_COLOR"], TEXT_PARAMS["BUTTON_BACKGROUND_COLOR"])
		if self.selected ==	True :
			 self.PYTEXT = font.render(self.TEXT, True, TEXT_PARAMS["BUTTON_BACKGROUND_COLOR"], TEXT_PARAMS["BUTTON_TEXT_COLOR"])
		# create a rectangular object for the
		# text surface object
		self.TEXT_RECT = self.PYTEXT.get_rect()
		
		# set the center of the rectangular object.
		self.TEXT_RECT.center = (self.COORD[0], self.COORD[1])


		screen.blit(self.PYTEXT, self.TEXT_RECT)
	
	def set_coord(self,x, y):
		self.COORD = [x, y]
	
	
	def alignCenterHorizontal(self):
		self.COORD = [WINDOW_SIZE[0]//2, self.COORD[1]]
	def alignCenterVertical(self):
		self.COORD = [self.COORD[0], WINDOW_SIZE[1]//2]


# static text box
class static_box:
	global WINDOW_SIZE, TEXT_PARAMS, screen
	def __init__(self, TEXT): # initializing object
				
		# location
		self.COORD = [0, 0]
		# text
		self.TEXT = TEXT
		
	
	def appear(self):
		# create a text surface object,
		# on which text is drawn on it.
		font = pygame.font.Font(TEXT_PARAMS["FONT_TYPE"], TEXT_PARAMS["FONT_SIZE"])
		
		self.PYTEXT = font.render(self.TEXT, True, TEXT_PARAMS["BUTTON_TEXT_COLOR"], (0,0,0))
		
		
		# create a rectangular object for the
		# text surface object
		self.TEXT_RECT = self.PYTEXT.get_rect()
		
		# set the center of the rectangular object.
		self.TEXT_RECT.center = (self.COORD[0], self.COORD[1])

		# pass object to display
		screen.blit(self.PYTEXT, self.TEXT_RECT)
	
	
	def set_coord(self,x, y):
		self.COORD = [x, y]
	
	def alignCenterHorizontal(self):
		self.COORD = [WINDOW_SIZE[0]//2, self.COORD[1]]
	def alignCenterVertical(self):
		self.COORD = [self.COORD[0], WINDOW_SIZE[1]//2]
		
		


# dynamic text box
class dynamic_box:
	global WINDOW_SIZE, TEXT_PARAMS, screen
	def __init__(self, TEXT): # initializing object
				
		# location
		self.COORD = [0, 0]
		# text
		self.text = TEXT
		
	
	def appear(self):
		# create a text surface object,
		# on which text is drawn on it.
		font = pygame.font.Font(TEXT_PARAMS["FONT_TYPE"], TEXT_PARAMS["FONT_SIZE"])
		
		self.PYTEXT = font.render(self.text, True, TEXT_PARAMS["BUTTON_TEXT_COLOR"], (0,0,0))
		
		
		# create a rectangular object for the
		# text surface object
		self.TEXT_RECT = self.PYTEXT.get_rect()
		
		# set the center of the rectangular object.
		self.TEXT_RECT.center = (self.COORD[0], self.COORD[1])

		# pass object to display
		screen.blit(self.PYTEXT, self.TEXT_RECT)
	
	
	def set_coord(self, x, y):
		self.COORD = [x, y]
	def set_text(self, text):
		self.text = text


	def alignCenterHorizontal(self):
		self.COORD = [WINDOW_SIZE[0]//2, self.COORD[1]]
	def alignCenterVertical(self):
		self.COORD = [self.COORD[0], WINDOW_SIZE[1]//2]




# input text box
class input_box:
	global WINDOW_SIZE, TEXT_PARAMS, screen
	def __init__(self): # initializing object
				
		# location
		self.COORD = [0, 0]
		
		# text
		self.TEXT = "Enter Name"
		
		# selection
		self.selected = False
		
		# input
		self.input = ""
		
	
	def select(self):
		self.selected = True
	def deselect(self):
		self.selected = False

	def appear(self):
		# create a text surface object,
		# on which text is drawn on it.
		font = pygame.font.Font(TEXT_PARAMS["FONT_TYPE"], TEXT_PARAMS["FONT_SIZE"])
		
		if self.input == "":
			self.TEXT = "Enter Name"
		else:
			self.TEXT = self.input
		
		
		
		if self.selected == False :
			self.PYTEXT = font.render(self.TEXT, True, TEXT_PARAMS["BUTTON_TEXT_COLOR"], TEXT_PARAMS["BUTTON_BACKGROUND_COLOR"])
		if self.selected ==	True :
			 self.PYTEXT = font.render(self.TEXT, True, TEXT_PARAMS["BUTTON_BACKGROUND_COLOR"], TEXT_PARAMS["BUTTON_TEXT_COLOR"])
		# create a rectangular object for the
		# text surface object
		self.TEXT_RECT = self.PYTEXT.get_rect()
		
		# set the center of the rectangular object.
		self.TEXT_RECT.center = (self.COORD[0], self.COORD[1])


		screen.blit(self.PYTEXT, self.TEXT_RECT)
	
	
	def set_coord(self, x, y):
		self.COORD = [x, y]
	def set_text(self, text):
		self.text = text


	def alignCenterHorizontal(self):
		self.COORD = [WINDOW_SIZE[0]//2, self.COORD[1]]
	def alignCenterVertical(self):
		self.COORD = [self.COORD[0], WINDOW_SIZE[1]//2]

	
	def input(char):
		if char == pygame.K_BACKSPACE:
			self.input = self.input[:-1]
		else:
			self.input += char.unicode


	
	


class page:
	global WINDOW_SIZE, TEXT_PARAMS, screen, paused
	def __init__(self, BUTTONS, STATIC_BOXES = [], DYNAMIC_BOXES = [], INPUT_BOXES = []): # initializing object
		
		
		self.BUTTONS, self.STATIC_BOXES, self.DYNAMIC_BOXES, self.INPUT_BOXES = [], [], [], []
		

		if BUTTONS:
			self.BUTTONS = BUTTONS
		
			self.selected_button = 0
			self.BUTTONS[self.selected_button].select()
		
			# arrange buttons along the screen
			button_x = WINDOW_SIZE[0]//2
			No_buttons = len(self.BUTTONS)
			#window_center = [ WINDOW_SIZE[0]//2, WINDOW_SIZE[1]//2 ]
			height = No_buttons*TEXT_PARAMS["FONT_SIZE"] + (No_buttons-1)*TEXT_PARAMS["BUTTON_SPACING"]
			
			for b in range(len(self.BUTTONS)):
				self.BUTTONS[b].set_coord(button_x, (b+1)*TEXT_PARAMS["FONT_SIZE"] + b*TEXT_PARAMS["BUTTON_SPACING"] - height//2 + WINDOW_SIZE[1]//2)
				#print(self.BUTTONS[b].COORD)		
		if STATIC_BOXES:
			self.STATIC_BOXES = STATIC_BOXES
		if DYNAMIC_BOXES:
			self.DYNAMIC_BOXES = DYNAMIC_BOXES
		if not(BUTTONS) and not(STATIC_BOXES) and not(DYNAMIC_BOXES):
			return "Page is empty!"
		
				
		
	def appear(self):
		if self.BUTTONS:
			for button in self.BUTTONS:
				button.appear()
		if self.STATIC_BOXES:
			for static in self.STATIC_BOXES:
				static.appear()
		if self.DYNAMIC_BOXES:
			for dynamic in self.DYNAMIC_BOXES:
				dynamic.appear()
		
	
	def selection(self, keys):
		if self.BUTTONS:
			self.appear()
			# move selection down
			if keys[pygame.K_DOWN] or keys[pygame.K_s]:
				#print("D")
				if self.selected_button < len(self.BUTTONS)-1:
					self.BUTTONS[self.selected_button].deselect()
					self.selected_button += 1
					self.BUTTONS[self.selected_button].select()
			
			# move selection up
			if keys[pygame.K_UP] or keys[pygame.K_w]:
				#print("W")
				if self.selected_button > 0:
					self.BUTTONS[self.selected_button].deselect()
					self.selected_button += -1
					self.BUTTONS[self.selected_button].select()
	
			if (keys[pygame.K_SPACE]) or (keys[pygame.K_RETURN]):
				#print("F")
				return self.BUTTONS[self.selected_button].TEXT
			#for i in self.BUTTONS:
			#	print(i.TEXT)
			self.appear()
			return "NotPressed"






buttonStartGame = button("Start Game")
buttonHighScore = button("HighScores")
buttonOptions 	= button("Options")
buttonAbout 	= button("About")
buttonExit	= button("Exit")

pageStartPage 	= page([buttonStartGame, buttonHighScore, buttonOptions, buttonAbout, buttonExit])



buttonMusicVolume 	= button("Music volume")
buttonSoundVolume 	= button("Sound volume")
buttonSetScreenSize 	= button("Set screen size")
buttonSetColors 	= button("Set colors")

pageOptions 		= page([buttonMusicVolume, buttonSoundVolume, buttonSetScreenSize, buttonSetColors])



buttonEmpty 	= button("")
pageStartGame 	= page([buttonEmpty])
pageResume 	= page([buttonEmpty])




staticGameOver 	= static_box("Game Over")
staticGameOver.set_coord(WINDOW_SIZE[0]//2-50*SCALE_FACTOR[0], 25*SCALE_FACTOR[1])
staticGameOver.alignCenterHorizontal()

buttonTryAgain 	= button("Try Again?")
buttonMainMenu 	= button("Main Menu")
buttonExit	= button("Exit")
pageGameOver 	= page([buttonTryAgain, buttonMainMenu, buttonExit], [staticGameOver])




staticGamePaused 	= static_box("Game Paused")
staticGamePaused.set_coord(WINDOW_SIZE[0]//2-50*SCALE_FACTOR[0], 25*SCALE_FACTOR[1])
staticGamePaused.alignCenterHorizontal()


buttonResume 		= button("Resume")
buttonEndGame		= button("End Game")
buttonExit		= button("Exit")
pagePaused		= page([buttonResume, buttonEndGame, buttonExit], [staticGamePaused])








pages = {
	"Start Page" 	: pageStartPage, 
	"Options" 	: pageOptions, 
	"Game Over" 	: pageGameOver, 
	"Start Game" 	: pageStartGame, 
	"Try Again?" 	: pageStartGame, 
	"Main Menu" 	: pageStartPage, 
	"Paused" 	: pagePaused
	}























