#include "Globals.h"
#include "Application.h"
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
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"

ModuleStage4::ModuleStage4() {
	//background

	//ground

	//water

}

ModuleStage4::~ModuleStage4(){}

bool ModuleStage4::Start() {
	bool ret = true;
	//load textures
	//colliders
	//reset variables (camera position, players position...)
	//enemies
	//audio
	//enable modules
	return ret;
}

bool ModuleStage4::CleanUp() {
	//disable modules
	//unload textures
	return true;
}

update_status ModuleStage4::Update() {
	//input

	//logic

	//draw everithing

	return UPDATE_CONTINUE;
}