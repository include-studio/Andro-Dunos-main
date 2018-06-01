#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleUI.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	/*shoot particles have name_typeweapon_powerupnumber_distintivenameornumber*/
	// laser particle
	laser_1_1_base.anim.PushBack({ 24,39,11,4 });
	laser_1_1_base.life = 670;
	laser_1_1_base.speed.x = 7;

	laser_1_2_fat.anim.PushBack({ 22,51,15,6 });
	laser_1_2_fat.life = 670;
	laser_1_2_fat.speed.x = 7;

	laser_1_6.anim.PushBack({ 21,6,16,10 });
	laser_1_6.life = 670;
	laser_1_6.speed.x = 7;

	//laser 2_1 particle
	laser_2_1_front.anim.PushBack({ 6,69,10,3 });
	laser_2_1_front.life = 670;
	laser_2_1_front.speed.x = 7;

	//laser 2_2 particle
	laser_2_1_back.anim.PushBack({ 6,84,10,3 });
	laser_2_1_back.life = 670;
	laser_2_1_back.speed.x = -7;
	//laser 2_3 particle
	laser_2_4.anim.PushBack({ 3,23,15,5 });
	laser_2_4.life = 670;
	laser_2_4.speed.x = -7;

	laser_2_7_fat.anim.PushBack({ 3,8,15,5 });
	laser_2_7_fat.life = 670;
	laser_2_7_fat.speed.x = 7;

	laser_2_3_diagonaluthin.anim.PushBack({ 7,88,8,6 });
	laser_2_3_diagonaluthin.life = 670;
	laser_2_3_diagonaluthin.speed.x = -5;
	laser_2_3_diagonaluthin.speed.y = -3;

	laser_2_3_diagonaldthin.anim.PushBack({ 7,96,8,6 });
	laser_2_3_diagonaldthin.life = 670;
	laser_2_3_diagonaldthin.speed.x = -5;
	laser_2_3_diagonaldthin.speed.y = 3;

	laser_2_3_diagonalu.anim.PushBack({ 5,50,11,8 });
	laser_2_3_diagonalu.life = 670;
	laser_2_3_diagonalu.speed.x = -5;
	laser_2_3_diagonalu.speed.y = -3;

	laser_2_3_diagonald.anim.PushBack({ 5,37,11,8 });
	laser_2_3_diagonald.life = 670;
	laser_2_3_diagonald.speed.x = -5;
	laser_2_3_diagonald.speed.y = 3;

	//laser 3 particle
	laser_3_1_0.anim.PushBack({ 16,101,32,3 });
	laser_3_1_0.anim.loop = false;
	laser_3_1_0.life = 670;
	laser_3_1_0.speed.x = 7;
	laser_3_1_0.hp = 10;

	//laser 3_1 particle
	laser_3_2_diagonalupfront.anim.PushBack({ 57,35,16,18 });
	laser_3_2_diagonalupfront.anim.loop = false;
	laser_3_2_diagonalupfront.life = 670;
	laser_3_2_diagonalupfront.speed.x = 7;
	laser_3_2_diagonalupfront.speed.y = -7;

	//laser 3_2 particle
	laser_3_2_diagonaldownfront.anim.PushBack({ 57,60,16,18 });
	laser_3_2_diagonaldownfront.anim.loop = false;
	laser_3_2_diagonaldownfront.life = 670;
	laser_3_2_diagonaldownfront.speed.x = 7;
	laser_3_2_diagonaldownfront.speed.y = 7;

	//laser 3_3 particle
	laser_3_3_diagonalupback.anim.PushBack({ 57,35,16,18 });
	laser_3_3_diagonalupback.anim.loop = false;
	laser_3_3_diagonalupback.life = 670;
	laser_3_3_diagonalupback.speed.x = -7;
	laser_3_3_diagonalupback.speed.y = 7;

	//laser 3_4 particle
	laser_3_3_diagonaldownback.anim.PushBack({ 57,60,16,18 });
	laser_3_3_diagonaldownback.anim.loop = false;
	laser_3_3_diagonaldownback.life = 670;
	laser_3_3_diagonaldownback.speed.x = -7;
	laser_3_3_diagonaldownback.speed.y = -7;

	//laser 3_5 particle
	laser_3_4_diagonalupfront.anim.PushBack({ 81,28,16,22 });
	laser_3_4_diagonalupfront.anim.loop = false;
	laser_3_4_diagonalupfront.life = 670;
	laser_3_4_diagonalupfront.speed.x = 7;
	laser_3_4_diagonalupfront.speed.y = -7;

	//laser 3_6 particle
	laser_3_4_diagonaldownfront.anim.PushBack({ 81,52,16,22 });
	laser_3_4_diagonaldownfront.anim.loop = false;
	laser_3_4_diagonaldownfront.life = 670;
	laser_3_4_diagonaldownfront.speed.x = 7;
	laser_3_4_diagonaldownfront.speed.y = 7;

	//laser 3_7 particle
	laser_3_4_diagonaldownback.anim.PushBack({ 97,14,16,22 });
	laser_3_4_diagonaldownback.anim.loop = false;
	laser_3_4_diagonaldownback.life = 670;
	laser_3_4_diagonaldownback.speed.x = -7;
	laser_3_4_diagonaldownback.speed.y = 7;

	//laser 3_8 particle
	laser_3_4_diagonalupback.anim.PushBack({ 97,66,16,22 });
	laser_3_4_diagonalupback.anim.loop = false;
	laser_3_4_diagonalupback.life = 670;
	laser_3_4_diagonalupback.speed.x = -7;
	laser_3_4_diagonalupback.speed.y = -7;

	//laser 3_5 particle
	laser_3_5_diagonalupfront.anim.PushBack({ 81,14,32,36 });
	laser_3_5_diagonalupfront.anim.loop = false;
	laser_3_5_diagonalupfront.life = 670;
	laser_3_5_diagonalupfront.speed.x = 7;
	laser_3_5_diagonalupfront.speed.y = -7;

	//laser 3_6 particle
	laser_3_5_diagonaldownfront.anim.PushBack({ 81,52,32,36 });
	laser_3_5_diagonaldownfront.anim.loop = false;
	laser_3_5_diagonaldownfront.life = 670;
	laser_3_5_diagonaldownfront.speed.x = 7;
	laser_3_5_diagonaldownfront.speed.y = 7;

	//laser 3_7 particle
	laser_3_5_diagonaldownback.anim.PushBack({ 81,14,32,36 });
	laser_3_5_diagonaldownback.anim.loop = false;
	laser_3_5_diagonaldownback.life = 670;
	laser_3_5_diagonaldownback.speed.x = -7;
	laser_3_5_diagonaldownback.speed.y = 7;

	//laser 3_8 particle
	laser_3_5_diagonalupback.anim.PushBack({ 81,52,32,36 });
	laser_3_5_diagonalupback.anim.loop = false;
	laser_3_5_diagonalupback.life = 670;
	laser_3_5_diagonalupback.speed.x = -7;
	laser_3_5_diagonalupback.speed.y = -7;

	//laser 3_5 particle
	laser_3_6_diagonalupfront.anim.PushBack({ 118,32,32,32 });
	laser_3_6_diagonalupfront.anim.loop = false;
	laser_3_6_diagonalupfront.life = 670;
	laser_3_6_diagonalupfront.speed.x = 7;
	laser_3_6_diagonalupfront.speed.y = -7;

	//laser 3_6 particle
	laser_3_6_diagonaldownfront.anim.PushBack({ 118,66,32,32 });
	laser_3_6_diagonaldownfront.anim.loop = false;
	laser_3_6_diagonaldownfront.life = 670;
	laser_3_6_diagonaldownfront.speed.x = 7;
	laser_3_6_diagonaldownfront.speed.y = 7;

	//laser 3_7 particle
	laser_3_6_diagonaldownback.anim.PushBack({ 118,32,32,32 });
	laser_3_6_diagonaldownback.anim.loop = false;
	laser_3_6_diagonaldownback.life = 670;
	laser_3_6_diagonaldownback.speed.x = -7;
	laser_3_6_diagonaldownback.speed.y = 7;

	//laser 3_8 particle
	laser_3_6_diagonalupback.anim.PushBack({ 118,66,32,32 });
	laser_3_6_diagonalupback.anim.loop = false;
	laser_3_6_diagonalupback.life = 670;
	laser_3_6_diagonalupback.speed.x = -7;
	laser_3_6_diagonalupback.speed.y = -7;

	//laser 3_5 particle
	laser_3_7_diagonalupfront.anim.PushBack({ 118,2,55,62 });
	laser_3_7_diagonalupfront.anim.loop = false;
	laser_3_7_diagonalupfront.life = 670;
	laser_3_7_diagonalupfront.speed.x = 7;
	laser_3_7_diagonalupfront.speed.y = -7;

	//laser 3_6 particle
	laser_3_7_diagonaldownfront.anim.PushBack({ 118,65,55,62 });
	laser_3_7_diagonaldownfront.anim.loop = false;
	laser_3_7_diagonaldownfront.life = 670;
	laser_3_7_diagonaldownfront.speed.x = 7;
	laser_3_7_diagonaldownfront.speed.y = 7;

	//laser 3_7 particle
	laser_3_7_diagonaldownback.anim.PushBack({ 118,2,55,62 });
	laser_3_7_diagonaldownback.anim.loop = false;
	laser_3_7_diagonaldownback.life = 670;
	laser_3_7_diagonaldownback.speed.x = -7;
	laser_3_7_diagonaldownback.speed.y = 7;

	//laser 3_8 particle
	laser_3_7_diagonalupback.anim.PushBack({ 118,65,55,62 });
	laser_3_7_diagonalupback.anim.loop = false;
	laser_3_7_diagonalupback.life = 670;
	laser_3_7_diagonalupback.speed.x = -7;
	laser_3_7_diagonalupback.speed.y = -7;

	//laser 4_1 particle
	laser_4_1_1.anim.PushBack({ 41,11,13,2 });
	laser_4_1_1.anim.PushBack({ 41,23,13,6 });
	laser_4_1_1.anim.loop = false;
	laser_4_1_1.anim.speed = 0.8f;
	laser_4_1_1.life = 670;
	laser_4_1_1.speed.x = 7;
	laser_4_1_1.speed.y = 1;

	//laser 4_2 particle
	laser_4_1_2.anim.PushBack({ 41,11,13,2 });
	laser_4_1_2.anim.PushBack({ 41,23,13,6 });
	laser_4_1_2.anim.PushBack({ 41,38,13,8 });
	laser_4_1_2.anim.loop = false;
	laser_4_1_2.anim.speed = 0.8f;
	laser_4_1_2.life = 670;
	laser_4_1_2.speed.x = 7;
	laser_4_1_2.speed.y = -1;

	//laser 4_3 upgrade 1 of laser 4
	laser_4_2_0.anim.PushBack({ 41,11,13,2 });
	laser_4_2_0.anim.PushBack({ 41,23,13,6 });
	laser_4_2_0.anim.loop = false;
	laser_4_2_0.anim.speed = 0.8f;
	laser_4_2_0.life = 670;
	laser_4_2_0.speed.x = 7;

	//laser 4_1 particle
	laser_4_4_1.anim.PushBack({ 41,11,13,2 });
	laser_4_4_1.anim.PushBack({ 41,23,13,6 });
	laser_4_4_1.anim.PushBack({ 41,38,13,8 });
	laser_4_4_1.anim.loop = false;
	laser_4_4_1.anim.speed = 0.8f;
	laser_4_4_1.life = 670;
	laser_4_4_1.speed.x = 7;
	laser_4_4_1.speed.y = 2;

	//laser 4_2 particle
	laser_4_4_2.anim.PushBack({ 41,11,13,2 });
	laser_4_4_2.anim.PushBack({ 41,23,13,6 });
	laser_4_4_2.anim.PushBack({ 41,38,13,8 });
	laser_4_4_2.anim.loop = false;
	laser_4_4_2.anim.speed = 0.8f;
	laser_4_4_2.life = 670;
	laser_4_4_2.speed.x = 7;
	laser_4_4_2.speed.y = -2;

	//laser 4_1 particle
	laser_4_5_1.anim.PushBack({ 41,11,13,2 });
	laser_4_5_1.anim.PushBack({ 41,23,13,6 });
	laser_4_5_1.anim.PushBack({ 41,38,13,8 });
	laser_4_5_1.anim.PushBack({ 41,49,13,12 });
	laser_4_5_1.anim.PushBack({ 41,64,13,14 });
	laser_4_5_1.anim.loop = false;
	laser_4_5_1.anim.speed = 0.8f;
	laser_4_5_1.life = 670;
	laser_4_5_1.speed.x = 7;
	laser_4_5_1.speed.y = 1;

	//laser 4_2 particle
	laser_4_5_2.anim.PushBack({ 41,11,13,2 });
	laser_4_5_2.anim.PushBack({ 41,23,13,6 });
	laser_4_5_2.anim.PushBack({ 41,38,13,8 });
	laser_4_5_2.anim.PushBack({ 41,49,13,12 });
	laser_4_5_2.anim.PushBack({ 41,64,13,14 });
	laser_4_5_2.anim.loop = false;
	laser_4_5_2.anim.speed = 0.8f;
	laser_4_5_2.life = 670;
	laser_4_5_2.speed.x = 7;
	laser_4_5_2.speed.y = -1;

	//laser 4_3 upgrade 1 of laser 4
	laser_4_3_1.anim.PushBack({ 41,11,13,2 });
	laser_4_3_1.anim.PushBack({ 41,23,13,6 });
	laser_4_3_1.anim.PushBack({ 41,38,13,8 });
	laser_4_3_1.anim.loop = false;
	laser_4_3_1.anim.speed = 0.8f;
	laser_4_3_1.life = 670;
	laser_4_3_1.speed.x = 7;

	laser_4_6.anim.PushBack({ 41,11,13,2 });
	laser_4_6.anim.PushBack({ 41,23,13,6 });
	laser_4_6.anim.PushBack({ 41,38,13,8 });
	laser_4_6.anim.PushBack({ 41,49,13,12 });
	laser_4_6.anim.PushBack({ 41,64,13,14 });
	laser_4_6.anim.loop = false;
	laser_4_6.anim.speed = 0.8f;
	laser_4_6.life = 670;
	laser_4_6.speed.x = 7;

	laser_4_7_1.anim.PushBack({ 41,11,13,2 });
	laser_4_7_1.anim.PushBack({ 41,23,13,6 });
	laser_4_7_1.anim.PushBack({ 41,38,13,8 });
	laser_4_7_1.anim.PushBack({ 41,49,13,12 });
	laser_4_7_1.anim.PushBack({ 41,64,13,14 });
	laser_4_7_1.anim.loop = false;
	laser_4_7_1.anim.speed = 0.8f;
	laser_4_7_1.life = 670;
	laser_4_7_1.speed.x = 7;
	laser_4_7_1.speed.y = 2;

	//laser 4_2 particle
	laser_4_7_2.anim.PushBack({ 41,11,13,2 });
	laser_4_7_2.anim.PushBack({ 41,23,13,6 });
	laser_4_7_2.anim.PushBack({ 41,38,13,8 });
	laser_4_7_2.anim.PushBack({ 41,49,13,12 });
	laser_4_7_2.anim.PushBack({ 41,64,13,14 });
	laser_4_7_2.anim.loop = false;
	laser_4_7_2.anim.speed = 0.8f;
	laser_4_7_2.life = 670;
	laser_4_7_2.speed.x = 7;
	laser_4_7_2.speed.y = -2;



	//bomb
	//1_1
	bomb_1_1.anim.PushBack({ 302,187,13,12 });
	bomb_1_1.anim.PushBack({ 302,171,13,12 });
	bomb_1_1.anim.PushBack({ 302,159,13,12 });
	bomb_1_1.anim.loop = false;
	bomb_1_1.speed.x = 4;
	bomb_1_1.speed.y = 3;
	bomb_1_1.anim.speed = 0.1f;
	bomb_1_1.life = 1000;


	//1_2
	bomb_1_2.anim.PushBack({ 302,187,13,12 });
	bomb_1_2.anim.PushBack({ 302,202,13,12 });
	bomb_1_2.anim.PushBack({ 302,214,13,12 });
	bomb_1_2.anim.loop = false;
	bomb_1_2.speed.x = 4;
	bomb_1_2.speed.y = -3;
	bomb_1_2.anim.speed = 0.1f;
	bomb_1_2.life = 1000;

	//2_1
	for (int i = 0; i < 8; i++)
		bomb_2_1.anim.PushBack({ 273,157 + i * 9,16,9 });
	bomb_2_1.anim.loop = false;
	bomb_2_1.speed.x = 1;
	bomb_2_1.speed.y = 5;
	bomb_2_1.anim.speed = 0.8f;
	bomb_2_1.life = 1000;

	//2_2
	for (int i = 0; i < 8; i++)
		bomb_2_2.anim.PushBack({ 273,157 + i * 9,16,9 });
	bomb_2_2.anim.loop = false;
	bomb_2_2.speed.x = 1;
	bomb_2_2.speed.y = -5;
	bomb_2_2.anim.speed = 0.8f;
	bomb_2_2.life = 1000;
	
	//2_3
	for (int i = 0; i < 8; i++)
		bomb_2_3.anim.PushBack({ 273,157 + i * 9,16,9 });
	bomb_2_3.anim.loop = false;
	bomb_2_3.speed.x = 3;
	bomb_2_3.speed.y = -5;
	bomb_2_3.anim.speed = 0.8f;
	bomb_2_3.life = 1000;

	//2_4
	for (int i = 0; i < 8; i++)
		bomb_2_4.anim.PushBack({ 273,157 + i * 9,16,9 });
	bomb_2_4.anim.loop = false;
	bomb_2_4.speed.x = 3;
	bomb_2_4.speed.y = 5;
	bomb_2_4.anim.speed = 0.8f;
	bomb_2_4.life = 1000;

	//3_1
	bomb_3_1.anim.PushBack({ 393,174,6,7});
	bomb_3_1.speed.x = 3;
	bomb_3_1.speed.y = 4;
	bomb_3_1.life = 1000;

	//3_2
	bomb_3_2.anim.PushBack({ 393,161,6,7 });
	bomb_3_2.speed.x = 3;
	bomb_3_2.speed.y = -4;
	bomb_3_2.life = 1000;

	//3_3
	bomb_3_3.anim.PushBack({ 393,174,6,7 });
	bomb_3_3.speed.x = -2;
	bomb_3_3.speed.y = 4;
	bomb_3_3.life = 1000;

	//3_4
	bomb_3_4.anim.PushBack({ 393,161,6,7 });
	bomb_3_4.speed.x = -2;
	bomb_3_4.speed.y = -4;
	bomb_3_4.life = 1000;

	//4_1
	bomb_4_1.anim.PushBack({ 63,11,3,16 });
	bomb_4_1.speed.x = 1;
	bomb_4_1.speed.y = 5;
	bomb_4_1.life = 1000;

	//4_2
	bomb_4_2.anim.PushBack({ 63,11,3,16 });
	bomb_4_2.speed.x = 1;
	bomb_4_2.speed.y = -5;
	bomb_4_2.life = 1000;

	//4_3
	bomb_4_3.anim.PushBack({ 57,35,16,18 });
	bomb_4_3.speed.x = -5;
	bomb_4_3.speed.y = 5;
	bomb_4_3.life = 1000;

	//4_4
	bomb_4_4.anim.PushBack({ 57,60,16,18 });
	bomb_4_4.speed.x = -5;
	bomb_4_4.speed.y = -5;
	bomb_4_4.life = 1000;

	//mini explosion particle
	mini_explosion.anim.PushBack({ 160,133,32,32 });
	mini_explosion.anim.PushBack({ 160,165,32,32 });
	mini_explosion.anim.PushBack({ 160,197,32,32 });
	mini_explosion.anim.PushBack({ 160,229,32,32 });
	mini_explosion.anim.loop = false;
	mini_explosion.anim.speed = 0.8f;

	//big explosion particle
	big_explosion.anim.PushBack({ 65,133,32,32 });
	big_explosion.anim.PushBack({ 65,165,32,32 });
	big_explosion.anim.PushBack({ 65,197,32,32 });
	big_explosion.anim.PushBack({ 65,229,32,32 });
	big_explosion.anim.PushBack({ 65,261,32,32 });
	big_explosion.anim.PushBack({ 97,133,32,32 });
	big_explosion.anim.PushBack({ 97,165,32,32 });
	big_explosion.anim.PushBack({ 97,197,32,32 });
	big_explosion.anim.PushBack({ 96,229,32,32 });
	big_explosion.anim.PushBack({ 96,261,32,32 });
	big_explosion.anim.PushBack({ 128,133,32,32 });
	big_explosion.anim.PushBack({ 128,164,32,32 });
	big_explosion.anim.PushBack({ 128,197,32,32 });
	big_explosion.anim.PushBack({ 128,228,32,32 });
	big_explosion.anim.PushBack({ 128,260,32,32 });
	big_explosion.anim.loop = false;
	big_explosion.anim.speed = 0.8f;

	//ring explosion
	ring_explosion.anim.PushBack({ 0,133,32,32 });
	ring_explosion.anim.PushBack({ 0,165,32,32 });
	ring_explosion.anim.PushBack({ 0,197,32,32 });
	ring_explosion.anim.PushBack({ 0,229,32,32 });
	ring_explosion.anim.PushBack({ 0,261,32,32 });
	ring_explosion.anim.PushBack({ 32,133,32,32 });
	ring_explosion.anim.PushBack({ 32,165,32,32 });
	ring_explosion.anim.PushBack({ 32,197,32,32 });
	ring_explosion.anim.PushBack({ 32,229,32,32 });
	ring_explosion.anim.PushBack({ 32,261,32,32 });


	explosion_player1.anim.PushBack({ 189,0,32,32 });
	explosion_player1.anim.PushBack({ 229,0,32,32 });
	explosion_player1.anim.PushBack({ 270,0,32,32 });
	explosion_player1.anim.PushBack({ 308,0,32,32 });
	explosion_player1.anim.PushBack({ 351,0,32,32 });
	explosion_player1.anim.PushBack({ 398,0,32,32 });
	explosion_player1.anim.PushBack({ 192,32,32,32 });
	explosion_player1.anim.PushBack({ 232,32,32,32 });
	explosion_player1.anim.PushBack({ 269,32,32,32 });
	explosion_player1.anim.PushBack({ 309,32,32,32 });
	explosion_player1.anim.PushBack({ 351,32,32,32 });
	explosion_player1.anim.PushBack({ 398,32,32,32 });
	explosion_player1.anim.PushBack({ 191,79,32,32 });
	explosion_player1.anim.PushBack({ 231,79,32,32 });
	explosion_player1.anim.PushBack({ 266,79,32,32 });
	explosion_player1.anim.PushBack({ 307,79,32,32 });
	explosion_player1.anim.loop = false;
	explosion_player1.anim.speed = 0.5f;

	explosion_player2.anim.PushBack({ 189,117,32,32 });
	explosion_player2.anim.PushBack({ 229,117,32,32 });
	explosion_player2.anim.PushBack({ 270,117,32,32 });
	explosion_player2.anim.PushBack({ 308,117,32,32 });
	explosion_player2.anim.PushBack({ 351,117,32,32 });
	explosion_player2.anim.PushBack({ 398,117,32,32 });
	explosion_player2.anim.PushBack({ 192,154,32,32 });
	explosion_player2.anim.PushBack({ 232,32,32,32 });
	explosion_player2.anim.PushBack({ 269,32,32,32 });
	explosion_player2.anim.PushBack({ 309,32,32,32 });
	explosion_player2.anim.PushBack({ 351,32,32,32 });
	explosion_player2.anim.PushBack({ 398,32,32,32 });
	explosion_player2.anim.PushBack({ 191,79,32,32 });
	explosion_player2.anim.PushBack({ 231,79,32,32 });
	explosion_player2.anim.PushBack({ 266,79,32,32 });
	explosion_player2.anim.PushBack({ 307,79,32,32 });
	explosion_player2.anim.loop = false;
	explosion_player2.anim.speed = 0.5f;

	//enemy blue shot
	enemy_blue.anim.PushBack({ 243,148,8,8 });
	enemy_blue.anim.PushBack({ 243,156,8,8 });
	enemy_blue.anim.PushBack({ 243,165,8,8 });
	enemy_blue.anim.PushBack({ 250,148,8,8 });
	enemy_blue.anim.speed = 0.2f;
	enemy_blue.life = 1500;
	enemy_blue.speed.x = -2;

	//enemy blue diagonal UP shot
	enemy_blue_up.anim.PushBack({ 243,148,8,8 });
	enemy_blue_up.anim.PushBack({ 243,156,8,8 });
	enemy_blue_up.anim.PushBack({ 243,165,8,8 });
	enemy_blue_up.anim.PushBack({ 250,148,8,8 });
	enemy_blue_up.anim.speed = 0.2f;
	enemy_blue_up.life = 1500;
	enemy_blue_up.speed.x = -2;
	enemy_blue_up.speed.y--;

	//enemy blue diagonal DOWN shot
	enemy_blue_down.anim.PushBack({ 243,148,8,8 });
	enemy_blue_down.anim.PushBack({ 243,156,8,8 });
	enemy_blue_down.anim.PushBack({ 243,165,8,8 });
	enemy_blue_down.anim.PushBack({ 250,148,8,8 });
	enemy_blue_down.anim.speed = 0.2f;
	enemy_blue_down.life = 1500;
	enemy_blue_down.speed.x = -2;
	enemy_blue_down.speed.y++;

	//enemy yellow laser shoot
	enemy_yellow_laser.anim.PushBack({ 208 + 32*0,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*1,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*2,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*3,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*4,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*5,275,32,13 });
	enemy_yellow_laser.anim.PushBack({ 208 + 32*6,275,32,13 });
	
	enemy_yellow_laser.anim.speed = 0.2f;
	enemy_yellow_laser.life = 1500;
	enemy_yellow_laser.speed.x = -2;
	enemy_yellow_laser.anim.loop = false;
	
	//enemy_blue_laser shoot

	enemy_blue_laser.anim.PushBack({ 276,296,32,4 });
	

	enemy_blue_laser.anim.speed = 0.2f;
	enemy_blue_laser.life = 1500;
	enemy_blue_laser.speed.x = -2;
	enemy_blue_laser.anim.loop = false;

	
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/Sprites/laser_types.png");
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if(p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}


void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, OWNER owner, ID id)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->owner_type = owner;
			p->id = id;

			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c2->type == COLLIDER_ENEMY) {
				if (active[i]->owner_type == OWNER_PLAYER1) {
					App->ui->score1 += 100;
					LOG("COLLISION PARTICLE PLAYER1");
				}
				if (active[i]->owner_type == OWNER_PLAYER2) {
					App->ui->score2 += 200;
					LOG("COLLISION PARTICLE PLAYER2");
				}
			}
			active[i]->hp-=1;
			//if (active[i]->hp <= 0) {
				delete active[i];
				active[i] = nullptr;
				break;
			//}
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life), id(p.id)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	if (id == BOMB_DELAY)
		LOG("HEY ESTOY EN: (%i,%i)", position.x, position.y);
	if (id == BOMB)
		LOG("PUES YO EN: (%i,%i)", position.x, position.y);

	


	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	/*if (App->player1->position.y > position.y && blue_followUp == false)
	{
		position.y += 1;
		blue_followUp = true;
	}

	if (App->player1->position.y < position.y && blue_followDown == false)
	{
		position.y -= 1;
		blue_followDown = true;
	}

	if (blue_followUp == true) position.y += 1;
	if (blue_followDown == true ) position.y -= 1;*/
		

	

	return ret;
}