#include "bat.h"

Bat::Bat(SDL_Renderer *ren, string filePath, float x, float y)
{
	string batPath = filePath + "bat1.png";

	//put the texture on a surface
	SDL_Surface *surface8 = IMG_Load(batPath.c_str());

	texture = SDL_CreateTextureFromSurface(ren, surface8);

	SDL_FreeSurface(surface8);

	//The rectangle which has the xPos, yPos, texture width and texture height - bat1
	batRect.x = x;
	batRect.y = y;
	batRect.w = 30;
	batRect.h = 30;

	//initialize bat direction
	xBat = 1;

	//calculate bat center
	batCenter.x = batRect.w / 2;
	batCenter.y = batRect.h / 2;

	speed = 10;
}

void Bat::move(float batSpeed, float deltaTime)
{
	posX += batSpeed * deltaTime;

	batRect.x = (int)(posX + 0.5f);
}


void Bat::Update(float deltaTime, SDL_Rect player)
{
	double distX = batRect.x - player.x;

	if (distX <= 240)
	{
		active = true;
	}
	else
	{
		active = false;
	}

	if (active == true)
	{
		float moveX = speed;
		posX += moveX * deltaTime;
		batRect.x = (int)(posX + 0.5f);
	}

	if (SDL_GetTicks() > attackTime)
	{
		attackTime = SDL_GetTicks() + 2000;
	}
}

//void Bat::bite()
//{
//
//}

void Bat::Draw(SDL_Renderer *ren)
{
	SDL_RenderCopyEx(ren, texture, NULL, &batRect, 0, &batCenter, SDL_FLIP_NONE);

}