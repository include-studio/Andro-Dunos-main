#include "Globals.h"
#include "ModuleShield.h"
#include "Application.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"

ModuleShield::ModuleShield() {
	//animation and states define

}

ModuleShield::~ModuleShield() {}

bool ModuleShield::Start() {
	bool ret = true;

	//load assets

	//reset var

	return ret;
}

update_status ModuleShield::Update() {
	//logic

	//draw shields

	return UPDATE_CONTINUE;
}

bool ModuleShield::CleanUp() {
	//unload assets

	return true;
}

void ModuleShield::OnCollision(Collider* c1, Collider* c2) {
	//logic collision
		//hp shields
}

