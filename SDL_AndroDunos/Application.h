#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 10

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleBackground;
class ModulePlayer1;
class ModulePlayer2;
class ModuleAudio;
class Module;
class ModuleFadeToBlack;
class ModuleMainMenu;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleMainMenu* mainmenu = nullptr;
	ModuleBackground* background = nullptr;
	ModulePlayer1* player1 = nullptr;
	ModulePlayer2* player2 = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* FadeToBlack = nullptr;

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