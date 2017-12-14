#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1Textures.h"
#include "j1Particles.h"
#include "Brofiler\Brofiler.h"
#include "j1Abilities.h"
#include "j1Timer.h"



#include "SDL/include/SDL_timer.h"

j1Abilities::j1Abilities()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

}

j1Abilities::~j1Abilities() {}

bool j1Abilities::Start()
{
	LOG("Loading abilities");

	return true;
}

bool j1Abilities::Awake(pugi::xml_node& config)
{
	bool ret = true;
	return ret;
}

void j1Abilities::AddAbility(const Ability& ability, const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, fPoint speed, int manacoast)
{
	BROFILER_CATEGORY("j1ParticlesAddParticle", Profiler::Color::AliceBlue);
	if (App->player->GodMode == true) {
		manacoast = 0;
	}
	for (uint i = 0; i < MAX_ACTIVE_ABILITIES; ++i)
	{
		if (active[i] == nullptr)
		{
			if (App->player->mana2 >= manacoast) {
				App->particles->AddParticle(particle, x, y, collider_type, delay, speed);
				App->player->mana2 -= manacoast;
				break;
			}
		}
	}
}

bool j1Abilities::Update(float dt)
{
	BROFILER_CATEGORY("j1ParticlesUpdate", Profiler::Color::AliceBlue);
	
	timer = secondsPased.ReadSec();
	if (timer >= time + 8.0f) {
		time = timer;
		if (App->player->mana2 < 100) {
			App->player->mana2 += 10;
		}
	}
	

	return true;
}

bool j1Abilities::CleanUp()
{
	LOG("Unloading particles");

	for (uint i = 0; i < MAX_ACTIVE_ABILITIES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

Ability::Ability()
{

}

Ability::Ability(const Ability& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Ability::~Ability()
{

}

bool Ability::Update()
{
	BROFILER_CATEGORY("ParticlesUpdate", Profiler::Color::AliceBlue);
	bool ret = true;



	return ret;
}
