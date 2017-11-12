#ifndef _ENEMY_GARGOYLE_H__ 
#define _ENEMY_GARGOYLE_H__

#include "j1Enemy.h"


class Enemy_gargoyle : public j1Enemy
{
private:
	Animation idle;
	Animation attack;
	Animation fly;
	iPoint original_pos;
	iPoint pathToFollow;
	iPoint gargoyleSpeed;

public:
	Enemy_gargoyle(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	uint getHitPoints();
};
#endif