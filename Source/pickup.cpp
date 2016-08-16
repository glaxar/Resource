#include "pickup.h"

Pickup::Pickup(SDL_Renderer *ren,  string filePath, int itemNum, float x, float y)
{
	if (itemNum == 0)
	{
		string crossPath = filePath + "cross.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(crossPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}

	if (itemNum == 0)
	{
		string keyPath = filePath + "key.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(keyPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}

	if (itemNum == 0)
	{
		string rockPath = filePath + "rock.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(rockPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}

	if (itemNum == 0)
	{
		string healthPath = filePath + "health.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(healthPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}

	if (itemNum == 0)
	{
		string ammoPath = filePath + "ammo.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(ammoPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);
	}

	//The rectangle which has the xPos, yPos, texture width and texture height - bat1
	pickupRect.x = x;
	pickupRect.y = y;
	pickupRect.w = 30;
	pickupRect.h = 30;
	posX = x;
	posY = y;
}