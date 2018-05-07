#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_Gamecontroller could not initialize! SDL_Error:\n");
		LOG(SDL_GetError());
	}
	
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keys[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	if (keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		controller1 = nullptr;
		controller2 = nullptr;
		if (controller)	controller = false;
		else if (!controller) controller = true;
	}

	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			return update_status::UPDATE_STOP;
	}

	if (controller == true && (controller1 == nullptr || controller2 == nullptr))
		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			if (SDL_IsGameController(i)) {
				if (controller1 == nullptr) {
					controller1 = SDL_GameControllerOpen(i);
					if (controller1) {
						char* mapping;
						mapping = SDL_GameControllerMapping(controller1);
						SDL_Log("Controller %i is mapped as \"%s\".", i, mapping);
						SDL_free(mapping);
						LOG("CONTROLLER1 INITIALIZED\n");
					}
					else {
						LOG("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
					}
				}
				else if (controller2 == nullptr) {
					controller2 = SDL_GameControllerOpen(i);
					if (controller2) {
						char* mapping;
						mapping = SDL_GameControllerMapping(controller2);
						SDL_Log("Controller %i is mapped as \"%s\".", i, mapping);
						SDL_free(mapping);
						LOG("CONTROLLER2 INITIALIZED\n");
					}
					else {
						LOG("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
					}
				}
			}
		}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}