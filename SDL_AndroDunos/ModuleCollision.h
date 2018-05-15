#ifndef __MODULECOLLISION_H__
#define __MODULECOLLISION_H__

#define MAX_COLLIDERS 500

#include "Module.h"

enum COLLIDER_TYPE {
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_WALL4,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_BONUS,
	COLLIDER_POWER_S,
	COLLIDER_ONE_UP,
	COLLIDER_DEAD,
	COLLIDER_SHIELD,
	

	COLLIDER_MAX
};
struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};
class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
};
#endif // !__MODULECOLLISION_H__
