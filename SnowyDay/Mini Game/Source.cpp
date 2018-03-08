#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#define HEIGHT 4320
#define WEIGHT 600


	
int main(int argc, char* argv[]) {
		//INICIALIZAR
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	//Audio

		//LOCAL VAR
	int x_ball = 275, y_ball = 50, x_background = 0, y_background = 0, x_pickup = 0, y_pickup = 0, x_snowman = 0, y_snowman = 525, x_sled = 255, y_sled = 0; //Position
	int ball_h = 50, ball_w = 50, cont_background = 0; //Part of h&w
	bool loop=true, key_left=false, key_right=false; //Part of Loop
	int vel=4, cont=0; //Time

		//SDL
	SDL_Event event;
	SDL_Rect background;
	SDL_Rect ball;
	SDL_Rect pickup;
	SDL_Rect snowman;
	SDL_Rect sled;



	SDL_Window *window = SDL_CreateWindow(
		"SnowyDay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 1000, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC); //Important

	SDL_Texture *texture_background = IMG_LoadTexture(renderer, "Backgorund_Skystar_BIG2.png");
	SDL_Texture *texture_ball = IMG_LoadTexture(renderer, "Snowball.png");
	SDL_Texture *texture_pickup = IMG_LoadTexture(renderer, "Snow_Pick_Up.png");
	SDL_Texture *texture_snowman = IMG_LoadTexture(renderer, "Snowman.png");
	SDL_Texture *texture_sled = IMG_LoadTexture(renderer, "Trineo.png");
	
	/*SDL_Surface* surface_background = IMG_Load("Backgorund_Skystar.png");
	SDL_Surface* surface_ball = IMG_Load("Snowball.png");
	SDL_Surface* surface_barrier = IMG_Load("Barrier.png");

	texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);
	texture_ball = SDL_CreateTextureFromSurface(renderer, surface_ball);
	texture_barrier = SDL_CreateTextureFromSurface(renderer, surface_barrier);*/
		//HEIGHT & WIDTH
	background.h = HEIGHT;
	background.w = WEIGHT;
	pickup.h = HEIGHT;
	pickup.w = WEIGHT;
	snowman.h = HEIGHT;
	snowman.w = WEIGHT;
	sled.h = HEIGHT;
	sled.w = WEIGHT;
	ball.h = ball_w;
	ball.w = ball_h;

		//LOOP PRINCIPAL
	while (loop) {

		SDL_RenderClear(renderer);

		ball.x = x_ball;
		ball.y = y_ball;
		background.x = x_background;
		background.y = y_background;
		pickup.x = x_pickup;
		pickup.y = y_pickup;
		snowman.x = x_snowman;
		snowman.y = y_snowman;
		sled.x = x_sled;
		sled.y = y_sled;

		//LOOP K_EVENT

		while (SDL_PollEvent(&event) ){
			

			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				loop = 0;
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					key_left = true;
						break;
				case SDLK_RIGHT:
					key_right = true;
					break;
				default:
					break;
				}
			}
			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					key_left = false;
					break;
				case SDLK_RIGHT:
					key_right = false;
					break;
				default:
					break;
				}
			}
		}
		if (key_left == true) {
			x_ball-= 7;
			if (x_ball <= 0) {
				x_ball += 7;
			}
		}
		if (key_right == true) {
			x_ball+= 7;
			if (x_ball >= 550) {
				x_ball -= 7;
			}
		}
			//CONDITIONS BACKGROUND
		
		if (background.y >= -4015) {
			y_background -= vel;
			y_pickup -= vel;
			y_sled -= vel;
			if (y_background <= -1400) { //Mov sled <--
				x_sled-=7;
				y_sled --;
			}

			if (cont <= 90) { //Mov cops <- ->
				if (cont <= 45) {
					x_pickup -= 1;
				}
				else {
					x_pickup += 1;
				}
				cont++;
			}
			else{ cont = 0; }
		}

		
		
		
		

			//SDL_RENDER

		SDL_RenderCopy(renderer, texture_background, NULL, &background);
		SDL_RenderCopy(renderer, texture_sled, NULL, &sled);
		SDL_RenderCopy(renderer, texture_pickup, NULL, &pickup);
		SDL_RenderCopy(renderer, texture_ball, NULL, &ball);
		SDL_RenderCopy(renderer, texture_snowman, NULL,  &snowman);
		

		

		SDL_RenderPresent(renderer);

	}


	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	return 0;
}