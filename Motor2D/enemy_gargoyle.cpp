#include "j1App.h"
#include "enemy_gargoyle.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Enemies.h"

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
	
	animation = &fly;
	LOG("x %i y %i", position.x, position.y);
	collider = App->collision->AddCollider({ position.x, position.y, 35, 38 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->enemies);
}

void Enemy_gargoyle::Move(float dt)
{
	
	iPoint mapPos = App->map->WorldToMap(position.x, position.y);

	if (mapPos.x < App->enemies->playerMapPos.x + 5 && mapPos.x > App->enemies->playerMapPos.x - 5) {
		if (App->pathfinding->CreatePath(mapPos, App->enemies->playerMapPos) != -1) {
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			if (path->Count() > 0) {
				pathToFollow = iPoint(path->At(0)->x, path->At(0)->y);
				if (pathToFollow.x < mapPos.x) {
					gargoyleSpeed.x = -1.0f;
					animation = &attack;
				}
				else if (pathToFollow.x > mapPos.x) {
					gargoyleSpeed.x = 1.0f;
					animation = &attack;
				}
				if (pathToFollow.y < mapPos.y) {
					gargoyleSpeed.y = -1.0f;
					animation = &attack;
				}
				else if (pathToFollow.y > mapPos.y) {
					gargoyleSpeed.y = 1.0f;
					animation = &attack;
				}
			}
		}
	}

	position += gargoyleSpeed;

}

void Enemy_gargoyle::OnCollision(Collider* collider) {
}

uint Enemy_gargoyle::getHitPoints() {
	return hitPoints;
}

