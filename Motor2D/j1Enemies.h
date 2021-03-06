#ifndef __j1Enemies_H__
#define __j1Enemies_H__


#include "j1Module.h"
#include "ModuleCollision.h"

#define MAX_ENEMIES 50


enum ENEMY_TYPES
{
	NO_TYPE,
	Gargoile,
	Knight,
	Final_Boss,
	Books,
};

class j1Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class j1Enemies : public j1Module
{
public:

	j1Enemies();
	~j1Enemies();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool FreeEnemies();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y);

	iPoint playerMapPos;
	int bossHP = 60;
	SDL_Texture* tile_x = nullptr;

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	j1Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites = NULL;
	SDL_Texture* final_boss = NULL;

	float proj_speed = 5.0f;
	float speed_x_mult, speed_y_mult, common_mult, a_mult;


};

#endif // __j1Enemies_H__
