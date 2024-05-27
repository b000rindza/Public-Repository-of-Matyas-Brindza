############################################################
##### The file "readme.txt" contains the documentation #####
############################################################



### IMPORTING PYTHON PACKAGES ###

from interface import *
from objects import *














# GAME ENGINE

def game(result):
	global screen
	
	
	
		
	# define player
	player = Player([WINDOW_SIZE[0]//2, WINDOW_SIZE[1]-100])
	
	
	# list for projectiles
#	projectiles = Projectiles()
	
	
	# rows of aliens :
	No_alien = 14 # No. aliens in a row
	
	r1 = [MovingObject("alien1", [15*SCALE_FACTOR_X*(i+0), 	40 *SCALE_FACTOR_Y]) for i in range(No_alien)]
	r2 = [MovingObject("alien2", [15*SCALE_FACTOR_X*(i+1), 	60 *SCALE_FACTOR_Y]) for i in range(No_alien)]
	r3 = [MovingObject("alien2", [15*SCALE_FACTOR_X*(i+2), 	80 *SCALE_FACTOR_Y]) for i in range(No_alien)]
	r4 = [MovingObject("alien3", [15*SCALE_FACTOR_X*(i+3), 	100*SCALE_FACTOR_Y]) for i in range(No_alien)]
	r5 = [MovingObject("alien3", [15*SCALE_FACTOR_X*(i+4), 	120*SCALE_FACTOR_Y]) for i in range(No_alien)]
	
	aliens = 	[r1, 	r2, 	r3, 	r4, 	r5]
	directions = 	["l", 	"r", 	"l", 	"r", 	"l"]
	
	
	
	
	
	
	# bunkers
	No_bunkers = 4
	spacing_x = WINDOW_SIZE[0]//(No_bunkers+1)
	bunkers = [StaticObject("bunker", [spacing_x*(i+1), 	150*SCALE_FACTOR_Y ]) for i in range(No_bunkers)]

	
	
	
	running = True
	paused = False
	
	start_time = pygame.time.get_ticks()
	print("Staring Game")
	staticScore = static_box("Score : ")
	staticScore.set_coord(WINDOW_SIZE[0]//2-50*SCALE_FACTOR[0], 15*SCALE_FACTOR[1])
	dynamicScore = dynamic_box(str(0))
	dynamicScore.set_coord(WINDOW_SIZE[0]//2+50*SCALE_FACTOR[0], 15*SCALE_FACTOR[1])
	pageGame = page([], [staticScore], [dynamicScore])
	while running:
		screen.fill((0, 0, 0))
		
		# GET KEYS		
		
		for event in pygame.event.get():
			# Check for KEYDOWN event
			if event.type == KEYDOWN:
				# If the Esc key is pressed, then exit the main loop
				if (event.key == K_ESCAPE) or (event.key == pygame.K_p):
					paused = not(paused)
			# Check for QUIT event. If QUIT, then set running to false.
			elif event.type == QUIT:
				running = False
		keys = pygame.key.get_pressed()
		
		
		
		
		
		
		if paused:
			current_page = "Paused"
			next_page = pages[current_page].selection(keys)
			
			if next_page!="NotPressed":
				print(next_page)
				
				if next_page == "Resume":	
					paused = False
				if next_page == "End Game":
					running = False
				if next_page == "Exit":
					result[0] = "Exit"
					return 0
					
			
		else:
		
			# move projectile
			player.projectiles.move()
			# check collision
			player.projectiles.instances, aliens = check_collision(player.projectiles.instances, aliens, player)
					
				
			# move aliens
			for i in range(len(aliens)):
				directions[i] = alien_move(aliens[i], directions[i])
			
			
			# player movement	
			case_handler(player.projectiles.instances, player, keys)
			
			# update bunkers
			update_bunkers(bunkers)
			
			
			# display score
			dynamicScore.set_text(str(player.score))
			pageGame.appear()
		



		
		# update screen
		elapsed_time = pygame.time.get_ticks() - start_time
		pygame.display.flip()
		time.sleep(1/FPS)
		#print(player.score)
		
		
	result[0] = "Game Over"
		
		


### MAIN LOOP ###


running = True
current_page = "Start Page"


# files :
# - player names
# - top 10 high score



while running:
	screen.fill((0, 0, 0))
	
	
	for event in pygame.event.get():
		# Check for KEYDOWN event
		if event.type == KEYDOWN:
			# If the Esc key is pressed, then exit the main loop
			if event.key == K_ESCAPE:
				running = False
		# Check for QUIT event. If QUIT, then set running to false.
		elif event.type == QUIT:
			running = False
	
	keys = pygame.key.get_pressed()
	
	
	next_page = pages[current_page].selection(keys)
	
	if next_page!="NotPressed":
		print(next_page)
		current_page = next_page
	if next_page == "Exit":
		running = False
	if (next_page == "Start Game") or (next_page == "Try Again?"):
		
		#game()
		#current_page = "Game Over"
		
		result = [""]
		game(result)
		
		if result[0] == "Exit":
			running = False
		elif result[0] == "Game Over":
			current_page = "Game Over"
		
	
	
		


	pygame.display.flip()
	time.sleep(2/FPS)





