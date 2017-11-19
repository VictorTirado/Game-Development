#include "j1App.h"
#include "enemy_boss.h"
#include "ModuleCollision.h"
#include "j1Particles.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1Pathfinding.h"
#include "j1Map.h"
#include "j1Enemies.h"
#include "j1Timer.h"
#

Enemy_Boss::Enemy_Boss(int x, int y) : j1Enemy(x, y)
{
	idle.PushBack({ 3404,512,399,347 });
	idle.PushBack({ 3005,512,399,347 });
	idle.PushBack({ 2600,512,399,347 });
	idle.PushBack({ 2185,514,399,347 });
	
	idle.speed = 0.1f;

	start_fly.PushBack({ 3408,2390,398,427 });
	start_fly.PushBack({ 3005,2390,398,427 });
	start_fly.speed = 0.1f;
	fly.PushBack({ 2568,2390,398,427 });
	fly.PushBack({ 2108,2390,512,427 });
	fly.PushBack({ 1685,2390,398,427 });
	fly.PushBack({ 1268,2390,398,427 });

	attack.PushBack({ 3416,1984,453,352 });
	attack.PushBack({ 3025,1981,379,354 });
	attack.PushBack({ 2538,1984,453,352 });
	attack.PushBack({ 2080,1984,543,352 });
	attack.PushBack({ 1616,1983,543,352 });
	attack.speed = 0.1f;
	attack.loop = 0.0f;
	attack_last_frame = { 1616,1983,543,352 };
	attack_frame = {2080,1984,543,352 };

	animation = &idle;
	LOG("x %i y %i", position.x, position.y);
	collider = App->collision->AddCollider({ position.x, position.y, 399, 347 }, COLLIDER_TYPE::COLLIDER_DRAKE, (j1Module*)App->enemies);
}

void Enemy_Boss::Move(float dt)
{
	
	timer2 = timer.ReadSec();
	if (timer2 >= time+6.0f) {
		animation = &attack;
		if (animation->GetCurrentFrame().x == attack_frame.x && animation->GetCurrentFrame().y == attack_frame.y && cont==0)
		{
			App->particles->AddParticle(App->particles->Dragonshot, position.x-10, position.y+195, COLLIDER_ENEMY, NULL, { -200*dt,0 });
			cont = 1;
		}
		if (animation->GetCurrentFrame().x == attack_last_frame.x && animation->GetCurrentFrame().y == attack_last_frame.y ) {
			time = timer2;
			cont = 0;
		}
	}
	else {
		attack.Reset();
		animation = &idle;
	}


}

void Enemy_Boss::OnCollision(Collider* collider) {
}

uint Enemy_Boss::getHitPoints() {
	return hitPoints;
}