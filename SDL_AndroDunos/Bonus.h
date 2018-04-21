#ifndef __BONUS_H__
#define __BONUS_H__

#include "ModulePowerUp.h"

struct Collider;

class Bonus :public ModulePowerUp{
	void OnCollision(Collider* c1, Collider* c2) override;
};
#endif // !__BONUS_H__
