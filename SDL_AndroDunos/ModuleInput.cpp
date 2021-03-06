#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	B[0] = SDL_CONTROLLER_BUTTON_A;
	B[1] = SDL_CONTROLLER_BUTTON_B;
	B[2] = SDL_CONTROLLER_BUTTON_X;
	B[3] = SDL_CONTROLLER_BUTTON_Y;
	B[4] = SDL_CONTROLLER_BUTTON_BACK;
	B[5] = SDL_CONTROLLER_BUTTON_GUIDE;
	B[6] = SDL_CONTROLLER_BUTTON_START;
	B[7] = SDL_CONTROLLER_BUTTON_LEFTSTICK;
	B[8] = SDL_CONTROLLER_BUTTON_RIGHTSTICK;
	B[9] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	B[10] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
	B[11] = SDL_CONTROLLER_BUTTON_DPAD_UP;
	B[12] = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	B[13] = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	B[14] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	B[15] = SDL_CONTROLLER_BUTTON_MAX;

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
		buttons1[i] = KEY_IDLE;
		buttons2[i] = KEY_IDLE;
	}
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


	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			return update_status::UPDATE_STOP;
	}

	if (controller1 == nullptr || controller2 == nullptr)
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
				else if (controller2 == nullptr && SDL_NumJoysticks()>1) {
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

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
			if (SDL_GameControllerGetButton(controller1, B[i])) {
				if (buttons1[i] == KEY_IDLE)
					buttons1[i] = KEY_DOWN;
				else
					buttons1[i] = KEY_REPEAT;
		}
			else {
				if (buttons1[i] == KEY_REPEAT || buttons1[i] == KEY_DOWN)
					buttons1[i] = KEY_UP;
				else
					buttons1[i] = KEY_IDLE;
			}
	}
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
		if (SDL_GameControllerGetButton(controller2, B[i])) {
			if (buttons2[i] == KEY_IDLE)
				buttons2[i] = KEY_DOWN;
			else
				buttons2[i] = KEY_REPEAT;
		}
		else {
			if (buttons2[i] == KEY_REPEAT || buttons2[i] == KEY_DOWN)
				buttons2[i] = KEY_UP;
			else
				buttons2[i] = KEY_IDLE;
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