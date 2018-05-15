#include "Globals.h"
#include "ModuleShield.h"
#include "Application.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleShield::ModuleShield() {
	//animation and states define

}

ModuleShield::~ModuleShield() {}

bool ModuleShield::Start() {
	bool ret = true;
	//load assets
	tx_shield = App->textures->Load("assets/Sprites/shield.png");

	//reset var

	return ret;
}

update_status ModuleShield::Update() {
	//logic
	position.x = App->player1->position.x + 39 + 20;
	position.y = App->player1->position.y;
	//draw shields
	SDL_Rect shield_r = { 18,22,13,16 };
	App->render->Blit(tx_shield, position.x, position.y, &shield_r);

	return UPDATE_CONTINUE;
}

bool ModuleShield::CleanUp() {
	//unload assets
	App->textures->Unload(tx_shield);

	return true;
}

void ModuleShield::OnCollision(Collider* c1, Collider* c2) {
	//logic collision
		//hp shields
}

