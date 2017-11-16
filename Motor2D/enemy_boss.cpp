#include "j1App.h"
#include "enemy_boss.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Enemies.h"

Enemy_Boss::Enemy_Boss(int x, int y) : j1Enemy(x, y)
{

	idle.PushBack({ 893,4,96,117 });
	idle.PushBack({ 775,4,96,117 });
	idle.PushBack({ 667,4,96,117 });
	idle.PushBack({ 555,4,96,117 });
	idle.PushBack({ 447,4,96,117 });
	idle.PushBack({ 340,4,96,117 });
	idle.PushBack({ 232,4,96,117 });
	idle.PushBack({ 124,4,96,117 });
	idle.PushBack({ 10,4,96,117 });
	idle.PushBack({ 87,131,96,117 });
	idle.PushBack({ 190,131,96,117 });
	idle.PushBack({ 305,131,96,117 });
	/*idle.PushBack({ 446,2,45,56 });
	idle.PushBack({ 387,2,45,56 });
	idle.PushBack({ 333,2,45,56 });
	idle.PushBack({ 278,2,45,56 });
	idle.PushBack({ 223,2,45,56 });
	idle.PushBack({ 169,2,45,56 });
	idle.PushBack({ 115,2,45,56 });
	idle.PushBack({ 61,2,47,56 });
	idle.PushBack({ 43,63,45,56 });
	idle.PushBack({ 95,63,48,56 });
	idle.PushBack({ 152,63,45,56 });*/
	idle.speed = 0.1f;

	//idle.PushBack({ 13,398,99,101 });

	/*fly.PushBack({ 17,326,39,33 });
	fly.PushBack({ 128,325,39,30 });
	fly.PushBack({ 233,321,33,30 });
	fly.PushBack({ 336,317,38,30 });
	fly.speed = 0.1f;*/


	attack.PushBack({ 583,317,39,46 });
	attack.PushBack({ 714,328,62,30 });
	attack.PushBack({ 834,320,39,57 });
	attack.speed = 0.1f;

	animation = &idle;
	LOG("x %i y %i", position.x, position.y);
	collider = App->collision->AddCollider({ position.x, position.y, 96, 117 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->enemies);
}

void Enemy_Boss::Move(float dt)
{

	/*iPoint mapPos = App->map->WorldToMap(position.x, position.y);

	if (mapPos.x < App->enemies->playerMapPos.x + 5 && mapPos.x > App->enemies->playerMapPos.x - 5) {
		if (App->pathfinding->CreatePath(mapPos, App->enemies->playerMapPos) != -1) {
			const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();
			if (path->Count() > 0) {
				pathToFollow = iPoint(path->At(0)->x, path->At(0)->y);
				if (pathToFollow.x < mapPos.x) {
					gargoyleSpeed.x = -1.0f;
				}
				else if (pathToFollow.x > mapPos.x) {
					gargoyleSpeed.x = 1.0f;
				}
				if (pathToFollow.y < mapPos.y) {
					gargoyleSpeed.y = -1.0f;
				}
				else if (pathToFollow.y > mapPos.y) {
					gargoyleSpeed.y = 1.0f;
				}
			}
		}
	}

	position += gargoyleSpeed;*/

}

void Enemy_Boss::OnCollision(Collider* collider) {
}

uint Enemy_Boss::getHitPoints() {
	return hitPoints;
}