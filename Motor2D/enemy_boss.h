#ifndef _ENEMY_BOSS_H__ 
#define _ENEMY_BOSS_H__

#include "j1Enemy.h"


class Enemy_Boss : public j1Enemy
{
private:
	Animation idle;
	Animation attack;
	Animation fly;
	Animation start_fly;
	iPoint original_pos;
	j1Timer timer;
	float time;
	float timer2;
	SDL_Rect attack_last_frame;

public:
	int lifes = 30;
	Enemy_Boss(int x, int y);
	void Move(float dt);
	void OnCollision(Collider* collider);
	uint getHitPoints();
};
#endif