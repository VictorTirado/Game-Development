#include "j1App.h"
#include "enemy_knight.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Enemies.h"

Enemy_knight::Enemy_knight(int x, int y) : j1Enemy(x, y)
{
	idle.PushBack({7,165,67,62});
	idle.PushBack({ 84,165,67,62 });
	idle.PushBack({ 159,165,67,62 });
	idle.PushBack({ 227,165,67,62 });
	idle.PushBack({ 296,165,67,62 });
	idle.PushBack({ 366,165,67,62 });
	idle.PushBack({ 456,165,67,62 });
	idle.speed = 0.3f;
	

	animation = &idle;
	LOG("x %i y %i", position.x, position.y);
	collider = App->collision->AddCollider({ position.x, position.y, 67, 62 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->enemies);
}

void Enemy_knight::Move(float dt)
{

	iPoint mapPos = App->map->WorldToMap(position.x, position.y);

	if (mapPos.x < App->enemies->playerMapPos.x + 5 && mapPos.x > App->enemies->playerMapPos.x - 5) {
	if (App->pathfinding->CreatePath(mapPos, App->enemies->playerMapPos) != -1) {
	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
	if (path->Count() > 0) {
	pathToFollow = iPoint(path->At(0)->x, path->At(0)->y);
	if (pathToFollow.x < mapPos.x) {
		knightSpeed.x = -1.0f;
	}
	else if (pathToFollow.x > mapPos.x) {
		knightSpeed.x = 1.0f;
	}
	if (pathToFollow.y < mapPos.y) {
		knightSpeed.y = -1.0f;
	}
	else if (pathToFollow.y > mapPos.y) {
		knightSpeed.y = 1.0f;
	}
	}
	}
	}

	position += knightSpeed;

}

void Enemy_knight::OnCollision(Collider* collider) {
}

uint Enemy_knight::getHitPoints() {
	return hitPoints;
}