#include "j1App.h"
#include "coin.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Enemies.h"
#include "j1Timer.h"


entity_coin::entity_coin(int x, int y) : j1Enemy(x, y)
{
	idle.PushBack({ 2174,26,30,30 });
	idle.PushBack({ 2211,26,30,30 });
	idle.PushBack({ 2248,26,30,30 });
	idle.PushBack({ 2286,26,30,30 });

	idle.speed = 0.3f;

	animation = &idle;
	
	collider = App->collision->AddCollider({ position.x, position.y, 30, 30 }, COLLIDER_TYPE::COLLIDER_COIN, (j1Module*)App->enemies);
}



void entity_coin::OnCollision(Collider* collider) {
}

