#include "Globals.h"
#include "ModuleShieldPlayer1.h"
#include "Application.h"
#include "ModulePlayer1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleShieldPlayer1::ModuleShieldPlayer1() {
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

ModuleShieldPlayer1::~ModuleShieldPlayer1() {}

bool ModuleShieldPlayer1::Start() {
	bool ret = true;
	//load assets
	tx_shield = App->textures->Load("assets/Sprites/shield.png");

	shield1_col = App->collision->AddCollider({ position1.x,position1.y, 16,16 }, COLLIDER_SHIELD, this);
	shield2_col = App->collision->AddCollider({ position2.x,position2.y, 16,16 }, COLLIDER_SHIELD, this);

	//reset var
	hp = 5;

	return ret;
}

update_status ModuleShieldPlayer1::Update() {

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
	shield1_col->SetPos(position1.x, position1.y);
	shield2_col->SetPos(position2.x, position2.y);

	if (hp <= 0) {
		this->Disable();
		shield1_col->to_delete = true;
		shield2_col->to_delete = true;
	}

	return UPDATE_CONTINUE;
}

bool ModuleShieldPlayer1::CleanUp() {
	//unload assets
	App->textures->Unload(tx_shield);

	return true;
}

void ModuleShieldPlayer1::OnCollision(Collider* c1, Collider* c2) {
	//logic collision
		//hp shields
	if (c1->type == COLLIDER_SHIELD)
		if (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY_SHOT)
			hp--;
}

