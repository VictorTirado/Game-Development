#ifndef _ENEMY_GARGOYLE_H__ 
#define _ENEMY_GARGOYLE_H__

#include "j1Enemy.h"


class Enemy_gargoyle : public j1Enemy
{
private:
	Animation idle;
	Animation attackR;
	Animation attackL;
	Animation fly;
	iPoint original_pos;
	iPoint pathToFollow;
	iPoint gargoyleSpeed;

public:
	Enemy_gargoyle(int x, int y);
	void Move(float dt);
	void OnCollision(Collider* collider);
	uint getHitPoints();
};
#endif