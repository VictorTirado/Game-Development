#ifndef _ENEMY_KNIGHT_H__ 
#define _ENEMY_KNIGHT_H__

#include "j1Enemy.h"


class Enemy_knight : public j1Enemy
{
private:
	Animation idle;
	Animation attack;
	Animation run;
	iPoint original_pos;
	iPoint pathToFollow;
	iPoint knightSpeed;

public:
	Enemy_knight(int x, int y);
	void Move();
	void OnCollision(Collider* collider);
	uint getHitPoints();
};
#endif