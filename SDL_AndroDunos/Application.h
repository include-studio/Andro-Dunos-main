#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 20 //20 with UI

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleStage1;
class ModulePlayer1;
class ModulePlayer2;
class ModuleAudio;
class Module;
class ModuleFadeToBlack;
class ModuleNeoGeo;
class ModuleViscoGames;
class ModuleMainMenu;
class ModuleStageClear;
class ModuleStage2;
class ModuleGameOver;
class ModuleParticles;
class ModuleCollision;
class ModuleInsertCoin;
class ModuleEnemies;
class ModuleFonts;
class ModuleUI;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleMainMenu* mainmenu = nullptr;
	ModuleStage1* stage1 = nullptr;
	ModulePlayer1* player1 = nullptr;
	ModulePlayer2* player2 = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleNeoGeo* neogeo = nullptr;
	ModuleViscoGames* visco = nullptr;
	ModuleStageClear* stageclear = nullptr;
	//ModuleStage2* stage2 = nullptr;
	ModuleGameOver* gameover = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleInsertCoin* insertCoin = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleUI* ui = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__