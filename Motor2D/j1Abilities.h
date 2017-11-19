#ifndef __j1ABILITIES_H__
#define __j1ABILITIES_H__

#include "j1Module.h"

#include "p2Defs.h"
#include "p2Point.h"
#include "Animation.h"

#define MAX_ACTIVE_ABILITIES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Ability
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;

	Ability();
	Ability(const Ability& p);
	~Ability();
	bool Update();
};

class j1Abilities : public j1Module
{
public:
	j1Abilities();
	~j1Abilities();


	bool Awake(pugi::xml_node&);

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void AddAbility(const Ability& ability, const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, fPoint speed);

private:
	Ability* active[MAX_ACTIVE_ABILITIES];
	uint last_particle = 0;
	int time = 0;
	int timer;
	j1Timer secondsPased;

public:
	Ability fire_ballR;
	Ability fire_ballL;
	Ability iceL;
	Ability iceR;
	Ability thunderR;
	Ability thunderL;

};

#endif // __j1ABILITIES_H__
