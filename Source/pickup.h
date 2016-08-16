#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#if defined(_WIN32) || (_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <string>

using namespace std;

class Pickup
{
public:
	bool active;

	SDL_Texture *pickup;

	SDL_Rect pickupRect;

	float pickupX, pickupY;

	Pickup(SDL_Renderer *ren, string filePath, int itemNum, float x, float y);

	void Update(float deltaTime);

	void move(float pickupSpeed, float deltaTime);

	float posX, posY;

	void Draw(SDL_Renderer *ren);
};