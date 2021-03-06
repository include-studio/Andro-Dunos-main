#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 25


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
class ModuleStage4;
class ModuleGameOver;
class ModuleParticles;
class ModuleCollision;
class ModuleInsertCoin;
class ModuleEnemies;
class ModuleFonts;
class ModulePowerUp;
class ModuleUI;
class ModuleSubMainMenu;
class ModuleShieldPlayer1;
class ModuleShieldPlayer2;

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
	ModuleStage4* stage4 = nullptr;
	ModuleGameOver* gameover = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleInsertCoin* insertCoin = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleFonts* fonts = nullptr;
	ModulePowerUp* powerup = nullptr;
	ModuleUI* ui = nullptr;
	ModuleSubMainMenu* submainmenu = nullptr;
	ModuleShieldPlayer1* shield1 = nullptr;
	ModuleShieldPlayer2* shield2 = nullptr;

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