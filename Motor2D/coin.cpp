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


Book::Book(int x, int y) : j1Enemy(x, y)
{
	idle.PushBack({ 2339,20,38,40 });
	idle.PushBack({ 2398,18,38,40 });
	idle.PushBack({ 2445,18,38,40 });
	
	idle.speed = 0.1f;
	animation = &idle;
	collider = App->collision->AddCollider({ position.x, position.y, 36, 40 }, COLLIDER_TYPE::COLLIDER_BOOKS, (j1Module*)App->enemies);
}



void Book::OnCollision(Collider* collider) {
}

