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
	idle.PushBack({ 3404,512,399,347 });
	idle.PushBack({ 3005,512,399,347 });
	idle.PushBack({ 2600,512,399,347 });
	idle.PushBack({ 2185,514,399,347 });
	
	idle.speed = 0.01f;

	//idle.PushBack({ 13,398,99,101 });

	/*fly.PushBack({ 17,326,39,33 });
	fly.PushBack({ 128,325,39,30 });
	fly.PushBack({ 233,321,33,30 });
	fly.PushBack({ 336,317,38,30 });
	fly.speed = 0.1f;*/

	attack.PushBack({ 3416,1984,453,352 });
	attack.PushBack({ 3025,1981,379,354 });
	attack.PushBack({ 2538,1984,453,352 });
	attack.PushBack({ 2080,1984,543,352 });
	attack.PushBack({ 1616,1983,543,352 });
	attack.speed = 0.1f;

	animation = &attack;
	LOG("x %i y %i", position.x, position.y);
	collider = App->collision->AddCollider({ position.x, position.y, 399, 347 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->enemies);
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