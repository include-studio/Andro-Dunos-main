#include "SDL/include/SDL.h"
#include "SDL/include/SDL_image.h"
#include "SDL/include/SDL_mixer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL/libx86/SDL2_image.lib")
#pragma comment(lib, "SDL/libx86/SDL2_mixer.lib")

#define HEIGHT 1520
#define WEIGHT 600
#define NSHOT 100
#define NFLAKE 500

//ARRAY SHOT
void shotInit(SDL_Rect a[]) {
	for (int i = 0; i < NSHOT; i++) {
		a[i].h = 26;
		a[i].w = 14;
		a[i].x = 0 - a[0].w;
		a[i].y = 0 - a[0].h;
	}
}
void snowflakeInit(SDL_Rect a[]) {
	for (int i = 0; i < NFLAKE; i++) {
		a[i].h = 73;
		a[i].w = 64;
		a[i].x = 300;
		a[i].y = 1001;
	}
}
int main(int argc, char* argv[]) {
	srand(time(NULL));
	//INICIALIZAR
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	//AUDIO
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;
	Mix_Music *bgm = Mix_LoadMUS("bgm.wav"); //bgm longer than 10 sec
	Mix_Music *bgm_Wind = Mix_LoadMUS("bgm_Wind.wav");
	Mix_Chunk *death = Mix_LoadWAV("death.wav");//sound effect 
	Mix_Chunk *fire_ball = Mix_LoadWAV("fire_ball.wav");
	Mix_Chunk *snow = Mix_LoadWAV("snow.wav");
	Mix_Chunk *mario_cry = Mix_LoadWAV("mario_cry.wav");

	//LOCAL VAR
	int x_ball = 275, y_ball = 0, x_background = 0, y_background = 0, x_pickup = 0, y_pickup = 0, x_sled = 255, y_sled = 0; //Position
	int cont_shot = 0, life = 3, contflake = 0, contN = 0, cont_cry = 0;
	int ball_h = 50, ball_w = 50, cont_background = 0; //Part of h&w
	bool loop = true, key_left = false, key_right = false, key_a = false, key_d = false, mov_e = true, shoot = false, gameover = false; //Part of Loop
	float vel = 0.5, cont = 0; //Time

							   //SDL
	SDL_Event event;
	SDL_Rect background;
	SDL_Rect ball;
	SDL_Rect pickup;
	SDL_Rect snowman;
	SDL_Rect sled;
	SDL_Rect enemy;
	SDL_Rect shot[NSHOT];
	SDL_Rect heart;
	SDL_Rect snowflake[NFLAKE];
	SDL_Rect snowsprite;


	SDL_Window *window = SDL_CreateWindow(
		"SnowyDay", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 1000, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Important

	SDL_Texture *texture_background = IMG_LoadTexture(renderer, "Backgorund_Skystar_BIG2.png");
	SDL_Texture *texture_ball = IMG_LoadTexture(renderer, "Snowball.png");
	SDL_Texture *texture_pickup = IMG_LoadTexture(renderer, "Snow_Pick_Up.png");
	SDL_Texture *texture_snowman = IMG_LoadTexture(renderer, "Snowman.png");
	SDL_Texture *texture_sled = IMG_LoadTexture(renderer, "Trineo.png");
	SDL_Texture *mario_tx = IMG_LoadTexture(renderer, "mario.png");
	SDL_Texture *shot_tx = IMG_LoadTexture(renderer, "fireshot.png");
	SDL_Texture *heart_tx = IMG_LoadTexture(renderer, "heart.png");
	SDL_Texture *snowflake_tx = IMG_LoadTexture(renderer, "snowflake.png");


	//HEIGHT & WIDTH
	background.h = HEIGHT;
	background.w = WEIGHT;
	pickup.h = HEIGHT;
	pickup.w = WEIGHT;
	snowman.h = HEIGHT;
	snowman.w = WEIGHT;
	sled.h = HEIGHT;
	sled.w = WEIGHT;
	ball.h = ball_h + 50;
	ball.w = ball_w + 50;
	enemy.h = 170;
	enemy.w = 150;
	enemy.x = 60;
	enemy.y = 980 - enemy.h - 50;
	shotInit(shot);
	snowman.x = 0;
	snowman.y = 525;
	sled.x = x_sled;
	sled.y = y_sled;
	heart.x = 15;
	heart.y = 950;
	heart.w = 11 * 5;
	heart.h = 9 * 5;
	snowflakeInit(snowflake);
	snowsprite.x = 0;
	snowsprite.y = 0;
	snowsprite.w = 64;
	snowsprite.h = 73;


	if (loop == true) {
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(bgm, 0);
		}

		else if (Mix_PausedMusic()) {
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}

	//LOOP PRINCIPAL
	while (loop) {

		if (cont_cry == 0) {
			Mix_PlayChannel(-1, mario_cry, 0);
			cont_cry++;
		}

		SDL_RenderClear(renderer);
		/*if (!gameover) {*/
		ball.x = x_ball;
		ball.y = y_ball;
		background.x = x_background;
		background.y = y_background;
		pickup.x = x_pickup;
		pickup.y = y_pickup;
		sled.x = x_sled;
		sled.y = y_sled;

		//LOOP K_EVENT

		while (SDL_PollEvent(&event)) {


			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				loop = 0;
			}


			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
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
			x_ball -= 7;
			if (x_ball <= 0) {
				x_ball += 7;
			}
		}
		if (key_right == true) {
			x_ball += 7;
			if (x_ball >= 550) {
				x_ball -= 7;
			}
		}




		Mix_PlayChannel(-1, fire_ball, 0);

		//Mix_PlayChannel(-1, mario_cry, 0);
		shot[cont_shot].x = enemy.x;
		shot[cont_shot].y = enemy.y;
		cont_shot++;
		if (cont_shot == NSHOT)
			cont_shot = 0;




		//snowflakes
		//for (int i = 0; i < contflake; i++) {
		if (contN % 50 == 0 || contN == 0) {
			snowflake[contflake].x = rand() % 600;
			snowflake[contflake].y = 990;
			contflake++;
		}
		//}
		for (int i = 0; i < contflake; i++) {
			snowflake[i].y -= 10;
			snowflake[i].x++;
		}

		if (contflake == NFLAKE)
			contflake = 0;
		contN++;
		//mov mario
		if (enemy.x >= WEIGHT - enemy.w)
			mov_e = false;
		if (enemy.x == 0)
			mov_e = true;
		if (mov_e)
			enemy.x += 5;
		if (!mov_e)
			enemy.x -= 5;

		//shot
		for (int i = 0; i <= cont_shot; i++) {
			int down;
			shot[i].y -= 15;
			shot[i].y += 8;

			//Hard_shot m0th3rFuk3Rs
			if (shot[i].x >= 600) {
				down = 0;
			}
			if (down == 1) {
				shot[i].x += 8;
			}
			if (shot[i].x <= 0) {
				down = 1;
			}
			if (down == 0) {
				shot[i].x -= 8;
			}
		}

		//CONDITIONS BACKGROUND

		if (background.y >= -4015) {

			if (ball.h >= 115) {
				y_background -= vel * 2;
				y_pickup -= vel * 2;
				y_sled -= vel * 2;
			}
			if (ball.h >= 130) {
				y_background -= vel * 3;
				y_pickup -= vel * 3;
				y_sled -= vel * 3;
			}
			else {
				y_background -= vel;
				y_pickup -= vel;
				y_sled -= vel;
			}



			//Animations
			if (background.y <= -1050) {
				x_sled -= vel;
			}
		}
		//collision
		for (int i = 0; i < cont_shot; i++) {
			if (SDL_HasIntersection(&shot[i], &ball) == SDL_TRUE) {
				Mix_PlayChannel(-1, death, 0);//Mix_PlayChannel(Channel, track, loop_times)
				ball.h -= 20;
				ball.w -= 20;
				i = cont_shot;
				shotInit(shot);
				life--;
			}
		}
		for (int i = 0; i < contflake; i++) {
			if (SDL_HasIntersection(&snowflake[i], &ball) == SDL_TRUE) {
				ball.h += 5;
				ball.w += 5;
				snowflake[i].x = 0 - snowflake->w;
				snowflake[i].y = 0 - snowflake->h;
			}
		}
		//SDL_RENDER
		SDL_RenderCopy(renderer, texture_background, NULL, &background);
		//SDL_RenderCopy(renderer, texture_pickup, NULL, &pickup);
		switch (life) {
		case 3:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 2:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x += 60;
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 1:
			SDL_RenderCopy(renderer, heart_tx, NULL, &heart);
			heart.x = 15;
			break;
		case 0://Game over - bgm_Wind Audio
			gameover = true;
			break;
		}
		for (int i = 0; i < contflake; i++) {
			SDL_RenderCopy(renderer, snowflake_tx, &snowsprite, &snowflake[i]);
		}
		snowsprite.x += snowsprite.w;
		if (snowsprite.x = snowsprite.w * 4)
			snowsprite.x = 0;
		SDL_RenderCopy(renderer, texture_sled, NULL, &sled);
		SDL_RenderCopy(renderer, texture_ball, NULL, &ball);
		SDL_RenderCopy(renderer, mario_tx, NULL, &enemy);
		for (int i = 0; i < cont_shot; i++) {
			SDL_RenderCopy(renderer, shot_tx, NULL, &shot[i]);
		}
		SDL_RenderCopy(renderer, texture_snowman, NULL, &snowman);


		SDL_RenderPresent(renderer);

		if (gameover == true) {

			if (background.y <= 10000) {
				y_background -= vel * 10;
			}


		}
		else {

			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				loop = 0;
			}

		}
	}
	Mix_FreeMusic(bgm);
	Mix_FreeMusic(bgm_Wind);
	Mix_FreeChunk(death);
	Mix_FreeChunk(fire_ball);
	Mix_FreeChunk(snow);
	Mix_FreeChunk(mario_cry);



	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_CloseAudio();
	return 0;
}