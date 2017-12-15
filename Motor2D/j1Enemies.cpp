#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Enemies.h"
#include "j1Particles.h"
#include "j1Textures.h"
#include "j1Enemy.h"
#include "j1Scene.h"
#include "enemy_gargoyle.h"
#include "enemy_boss.h"
#include "enemy_knight.h"
#include "coin.h"
#include "ModuleCollision.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Map.h"
#include "Brofiler\Brofiler.h"


#define SPAWN_MARGIN 50

j1Enemies::j1Enemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
j1Enemies::~j1Enemies()
{
}

bool j1Enemies::Start()
{
	if (sprites == nullptr) {
		LOG("No cargado");
	}
	sprites = App->tex->Load("Enemies/enemies.png");
	if (sprites != nullptr) {
		LOG("Cargado");
	}
	return true;
}

bool j1Enemies::PreUpdate()
{
	BROFILER_CATEGORY("j1EnemiesPreUpdate", Profiler::Color::Cyan);
	if (App->player->spawnEnemies == true) {
		int iterator = 0;
	
		while (App->map->gargoyleSpawn.At(iterator) != NULL && App->map->knightSpawn.At(iterator) != NULL && App->map->drakeSpawn.At(iterator) != NULL) {
			AddEnemy(Gargoile, App->map->gargoyleSpawn.At(iterator)->data.x, App->map->gargoyleSpawn.At(iterator)->data.y);
			AddEnemy(Knight, App->map->knightSpawn.At(iterator)->data.x, App->map->knightSpawn.At(iterator)->data.y);
			AddEnemy(Final_Boss, App->map->drakeSpawn.At(iterator)->data.x-30, App->map->drakeSpawn.At(iterator)->data.y-256);
			iterator++;
		}
	
		App->player->spawnEnemies = false;
	}
	App->map->gargoyleSpawn.~p2List();
	App->map->knightSpawn.~p2List();
	App->map->drakeSpawn.~p2List();
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (-queue[i].y < (App->render->camera.y / App->win->screen_surface->h) + SPAWN_MARGIN / 2)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;

			}

		}
	}



	return true;
}

// Called before render is available
bool j1Enemies::Update(float dt)
{
	BROFILER_CATEGORY("j1EnemiesUpdate", Profiler::Color::Cyan);
	playerMapPos = App->map->WorldToMap(App->player->position.x, App->player->position.y);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move(dt);
	if (App->player->dead == true)
	{
		App->player->dead = false;
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) {
			uint gid = App->map->Get_gid(enemies[i]->position.x, enemies[i]->position.y);
			if (enemies[i]->type == Knight && App->map->data.maplayers.end->data->data[gid + 150] == 1087) {
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}



	return true;
}

bool j1Enemies::PostUpdate()
{
	BROFILER_CATEGORY("j1EnemiesPostUpdate", Profiler::Color::Cyan);
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y *App->win->screen_surface->h < (App->render->camera.y) - SPAWN_MARGIN * 16)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return true;
}

// Called before quitting
bool j1Enemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->tex->UnLoad(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		queue[i].type = NO_TYPE;
	}

	return true;
}

bool j1Enemies::FreeEnemies()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		queue[i].type = NO_TYPE;
	}

	return true;
}

bool j1Enemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void j1Enemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::Gargoile:
			enemies[i] = new Enemy_gargoyle(info.x, info.y);
			break;
		case ENEMY_TYPES::Knight:
			enemies[i] = new Enemy_knight(info.x, info.y);
			break;
		case ENEMY_TYPES::Final_Boss:
			enemies[i] = new Enemy_Boss(info.x, info.y);
			break;
		case ENEMY_TYPES::Coin:
			enemies[i] = new entity_coin(info.x, info.y);
			break;
		}
	}
}

void j1Enemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			if (enemies[i]->GetCollider() == c1) {
				if (c2->type == COLLIDER_ATTACK && c1->type != COLLIDER_DRAKE) {
					delete enemies[i];
					enemies[i] = nullptr;
				}
				else if (c2->type == COLLIDER_ATTACK && c1->type == COLLIDER_DRAKE) {
					bossHP--;
					c2->to_delete = true;
					if (bossHP <= 0) {
						delete enemies[i];
						enemies[i] = nullptr;
					}
					LOG("BOSS");
				}
				else if (c2->type == COLLIDER_PLAYER && c1->type == COLLIDER_COIN) {
					App->player->coins_achieved++;
					delete enemies[i];
					enemies[i] = nullptr;

				}
			}
		}


	}
}