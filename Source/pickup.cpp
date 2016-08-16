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

		crossRect.x = x;
		crossRect.y = y;
		crossRect.w = 30;
		crossRect.h = 30;
	}

	if (itemNum == 1)
	{
		string keyPath = filePath + "key.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(keyPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);

		keyRect.x = x;
		keyRect.y = y;
		keyRect.w = 30;
		keyRect.h = 30;
	}

	if (itemNum == 2)
	{
		string rockPath = filePath + "rock.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(rockPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);

		rockRect.x = x;
		rockRect.y = y;
		rockRect.w = 30;
		rockRect.h = 30;
	}

	if (itemNum == 3)
	{
		string healthPath = filePath + "health.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(healthPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);

		healthRect.x = x;
		healthRect.y = y;
		healthRect.w = 30;
		healthRect.h = 30;
	}

	if (itemNum == 4)
	{
		string ammoPath = filePath + "ammo.png";

		//put the texture on a surface
		SDL_Surface *surface = IMG_Load(ammoPath.c_str());

		pickup = SDL_CreateTextureFromSurface(ren, surface);

		SDL_FreeSurface(surface);

		ammoRect.x = x;
		ammoRect.y = y;
		ammoRect.w = 30;
		ammoRect.h = 30;
	}

	if (itemNum == 5)
		{
			string invHUDPath = filePath + "inventory.png";

			//put the texture on a surface
			SDL_Surface *surface = IMG_Load(invHUDPath.c_str());

			pickup = SDL_CreateTextureFromSurface(ren, surface);

			SDL_FreeSurface(surface);

			invHUDRect.x = x;
			invHUDRect.y = y;
			invHUDRect.w = 30;
			invHUDRect.h = 30;

		}

	if (itemNum == 6)
		{
			string healthBPath = filePath + "healthBottle.png";

			//put the texture on a surface
			SDL_Surface *surface = IMG_Load(healthBPath.c_str());

			pickup = SDL_CreateTextureFromSurface(ren, surface);

			SDL_FreeSurface(surface);

			hBotRect.x = x;
			hBotRect.y = y;
			hBotRect.w = 30;
			hBotRect.h = 30;

		}

	if (itemNum == 7)
		{
			string healthRPath = filePath + "healthRed.png";

			//put the texture on a surface
			SDL_Surface *surface = IMG_Load(healthRPath.c_str());

			pickup = SDL_CreateTextureFromSurface(ren, surface);

			SDL_FreeSurface(surface);

			hRedRect.x = x;
			hRedRect.y = y;
			hRedRect.w = 30;
			hRedRect.h = 30;

		}

	if (itemNum == 8)
			{
				string ammoHUDPath = filePath + "ammoHUD.png";

				//put the texture on a surface
				SDL_Surface *surface = IMG_Load(ammoHUDPath.c_str());

				pickup = SDL_CreateTextureFromSurface(ren, surface);

				SDL_FreeSurface(surface);

			}

	//The rectangle which has the xPos, yPos, texture width and texture height - bat1
	pickupRect.x = x;
	pickupRect.y = y;
	pickupRect.w = 70;
	pickupRect.h = 70;
	posX = x;
	posY = y;
}

void Pickup::Draw(SDL_Renderer *ren)
{
	SDL_RenderCopy(ren, pickup, NULL, &pickupRect);
}
