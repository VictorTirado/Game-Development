#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Enemies.h"
#include "j1Particles.h"
#include "j1Textures.h"
#include "j1Enemy.h"
#include "enemy_gargoyle.h"
#include "ModuleCollision.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Window.h"


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
	sprites = App->tex->Load("Enemies/Enemies.png");
	if (sprites != nullptr) {
		LOG("Cargado");
	}
	return true;
}

bool j1Enemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (-queue[i].y < (App->render->camera.y / App->win->screen_surface->h) + SPAWN_MARGIN / 2)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				//LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);

			}

		}
	}



	return true;
}

// Called before render is available
bool j1Enemies::Update(float dt)
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();


	return true;
}

bool j1Enemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			//if (-enemies[i]->position.y *App->win->screen_surface->h < (App->render->camera.y) - SPAWN_MARGIN * 16)
			//{
			//	//LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
			//	delete enemies[i];
			//	enemies[i] = nullptr;
			//}
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
		case ENEMY_TYPES::Soldier:
			//enemies[i] = new Enemy(info.x, info.y);
			break;
		}
	}
}

void j1Enemies::OnCollision(Collider* c1, Collider* c2)
{

}