#include "j1App.h"
#include "enemy_gargoyle.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"


Enemy_gargoyle::Enemy_gargoyle(int x, int y) : j1Enemy(x, y)
{
	idle.PushBack({464,319,35,38});

	fly.PushBack({ 17,326,39,33});
	fly.PushBack({ 128,325,39,30 });
	fly.PushBack({ 233,321,33,30 });
	fly.PushBack({ 336,317,38,30 });
	fly.speed = 0.1f;

	attack.PushBack({583,317,39,46});
	attack.PushBack({ 714,328,62,30 });
	attack.PushBack({ 834,320,39,57 });
	attack.speed = 0.1f;
	

}

void Enemy_gargoyle::Move()
{
	

}

void Enemy_gargoyle::OnCollision(Collider* collider) {
}

uint Enemy_gargoyle::getHitPoints() {
	return hitPoints;
}

