#ifndef __J1ENEMY_H__
#define __J1ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct Path;
struct SDL_Texture;
struct Collider;

class j1Enemy
{
protected:
	Animation* animation = nullptr;
	uint hitPoints;
	uint currentTime;
	uint lastTime;
	int time = 0;
	bool shot;
	bool hit_animation;

public:
	Collider* collider = nullptr;
	iPoint position;
	int type;
	int score;
	int id;

public:
	j1Enemy(int x, int y);
	virtual ~j1Enemy();

	const Collider* GetCollider() const;

	virtual void Move(float dt) {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual uint getHitPoints() { return 0; }
};

#endif // __J1ENEMY_H__