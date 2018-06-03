#include "Globals.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleStage4.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStageClear.h"
#include "ModuleAudio.h"
#include "ModuleGameOver.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePowerUp.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"


ModuleStage4::ModuleStage4() {
	//background
	back.x = 0;
	back.y = 0;
	back.w = 1024;
	back.h = 323;

	//ground
	ground[0].x = 0;
	ground[0].y = 0;
	ground[0].w = 2048;
	ground[0].h = 319;

	ground[1].x = 0;
	ground[1].y = 319;
	ground[1].w = 673;
	ground[1].h = 319;

	ground[2].x = 0;
	ground[2].y = 672;
	ground[2].w = 2048;
	ground[2].h = 285;

	ground[3].x = 0;
	ground[3].y = 1090;
	ground[3].w = 1113;
	ground[3].h = 324;

	//water
	water.PushBack({ 1235,978,304,21 });
	water.PushBack({ 1235,1017,304,21 });
	water.PushBack({ 1235,1056,304,21 });
	water.PushBack({ 1235,1095,304,21 });
	water.PushBack({ 1235,1136,304,21 });
	water.loop = true;
	water.speed = 0.08f;

	//light
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 3; i++)
			backlight.PushBack({ 0,i * 292,1024,324 });
		for (int i = 2; i >= 0; i--)
			backlight.PushBack({ 0,i * 292,1024,324 });
	}
	backlight.speed = 0.1f;

	//ground column
	groundColumn.x = 1568;
	groundColumn.y = 979;
	groundColumn.w = 368;
	groundColumn.h = 198;

}

ModuleStage4::~ModuleStage4(){}

bool ModuleStage4::Start() {

	
	bool ret = true;
	//Timer
	time_preAnim = init_time = SDL_GetTicks(); 
	time_backAnim = time_music = 0;
	//load textures
	back_tx = App->textures->Load("assets/Sprites/background4.png");
	backlight_tx = App->textures->Load("assets/Sprites/background4anim.png");
	ground_tx = App->textures->Load("assets/Sprites/ground4.png");

	//colliders
	App->collision->AddCollider({ 1000,215,125,100 }, COLLIDER_WALL4); //x y w h
	App->collision->AddCollider({ 1240,215,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1365,200,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1490,175,175,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1665,190,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1745,200,175,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 1920,185,135,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2055,170,64,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2119,155,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2184,140,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2249,125,95,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2344,145,110,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2454,125,160,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2614,110,225,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2839,80,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2919,45,45,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2964,85,255,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3219,122,127,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3346,142,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3411,157,15,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3426,188,33,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3459,203,15,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3474,233,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3554,263,30,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3584,288,30,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3614,308,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 3704,323,1530,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5234,313,275,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5509,288,25,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5534,268,50,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 5584,328,225,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6065,328,508,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6573,308,130,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6703,298,20,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6723,278,20,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6743,285,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6833,265,125,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 6958,250,62,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7020,280,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7100,310,80,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7180,290,90,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7270,270,100,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7370,205,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7435,160,285,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7720,200,210,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7930,235,500,100 }, COLLIDER_WALL4);


	App->collision->AddCollider({ 1645,-40,545,50 }, COLLIDER_WALL4); //Up
	App->collision->AddCollider({ 2190,-60,65,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2255,-110,295,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2550,-90,195,50 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 2745,-130,100,50 }, COLLIDER_WALL4);

	App->collision->AddCollider({ 5585,90,50,50 }, COLLIDER_WALL4); //Up 2
	App->collision->AddCollider({ 5635,80,160,100 }, COLLIDER_WALL4);  
	App->collision->AddCollider({ 5795,95,210,50 }, COLLIDER_WALL4);

	App->collision->AddCollider({ 7070,90,20,50 }, COLLIDER_WALL4); //Up3
	App->collision->AddCollider({ 7090,80,222,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7312,20,35,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7347,-40,65,100 }, COLLIDER_WALL4);
	App->collision->AddCollider({ 7412,-65,145,100 }, COLLIDER_WALL4);


	//Enemies
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 405, 30);  //MINIGREEN
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 425, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 445, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 465, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 485, 30);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 405, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 425, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 445, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 465, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 485, 197);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 555, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 575, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 595, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 625, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN1, 645, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 555, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 575, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 595, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 625, 197);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN2, 645, 197);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 700, 90); //POWERUP

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 950, 50); //WAVING SHIP
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 963, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 976, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 989, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 1050, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 1063, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 1076, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP, 1089, 110);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 1190, 110); //POWER UP 2

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 1220, 50); //TINY RED SHIP
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 1260, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 1300, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP, 1340, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 1370, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 1410, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 1450, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 1490, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 1500, 50); //WAVING SHIP WEIRD
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 1540, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 1580, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 1620, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 1660, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::VENDING, 1550, 138, true); //VENDING

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1563, 170);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1562, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1561, 230);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1560, 260);

	App->enemies->AddEnemy(ENEMY_TYPES::VENDING, 1675, 158, true);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1688, 190);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1687, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1686, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIGREEN3, 1685, 280);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 1990, 70); //1st Miniminiboss
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 2030, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 2070, 70);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2220, 40); //HORITZONTAL ROCKET ZIG ZAG
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2235, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2250, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 2290, 80); 
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 2305, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 2320, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2360, 25);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2375, 25);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 2390, 25);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 2550, 10); //POWER UP 3

	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2700, 20); //LONGSHIP
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2720, 40); 
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2740, 30); 
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2750, 25);
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2760, 45);
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2770, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2780, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2790, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::LONG, 2800, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 2880, -40); //2nd Miniminiboss
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 2840, -40);
	App->enemies->AddEnemy(ENEMY_TYPES::MINIMINIBOSS, 2800, -40);

	App->enemies->AddEnemy(ENEMY_TYPES::COLUMN, 2902, -66); //COLUMN

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3100, 0); //WAVING SHIP WEIRD
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3140, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3180, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3220, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3260, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3300, 0); //WAVING SHIP WEIRD
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3340, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3380, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3420, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 3460, 0);

	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 3750, 130); //TRIPLECANON
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 3725, 100);

	//Test
	//App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP, 500, 30); //Big ship WATER
	//App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP2, 500, 30); //Big ship WATER Wing1
	//App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP3, 500, 30); //Big ship WATER Wing2
	//---------------------------------------------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP, 3950, 165, true); //Big ship WATER
	App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP2, 3950, 165); //Big ship WATER Wing1
	App->enemies->AddEnemy(ENEMY_TYPES::BIGSHIP3, 3950, 165); //Big ship WATER Wing2

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4150, 340); //FISH TIMEEEE
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4150, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4150, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4050, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4050, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4050, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4075, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4075, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4075, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4250, 340);
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4250, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4250, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4325, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4325, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4325, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4475, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4475, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4475, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4675, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4675, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4675, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4705, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4705, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4705, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4735, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4735, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4735, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4805, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4805, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4805, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4825, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4825, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4825, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4900, 340);
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4900, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4900, 287); 

	
	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 4945, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 4945, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 4945, 287); 

	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 5045, 340);
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 5045, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 5045, 287);
	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 5105, 340); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER, 5105, 287); 
	App->enemies->AddEnemy(ENEMY_TYPES::WATER2, 5105, 287); 
	
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 5350, 210); //TRIPLECANON
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 5325, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 5450, 210);
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 5425, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 5480, 210); //POWER UP 4

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5640, 230); //HORITZONATAL ROCKET
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5655, 230);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5670, 230);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5700, 270);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5715, 270);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 5730, 270);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 6070, 210); //POWER UP 5

	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 6250, 210); //TRIPLECANON
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 6225, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON, 6350, 210);
	App->enemies->AddEnemy(ENEMY_TYPES::TRIPLECANON2, 6325, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6490, 160); //HORITZONTAL ROCKET
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6505, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6520, 160);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 6550, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 6565, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET3, 6580, 220);

	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6610, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6625, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::HORIZONTALROCKET2, 6640, 160);

	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6760, 200); //COOL SHIP
	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6780, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6800, 200);

	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6840, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6860, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::COOL, 6880, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7000, 180); //WAVING SHIP WEIRD
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7040, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7080, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7120, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7160, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7220, 250); //TINY RED SHIP need ground move
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7260, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7300, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7340, 250);

	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7380, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7420, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7460, 250);
	App->enemies->AddEnemy(ENEMY_TYPES::TINYREDSHIP2, 7500, 250);


	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7500, 100); //WAVING SHIP WEIRD need ground move
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7540, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7580, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7620, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::WAVINGSHIP2, 7660, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, 7670, 100); //POWER UP 6

	//reset variables (camera position, players position...)
	App->render->camera.x = 0;
	App->render->camera.y = -100;
	stage = 0;

	positionGroundColumn.x = 2869;
	positionGroundColumn.y = -163;

	//enemies

	App->powerup->AddPowerUp(App->powerup->one_up, 4285, 220, COLLIDER_ONE_UP);

	//audio

	App->audio->PlayMusic("assets/Audio/11_Stage_4 -Caven-Intro.ogg");


	//enable modules
	App->player1->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->powerup->Enable();

	if (App->player2->insert2 == true)
	{
		App->player2->Enable();
	}

	return ret;
}

bool ModuleStage4::CleanUp() {
	//disable modules
	App->player1->Disable();
	App->player2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->powerup->Disable();
	App->enemies->Disable();
	//unload textures
	App->textures->Unload(back_tx);
	App->textures->Unload(ground_tx);

	time_music = 0;
	intro_bgm = true;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	

	return true;
}

update_status ModuleStage4::Update() {

	//Time
	if (intro_bgm)
		time_music = SDL_GetTicks() - init_time;

	time_backAnim = SDL_GetTicks() - time_preAnim;

	//Audio
	
	if (time_music >= 3750 && intro_bgm == true) {
		//Mix_PlayMusic(App->audio->stage4, -1);
		App->audio->PlayMusic("assets/Audio/11_Stage_4 -Caven-Loop.ogg", 0.0f);

		intro_bgm = false;
	}

	/*
	if (time_backAnim >= 3750) {
		//active blit bakcground animation
		light = true;
		time_preAnim = SDL_GetTicks();
		time_backAnim = 0;
	}
	*/


	//input
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN && App->ui->credit >= 1) {
		if (!App->player2->IsEnabled()) {
			App->player2->Enable();
			App->player2->position.x = App->player1->position.x;
			App->player2->position.y = 2 * SCREEN_HEIGHT / 3;
			App->player2->insert2 = true;
			App->ui->credit--;
		}
	}
	//logic

	

	for (int i = 0; i < 4; i++)
		App->render->Blit(back_tx, back.w*i, -50, NULL, BACKGROUND4SPEED);
	/*
	if (light) {
		SDL_Rect lighting = backlight.GetCurrentFrame();
		for (int i = 0; i < 4; i++)
			App->render->Blit(backlight_tx, back.w*i, -50, &lighting, BACKGROUND4SPEED);
		if (backlight.isInFrame(8)) {
			light = false;
			backlight.reset();
		}
	}
	*/

	App->render->Blit(ground_tx, positionGroundColumn.x, positionGroundColumn.y, &groundColumn, GROUND4SPEED); //-97

	//columnground moving
	if (App->render->camera.x >= 2813 * SCREEN_SIZE) {
		if (positionGroundColumn.y <= -133)
			positionGroundColumn.y = positionGroundColumn.y + 0.001f;
	}
	
	
	switch (stage) {
	case 0:				//scroll diagonal to y=43
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y += 1;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.y >= -2*SCREEN_SIZE)
			stage++;;
		break;
	case 1:				//scroll horizontal
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 1960 * SCREEN_SIZE)
			stage++;;
		break;
	case 2:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y--;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.y <= -97*SCREEN_SIZE)
			stage++;
		break;
	case 3:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 3092 * SCREEN_SIZE)
			stage++;
		break;
	case 4:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y += 1;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.y >= 113 * SCREEN_SIZE)
			stage++;
		break;
	case 5:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 7200 * SCREEN_SIZE)
			stage++;
		break;
	case 6:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->render->camera.y--;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.y <= 13 * SCREEN_SIZE)
			stage++;
		break;
	case 7:
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player1->position.x++;
		App->player2->position.x++;
		if (App->render->camera.x >= 7970 * SCREEN_SIZE)
			stage++;
		break;
	case 8:
		App->fade->FadeToBlack(this, App->stageclear, 0.5f);
		break;
	}	

	if (App->input->keyboard[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->stageclear, 1);
	}
		
	return UPDATE_CONTINUE;
}

update_status ModuleStage4::PostUpdate() {

	App->render->Blit(ground_tx, 1000, -97, &ground[0], GROUND4SPEED);
	
	App->render->Blit(ground_tx, 1000 + ground[0].w, 18, &ground[1], GROUND4SPEED);

	animation_water = &water;
	water_rect = animation_water->GetCurrentFrame();

	for (int i = 0; i < 5; i++)
		App->render->Blit(ground_tx, (1000 + ground[0].w + ground[1].w) + water_rect.w*i - 9, 316, &water_rect, GROUND4SPEED);

	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w, 52, &ground[2], GROUND4SPEED);
	App->render->Blit(ground_tx, 2511 + ground[0].w + ground[1].w + ground[2].w, 13, &ground[3], GROUND4SPEED);

	return UPDATE_CONTINUE;
}