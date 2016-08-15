#if defined (_WIN32) || (_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#endif

#if defined (__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#endif

#include <string>

using namespace std;

class Bat
{
public:
	bool active;
	bool alive;
	bool attack;
	int health = 3;

	//regulates the attack
	float attackTime = 0.0f;
	float attackRate = 1000.0f; //milliseconds

								//bat texture
	SDL_Texture *texture;

	//rectangle for position and size
	SDL_Rect batRect;

	//bat centerpoint
	SDL_Point batCenter;

	//movement direction
	float xBat;

	//bat speed
	float speed;

	//bat x/y positions
	float batX, batY;

	float angle;

	//calls the bat's texture image and starting location
	Bat(SDL_Renderer *ren, string filePath, float x, float y);

	void Update(float deltaTime, SDL_Rect player);

	void move(float batSpeed, float deltaTime);

	float posX;

	void Draw(SDL_Renderer *ren);


};