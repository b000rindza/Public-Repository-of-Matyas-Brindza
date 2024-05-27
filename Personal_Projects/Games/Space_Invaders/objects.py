from parameters import *





selectedGraphics = "default"




### SINGLE OBJECTS ###

class StaticObject:
	global GAME_DIR, WINDOW_SIZE, SCALE_FACTOR, screen, keys, objSpeed, objDimension, selectedGraphics
	def __init__(self, objType, coord): # initializing object
		
		
		
		
		# graphics
		self.TYPE = objType # {alien1, alien2, alien3, player, projectile, bunker}
		
		
		self.OBJ_DIR = GAME_DIR+"graphics/images/"+str(self.TYPE)+"/"+selectedGraphics+"/"
		
		self.FILES = np.sort(np.array(os.listdir(self.OBJ_DIR)))
		self.health = len(self.FILES)
		
		print(self.FILES)
		self.IMAGES = {}
		
		if len(self.FILES) == 1 :
			self.IMAGES[1] = pygame.image.load(self.OBJ_DIR + str(self.TYPE) + ".png")
		elif len(self.FILES) > 1 :
			for i in range(1,len(self.FILES)+1):
				self.IMAGES[i] = pygame.image.load(self.OBJ_DIR + str(self.TYPE) + "_h="+str(i)+".png")
		
		

		self.WIDTH, self.HEIGHT = self.IMAGES[1].get_width()*SCALE_FACTOR[0], self.IMAGES[1].get_height()*SCALE_FACTOR[1]		
		if len(self.FILES) == 1 :
			self.IMAGES[1] = pygame.transform.scale(self.IMAGES[1], (self.WIDTH, self.HEIGHT ) )
		elif len(self.FILES) > 1 :
			for i in range(1,len(self.FILES)+1):
				self.IMAGES[i] = pygame.transform.scale(self.IMAGES[i], (self.WIDTH, self.HEIGHT ) )
		
		
		#self.WIDTH, self.HEIGHT = objDimension[self.TYPE]
		
		# location
		self.x = coord[0]
		self.y = coord[1]
		
			
		
	def say_hello(self):
		print("Hello! I am a(n) " + self.TYPE + ".")



	def appear(self):
		if self.health > 0:
			screen.blit(self.IMAGES[self.health], (self.x-self.WIDTH//2, self.y-self.HEIGHT//2))
		


	# setter and getter function for coordinates		
	def coord(coordinates):
		self.x = coordinates[0]
		self.y = coordinates[1]
	def coord():
		return np.array([self.x, self.y])
	
	# take damage
	def damage():
		self.health += -1


class MovingObject(StaticObject):
	global objSpeed, objDimension
	def __init__(self, objType, coord): # initializing object
		super().__init__(objType, coord) # call the constructor of the mother class
		
		# set speed
		self.SPEED = objSpeed[self.TYPE]
	
	
	# check if the object reached the edge of the screen
	def check_border(self):
		
		res = False
		
		# HORIZONTAL
		if self.x <= self.WIDTH:
			self.x = self.WIDTH
			res =  True
		if self.x >= WINDOW_SIZE[0]-self.WIDTH:
			self.x = WINDOW_SIZE[0]-self.WIDTH
			res = True
		
		# VERTICAL
		if self.y <= self.HEIGHT:
			self.y = self.HEIGHT
			res = True
		if self.y >= WINDOW_SIZE[1]-self.HEIGHT:
			self.y = WINDOW_SIZE[1]-self.HEIGHT
			res = True
		
		return res
	
	
	# MOVEMENT
	def move_up(self):
		self.y += -1*self.SPEED
		if not(self.check_border()):
			return False
		else:
			return True
	def move_down(self):
		self.y += 1*self.SPEED
		if not(self.check_border()):
			return False
		else:
			return True
	def move_left(self):
		self.x += -1*self.SPEED
		if not(self.check_border()):
			return False
		else:
			return True
	def move_right(self):
		self.x += 1*self.SPEED
		if not(self.check_border()):
			return False
		else:
			return True


class Player(MovingObject):
	def __init__(self, coord):
		super().__init__("player", coord) # call the constructor of the mother class
		# score
		self.score = 0

		self.time_of_last_fire = 0
		
		self.projectiles = Projectiles()
	
	# firing projectile
	def fire(self):
		
		if pygame.time.get_ticks() - self.time_of_last_fire > 150:
			self.projectiles.instances.append( MovingObject( "projectile", [ self.x, self.y-self.HEIGHT//2-objDimension["projectile"][1]//2] ) )
			self.time_of_last_fire = pygame.time.get_ticks()
	
	def appear(self):
		if self.health > 0:
			screen.blit(self.IMAGES[self.health], (self.x-self.WIDTH//2, self.y-self.HEIGHT//2))
		if len(self.projectiles.instances)>0:
			self.projectiles.appear()




class Alien(MovingObject):
	def __init__(self, coord, TYPE, reward):
		super().__init__(TYPE, coord) # call the constructor of the mother class
		
		self.reward = reward
		self.projectiles = Projectiles()
	
	
	# firing projectile
	def fire(self):
		
		if pygame.time.get_ticks() - self.time_of_last_fire > 150:
			self.projectiles.instances.append( MovingObject( "projectile", [ self.x, self.y-self.HEIGHT//2-objDimension["projectile"][1]//2] ) )
			self.time_of_last_fire = pygame.time.get_ticks()
	
	def appear(self):
		if self.health > 0:
			screen.blit(self.IMAGES[self.health], (self.x-self.WIDTH//2, self.y-self.HEIGHT//2))
		if len(self.projectiles.instances)>0:
			self.projectiles.appear() 




#class AlienRow(ObjectBundle):
#	def __init__(self, ListOfAliens):
#		super()__init__()
#		for alien in ListOfAliens:
#			self.add_object(alien)
	
	
		
	

#class AlienGrid(ObjectBundle):
#	def __init__(self, ListOfAlienRows):
#		super()__init__()
#		for alienrow in ListOfAlienRows:
#			self.add_object(alienrow)
#	
#	def move(self):
#		
#		for row in self.instances:
#			row.move()
		
		
		


	
	

### OBJECT BUNDLES ###

class ObjectBundle:
	#def __init__(self, objects):
	#	self.instances = objects

	def __init__(self):
		self.instances = []
	
	
	def add_object(self, obj):
		self.instances.append(obj)
	
	
	def remove_the_dead(self):
		objNo = len(self.instances)
		for i in range(objNo):
			if self.instances[i].health == 0:
				objNo += -1
				self.instances.remove(self.instances[i])
				i += -1
	
	def appear(self):
		self.remove_the_dead()
		for obj in self.instances:
			obj.appear()

class Projectiles(ObjectBundle):
	def __init__(self):
		super().__init__()
	#def __init__(self, objects):
	#	super(objects).__init__()


	
	def move(self):
		for i in self.instances:
			i.move_up()
			i.appear()
	
#	def check_edge(self):
#		self.instances
#			projectiles = [ p for p in projectiles if p.check_border() == False ]
		
	
	def appear(self):
		#self.check_edge(self)
		self.remove_the_dead()
		
		for obj in self.instances:
			obj.appear()
	
	

class Attackers(ObjectBundle): # row of aliens
	def __init__(self):
		super().__init__()
	#def __init__(self, objects):
	#	super(objects).__init__()

	def add(self, obj):
		self.instances.append(obj)
	
#	def add(self) # add multiple objects
		
	def move(self):
		for i in self.instances:
			i.move_up()
			i.appear()



def case_handler(projectiles, player, keys):
#	global keys

	if keys[pygame.K_LEFT] or keys[pygame.K_a]:
		#print("L")
		player.move_left()
	if keys[pygame.K_RIGHT] or keys[pygame.K_d]:
		#print("R")
		player.move_right()
	if keys[pygame.K_DOWN] or keys[pygame.K_s]:
		#print("D")
		player.move_down()
	if keys[pygame.K_UP] or keys[pygame.K_w]:
		#print("U")
		player.move_up()
	if keys[pygame.K_SPACE]:
		#print("F")
		player.fire()
		
	player.appear()


def alien_move(a, direction ="l"):
	
	if not(a):
		return direction
	
	if a[0].x <= a[0].WIDTH:
		for i in a:
			i.move_right()
			direction = "r"
	if a[-1].x >= WINDOW_SIZE[0] - a[0].WIDTH:
		for i in a:
			i.move_left()
			direction = "l"

	if direction =="l":
		for i in a:
			i.move_left()
	if direction =="r":
		for i in a:
			i.move_right()

	for i in a:
		i.appear()
		#screen.blit(i.IMAGE, (i.x+i.WIDTH//2, i.y-i.HEIGHT//2))
		
	return direction
	






def check_hit_alien(alien, player):
	
	destroyed_projectile = -1
	hit = False
	if len(player.projectiles.instances)>0:
		for p in range(len(player.projectiles.instances)): # iterate projectiles
			if (  ( np.abs(alien.x-player.projectiles.instances[p].x) < (alien.WIDTH + player.projectiles.instances[p].WIDTH)//2 ) 
			  and ( np.abs(alien.y-player.projectiles.instances[p].y) < (alien.HEIGHT + player.projectiles.instances[p].HEIGHT)//2 )  ):
				hit = True
		if hit:	
			player.projectiles.instances.pop(destroyed_projectile)
			if alien.TYPE == "alien1":
				player.score += 30
			if alien.TYPE == "alien2":
				player.score += 20
			if alien.TYPE == "alien3":
				player.score += 10
	return hit


def check_collision(projectiles, aliens, player):
	
	for row in range(len(aliens)): # iterate rows
		aliens[row] = [ alien for alien in aliens[row] if not(check_hit_alien(alien, player)) ]

	
	



	return projectiles, aliens







def update_bunkers(bunkers):
	
	for b in bunkers:
		b.appear()

