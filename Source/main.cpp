#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"

#endif

#if defined(_WIN32) || (_WIN64)

#include <direct.h>
#define getcwd _getcwd

#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "unistd.h"

#endif

#include <stdio.h>
#include <iostream>
#include <ctime>

#include "bat.h"
#include "pickup.h"

using namespace std;

//variables for the background movement and position
//int for background
int bgSpeed = 100;

//Create the SDL rectangle for the background texture's position and size - background1
SDL_Rect bg1Pos, playerRect, pBulletPos, tBulletPos, turretRect, eBulletRect, crossPos, keyPos, rockPos;


int playerVel = 4;
float playerX = 0.0f;
float playerY = 0.0f;

// boolean to see if the turret is active
bool turretActive = false, crossInvActive = false, keyInvActive = false, rockInvActive = false, crossActive = true, keyActive = true, rockActive = true;

//basic vars for simple player(p)/enemy(e) bullet fire with 1 bullet each
bool eBulletActive = true;
bool pBulletActive = true;

int eBulletDir = 0;
int pBulletDir = 0;

// vars for playerHealth and bullet health
int pHealth = 10;
int eHealth = 5;

int pAmmo = 8;

//regulates the attack
float attackTime = 0.0f;
float attackRate = 1000.0f; //milliseconds

//Background float vars for movement
float b1Pos_X = 0, b1Pos_Y = -768;
//float b2Pos_X = 0, b2Pos_Y = -768;

//deltaTime var initialization - for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

void Background(float deltaTime)
{
	//Update bg1 float position values
	b1Pos_Y += (bgSpeed * 1) * deltaTime;
	bg1Pos.y = (int)(b1Pos_Y + 0.5f);

//	//Reset the float position values of bg1 when off the bottom of the screen
//	if (bg1Pos.y >= 768)
//	{
//		bg1Pos.y = -768;
//		b1Pos_Y = bg1Pos.y;
//	}
}

//class turret
//{
//	//turret active?
//	bool active = false;
//
//	//turret health
//	int tHealth = 10;
//
//	//random number seed
//	//srand(time(NULL));
//};

//class player
//{
//	int pHealth = 10;
//
//};

void playerHit()
{
	//player hurt
	pHealth -= 1;
	cout << pHealth << endl;
}

int main(int argc, char* argv[]) {

#if defined(_WIN32) || (_WIN64)

	cout << "Running on Windows..." << endl;
	cout << "Added on Windows..." << endl;

	string currentWorkingDirectory(getcwd(NULL, 0));

	string images_dir = currentWorkingDirectory + "\\Resource\\Images\\";

#endif

#if defined(__APPLE__)

	cout << "Running on Apple..." << endl;

	//String var to hold the current working directory on __APPLE__
	string currentWorkingDirectory(getcwd(NULL, 0));

	//Create a string to link to the images folder on __APPLE__
	string images_dir = currentWorkingDirectory + "/Resource/Images/";

#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"Into The Cave",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		1024,                               // width, in pixels
		768,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	//Create a renderer variable - pointer
	SDL_Renderer *ren = NULL;

	//Create renderer
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/////////////////Create Backgrounds - START

	//Create the SDL surface to hold the texture file
	SDL_Surface *surface = IMG_Load((images_dir + "background.png").c_str());

	//Create in game texture - background 1
	SDL_Texture *background1;

	//Place surface with image to display in the texture
	background1 = SDL_CreateTextureFromSurface(ren, surface);

	//free the SDL surface
	SDL_FreeSurface(surface);

	//The rectangle which has the xPos, yPos, texture width and texture height - background1
	bg1Pos.x = 0;
	bg1Pos.y = -768;
	bg1Pos.w = 3072;
	bg1Pos.h = 2304;


	/////////////////Create Backgrounds - END

	//create a SDL surface to hold the player image
	SDL_Surface *surface2 = IMG_Load((images_dir + "player.png").c_str());

	// SDL Texture
	SDL_Texture *player;

	//place surface info into the texture bkdg1
	player = SDL_CreateTextureFromSurface(ren, surface2);

	//free the SDL surface
	SDL_FreeSurface(surface2);

	// Set the x, y, width and height SDL Rectangle values
	playerRect.x = 200;
	playerRect.y = 370;
	playerRect.w = 85;
	playerRect.h = 85;

	/////////////////Create turret - START

	//Create the SDL surface to hold the texture file
	SDL_Surface *surface3 = IMG_Load((images_dir + "turret.png").c_str());

	//Create in game texture - turret
	SDL_Texture *turret;

	//Place surface with image to display in the texture
	turret = SDL_CreateTextureFromSurface(ren, surface3);

	//free the SDL surface
	SDL_FreeSurface(surface3);

	//The rectangle which has the xPos, yPos, texture width and texture height - turret1
	turretRect.x = 400;
	turretRect.y = 340;
	turretRect.w = 85;
	turretRect.h = 85;

	/////////////////Create turret - END

	/////////////////Create bat - START

	Bat bat1 = Bat(ren, images_dir.c_str(), 300, 370);

	/////////////////Create bat - END

	/////////////////Create HUD - START
	
	Pickup cross = Pickup(ren, images_dir.c_str(), 0, 480, 370);
	Pickup key = Pickup(ren, images_dir.c_str(), 1, 80, 370);
	Pickup rock = Pickup(ren, images_dir.c_str(), 2, 580, 370);
	Pickup health = Pickup(ren, images_dir.c_str(), 3, 250, 320);
	Pickup ammo = Pickup(ren, images_dir.c_str(), 4, 250, 350);
	Pickup invHUD = Pickup(ren, images_dir.c_str(), 5, 100, 100);
	Pickup healthBottle = Pickup(ren, images_dir.c_str(), 6, 100, 550);
	Pickup healthRed = Pickup(ren, images_dir.c_str(), 7, 100, 550);
	Pickup ammoHUD = Pickup(ren, images_dir.c_str(), 8, 900, 550);
	Pickup crossI = Pickup(ren, images_dir.c_str(), 0, 40, 60);
	Pickup keyI = Pickup(ren, images_dir.c_str(), 1, 160, 60);
	Pickup rockI = Pickup(ren, images_dir.c_str(), 2, 100, 160);


	/////////////////Create HUD - END

	//Create the SDL surface to hold the texture file
		SDL_Surface *surface = IMG_Load((images_dir + "cross.png").c_str());

		//Create in game texture - background 1
		SDL_Texture *cross;

		//Place surface with image to display in the texture
		cross = SDL_CreateTextureFromSurface(ren, surface);

		//free the SDL surface
		SDL_FreeSurface(surface);

		//The rectangle which has the xPos, yPos, texture width and texture height - inventory cross
		bg1Pos.x = 40;
		bg1Pos.y = 60;
		bg1Pos.w = 40;
		bg1Pos.h = 40;

	/////////////////Create player bullet - START

	//Create the SDL surface to hold the texture file
	SDL_Surface *surface4 = IMG_Load((images_dir + "pbullet.png").c_str());

	//Create in game texture - turret
	SDL_Texture *pBullet;

	//Place surface with image to display in the texture
	pBullet = SDL_CreateTextureFromSurface(ren, surface4);

	//free the SDL surface
	SDL_FreeSurface(surface4);

	//The rectangle which has the xPos, yPos, texture width and texture height - background1
	pBulletPos.x = -200;
	pBulletPos.y = -768;
	pBulletPos.w = 32;
	pBulletPos.h = 32;

	/////////////////Create player bullet - END

	/////////////////Create enemy bullet - START

	//Create the SDL surface to hold the texture file
	SDL_Surface *surface5 = IMG_Load((images_dir + "tbullet.png").c_str());

	//Create in game texture - turret
	SDL_Texture *tBullet;

	//Place surface with image to display in the texture
	tBullet = SDL_CreateTextureFromSurface(ren, surface5);

	//free the SDL surface
	SDL_FreeSurface(surface5);

	//The rectangle which has the xPos, yPos, texture width and texture height
	tBulletPos.x = -200;
	tBulletPos.y = -200;
	tBulletPos.w = 16;
	tBulletPos.h = 16;

	/////////////////Create enemy bullet - END

	crossPos.x = 70;
	crossPos.y = 120;
	crossPos.w = 70;
	crossPos.h = 70;

	keyPos.x = 130;
	keyPos.y = 120;
	keyPos.w = 70;
	keyPos.h = 70;

	rockPos.x = 100;
	rockPos.y = 120;
	rockPos.w = 70;
	rockPos.h = 70;

//    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
//    int x = 0, y = 0;
	//SDL_Surface *background = 0;

	////The surface contained by the window
	//SDL_Surface* screenSurface = NULL;
	////Image to load on screen
	//SDL_Surface* background = NULL;
	//
	////Get window surface
	//screenSurface = SDL_GetWindowSurface(window);
	//
	////Fill the surface white
	//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 42, 254));
	//
	////Update the surface
	//SDL_UpdateWindowSurface(window);

	// The window is open: could enter program loop here (see SDL_PollEvent())

	//event to handle input
	SDL_Event event;

	bool running = true;
	while (running)
	{


		while (SDL_PollEvent(&event) != 0)
		{
			//check to see if the SDL Window is closed - player clicks X in window
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else {
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0)//key pressed
				{
					switch (event.key.keysym.sym)
					{
						//case keyboard movement
					case SDLK_ESCAPE:
						running = false;
						break;
						//move right
					case SDLK_RIGHT:
						playerX += playerVel;
						break;
						//move left
					case SDLK_LEFT:
						playerX -= playerVel;
						break;
					case SDLK_SPACE:
						// check to see if bullet is not already active
						if (pBulletActive == false && pAmmo > 0)
						{

							// move to player's position
							pBulletPos.x = playerRect.x;
							pBulletPos.y = (playerRect.y + (playerRect.h / 2));

							// check to see if the player is to the left or right of the turret and set the
							// player's bulletDir as needed
							if (playerX < turretRect.x) {
								pBulletDir = 5;
							}
							else {
								pBulletDir = -5;
							}
							// active bullet
							pBulletActive = true;

							pAmmo -= 1;
							cout << pAmmo << endl;
						}
						break;
					}
				}
				else if (event.type == SDL_KEYUP && event.key.repeat == 0)//key released
				{
					switch (event.key.keysym.sym)
					{
						//move right
					case SDLK_RIGHT:
					{
						if (pBulletActive == false)
						{
							pBulletDir = 5;
						}
						playerX -= playerVel;
					}
						break;
						//move left
					case SDLK_LEFT:
					{
						if (pBulletActive == false)
						{
							pBulletDir = -5;
						}
						playerX += playerVel;
					}
						break;
					}
				}
			}
		}

		Background(deltaTime);

		playerRect.x += playerX;

		if (playerRect.x < 30)
		{
			playerRect.x = 35;
		}

		if (playerRect.x > 950)
		{
			playerRect.x = 945;
		}

		//distance to player
		double distancex = ((turretRect.x + (turretRect.w / 2))
			- (playerRect.x + (playerRect.w / 2)))
			* ((turretRect.x + (turretRect.w / 2))
				- (playerRect.x + (playerRect.w / 2)));
		double distancey = (turretRect.y - playerRect.y)
			* (turretRect.y - playerRect.y);

		double calcdistance = sqrt(distancex + distancey);

		if (calcdistance <= 230 && eHealth >= 1) {
			turretActive = true;
			//cout << turretActive << endl;

			//random number 1 - 10 (higher number, slower fire rate
			int random_number = std::rand() % 5;

			// check to see if bullet is not already active and random number equals 5
			if ((eBulletActive) == false && (random_number == 5)) {

				// move to player's position
				tBulletPos.x = turretRect.x;
				tBulletPos.y = (turretRect.y + (turretRect.h / 2));

				// check to see if the player is to the left or right of the turret and set the
				// player's bulletDir as needed
				if (playerRect.x < turretRect.x) {
					eBulletDir = -5;
				}
				else {
					eBulletDir = 5;
				}
				// active bullet
				eBulletActive = true;
			}

		}
		else {
			turretActive = false;
		}
		//if the enemy bullet is active - update
		if (eBulletActive) {
			tBulletPos.x += eBulletDir;
		}

		// check for off screen - LEFT or RIGHT
		if (tBulletPos.x > 1024 || tBulletPos.x < 0) {
			eBulletActive = false;
			tBulletPos.x = -200;
			tBulletPos.y = -200;
			eBulletDir = 0;
		}

		//cout << bat1.active << endl;
		bat1.Update(deltaTime, playerRect);

		//if the player bullet is active - update
		if (pBulletActive) {
			pBulletPos.x += pBulletDir;
		}

		// check for off screen - LEFT or RIGHT
		if (pBulletPos.x > 1024 || pBulletPos.x < 0) {
			pBulletActive = false;
			pBulletPos.x = -100;
			pBulletPos.y = -100;
			pBulletDir = 0;
		}

		//player collision with turret bullet
		if (SDL_HasIntersection(&playerRect, &tBulletPos)) {

			//reset enemy bullet
			eBulletActive = false;
			tBulletPos.x = -200;
			tBulletPos.y = -200;
			eBulletDir = 0;

			//player hurt
			pHealth -= 1;
			cout << pHealth << endl;

		}

		//turret collision with player bullet while active
		if (SDL_HasIntersection(&turretRect, &pBulletPos) && turretActive == true) {

			//reset player bullet
			pBulletActive = false;
			pBulletPos.x = -200;
			pBulletPos.y = -200;
			pBulletDir = 0;

			//subtract player health
			eHealth -= 1;
			cout << eHealth << endl;
			//if (eHealth <= 0)
			//	turretActive = false;
		}

		//turret collision with player bullet while NOT active
		if (SDL_HasIntersection(&turretRect, &pBulletPos) && turretActive == false) {

			////reset player bullet
			//pBulletActive = false;
			//pBulletPos.x = -200;
			//pBulletPos.y = -200;
			//pBulletDir = 0;
		}

		//bat collision with player
		if (SDL_HasIntersection(&playerRect, &bat1.batRect)) {
			if (SDL_GetTicks() > attackTime)
			{
				playerHit();
				attackTime = SDL_GetTicks() + 1000;
			}
		}

		//bat collision with player bullet while active
		if (SDL_HasIntersection(&bat1.batRect, &pBulletPos) && bat1.alive == true) {

			//reset player bullet
			pBulletActive = false;
			pBulletPos.x = -200;
			pBulletPos.y = -200;
			pBulletDir = 0;

			//subtract player health
			bat1.health -= 1;
			cout << bat1.health << endl;
			//if (eHealth <= 0)
			//	turretActive = false;
		}

		//player collision with turret bullet
				if (SDL_HasIntersection(&playerRect, &tBulletPos)) {

					//reset enemy bullet
					crossActive = false;
					crossInvActive = true;
					tBulletPos.x = -200;
					tBulletPos.y = -200;
					eBulletDir = 0;


				}
				//player collision with turret bullet
						if (SDL_HasIntersection(&playerRect, &tBulletPos)) {

							//reset enemy bullet
							keyActive = false;
							keyInvActive = true;
							tBulletPos.x = -200;
							tBulletPos.y = -200;
							eBulletDir = 0;


						}
						//player collision with turret bullet
						if (SDL_HasIntersection(&playerRect, &tBulletPos)) {

							//reset enemy bullet
							rockActive = false;
							rockInvActive = true;
							tBulletPos.x = -200;
							tBulletPos.y = -200;
							eBulletDir = 0;


						}
		if(SDL_HasIntersection(&health.healthRect, &playerRect))
		{
			pHealth = 10;
		}

		if(SDL_HasIntersection(&ammo.ammoRect, &playerRect))
		{
			pAmmo = 8;
		}

		Background(deltaTime);

		SDL_RenderClear(ren);

		SDL_RenderCopy(ren, background1, NULL, &bg1Pos);

		if (bat1.health > 0)
		{
			bat1.Draw(ren);
		}

		if(cross.active == true)
		{
			cross.Draw(ren);
		}
		if(key.active == true)
		{
			key.Draw(ren);
		}
		if(rock.active == true)
		{
			rock.Draw(ren);
		}
		if(health.active == true)
		{
			health.Draw(ren);
		}
		if(ammo.active == true)
		{
			ammo.Draw(ren);
		}
		if(invHUD.active == true)
		{
			invHUD.Draw(ren);
		}

		if(healthRed.active == true)
		{
			healthRed.Draw(ren);
		}
		if(healthBottle.active == true)
		{
			healthBottle.Draw(ren);
		}
		if(ammoHUD.active == true)
		{
			ammoHUD.Draw(ren);
		}

		//draw enemy bullet
		if (eBulletActive) {
			SDL_RenderCopy(ren, tBullet, NULL, &tBulletPos);
		}

		//draw player bullet
		if (pBulletActive) {
			SDL_RenderCopy(ren, pBullet, NULL, &pBulletPos);
		}

		if (pHealth > 0)
		{
			SDL_RenderCopy(ren, player, NULL, &playerRect);
		}

		if (eHealth > 0)
		{
			SDL_RenderCopy(ren, turret, NULL, &turretRect);
		}
		if(crossI.active == true)
		{
			crossI.Draw(ren);
		}
		if(keyI.active == true)
		{
			keyI.Draw(ren);
		}
		if(rockI.active == true)
		{
			rockI.Draw(ren);
		}

		SDL_RenderPresent(ren);

		// Delay so that we are at 60 FPS
		SDL_Delay(16);
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
