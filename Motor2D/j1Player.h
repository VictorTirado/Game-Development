#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"
#include "ModuleCollision.h"

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();


	bool Save(pugi::xml_node&) const;

	bool Load(pugi::xml_node&);
	void ShotR(float dt);
	void ShotL(float dt);
	void ThunderR();
	void ThunderL();
	void Ice();
	void j1Player::OnCollision(Collider* c1, Collider* c2);
	

public:

	iPoint startPos = { 0, 1000 };
	iPoint position = { 0,0 };
	
	int cost_fire = 10;
	int cost_thunder = 10;
	int cost_ice = 20;
	bool dead= false;
	uint lifes = 3;
	int mana2 = 100;
	uint score = 0;
	uint coins_achieved = 0;
	int speed;
	int cont = 0;
	int cont2 = 0;
	Animation* current_animation = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* attributes = nullptr;
	Animation* manas = nullptr;
	Animation idle;
	Animation runR;
	Animation runL;
	Animation attack;
	Animation death;
	Animation meleeR;
	Animation meleeL;
	
	Animation shotR;
	Animation shotL;
	Animation jumpR;
	Animation jumpL;
	Animation levitate;
	
	bool Iceattack = false;
	bool jumping = false;
	bool levitating = false;
	bool attackingMelee = false;
	bool shooting = false;
	uint gid;
	SDL_RendererFlip flip;
	bool firstUpdate = true;
	bool spawnEnemies = true;
	SDL_Rect levitate_last_frame;
	SDL_Rect shoot_frameR;
	SDL_Rect shoot_last_frameR;
	SDL_Rect shoot_frameL;
	SDL_Rect shoot_last_frameL;
	SDL_Rect melee_frameR;
	SDL_Rect melee_last_frameR;
	SDL_Rect melee_frameL;
	SDL_Rect melee_last_frameL;

	SDL_Rect attack_last_frame;
	SDL_Rect attack_frame;
	bool GodMode = false;
	Collider* collider;

	
};


#endif
