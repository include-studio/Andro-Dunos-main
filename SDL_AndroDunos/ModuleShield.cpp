#include "Globals.h"
#include "ModuleShield.h"
#include "Application.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleShield::ModuleShield() {
	//animation and states define
	//p1.PushBack({})
	for (int i = 0; i < 6; i++) {
		s2u.PushBack({ 0, 34 + i * 14, 16, 14 });
		s2d.PushBack({ 16, 34 + i * 14, 16, 14 });
	}
	s2u.loop = true;
	s2d.loop = true;
	s2u.speed = 0.7f;
	s2d.speed = 0.7f;

	for (int i = 0; i < 6; i++)
		s3.PushBack({ i * 14,0,14,16 });
	s3.loop = true;
	s3.speed = 0.7f;

	for (int i = 0; i < 6; i++)
		s4.PushBack({ i * 14,16,14,16 });
	s4.loop = true;
	s4.speed = 0.7f;

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

	switch (App->player1->type_weapon) {
	case 1:
		position1.x=App->player1->position.x + int(27.0f * cosf(rotation))+15;
		position1.y = App->player1->position.y + int(27.0f * sinf(rotation));
		position2.x = App->player1->position.x + int(27.0f * cosf(rotation+PI)) + 15;
		position2.y = App->player1->position.y + int(27.0f * sinf(rotation+PI));
		rotation += 0.13f;
		App->render->Blit(tx_shield, position1.x, position1.y, &s3.GetCurrentFrame());
		App->render->Blit(tx_shield, position2.x, position2.y, &s3.GetCurrentFrame());
		break;
	case 2:
		position1.x = App->player1->position.x + 16;
		position1.y = App->player1->position.y - 15;
		position2.x = App->player1->position.x + 16;
		position2.y = App->player1->position.y + 20;
		App->render->Blit(tx_shield, position1.x, position1.y, &s2u.GetCurrentFrame());
		App->render->Blit(tx_shield, position2.x, position2.y, &s2d.GetCurrentFrame());
		break;
	case 3:
		SDL_Rect shield_f = s3.GetCurrentFrame(); //in this case we use rects because 2 objects use de same animation, so, if we put GetCurrentFrame() in blit the one shield will be one frame next the other
		position1.x = App->player1->position.x + 36;
		position1.y = App->player1->position.y - 8;
		position2.x = App->player1->position.x + 36;
		position2.y = App->player1->position.y + 14;
		App->render->Blit(tx_shield, position1.x, position1.y, &shield_f);
		App->render->Blit(tx_shield, position2.x, position2.y, &shield_f);
		break;
	case 4:
		SDL_Rect shield_b = s4.GetCurrentFrame(); 
		position1.x = App->player1->position.x -2;
		position1.y = App->player1->position.y - 8;
		position2.x = App->player1->position.x -2;
		position2.y = App->player1->position.y + 14;
		App->render->Blit(tx_shield, position1.x, position1.y, &shield_b);
		App->render->Blit(tx_shield, position2.x, position2.y, &shield_b);
		break;
	}
	

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

