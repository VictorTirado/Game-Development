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



#include "SDL/include/SDL_timer.h"



j1Particles::j1Particles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	fire_ball.anim.PushBack({ 448,584,26,17});
	fire_ball.anim.PushBack({ 482,584,26,17 });
	fire_ball.anim.PushBack({ 516,584,26,17 });
	fire_ball.anim.PushBack({ 549,584,26,17 });

	thunder.anim.PushBack({ 0,0,70,14 });
	thunder.anim.PushBack({ 0,0,70,14 });
	thunder.anim.PushBack({0,0,70,14});
	thunder.anim.speed = 0.5f;

	iceL.anim.PushBack({ 0,0,41,45 });
	iceL.anim.PushBack({ 0,0,41,45 });
	iceL.anim.PushBack({ 0,0,41,45 });
	iceL.anim.PushBack({ 0,0,41,45 });
	iceL.anim.PushBack({318,398,41,45});
	iceL.anim.PushBack({ 442,398,41,45 });
	iceL.anim.PushBack({ 588,397,41,45 });
	iceL.anim.PushBack({ 11,482,41,45 });
	iceL.anim.PushBack({ 186,482,41,45 });
	iceL.anim.PushBack({ 336,482,41,45 });
	iceL.anim.PushBack({ 499,482,41,45 });
	iceL.anim.PushBack({ 648,482,41,45 });
	iceL.anim.PushBack({ 814,482,41,45 });
	iceL.anim.PushBack({ 966,482,41,45 });
	iceL.anim.speed = 0.1f;


	iceR.anim.PushBack({ 0,0,41,45 });
	iceR.anim.PushBack({ 0,0,41,45 });
	iceR.anim.PushBack({ 0,0,41,45 });
	iceR.anim.PushBack({ 0,0,41,45 });
	iceR.anim.PushBack({ 409,398,20,45 });
	iceR.anim.PushBack({ 533,398,41,45 });
	iceR.anim.PushBack({ 678,398,41,45 });
	iceR.anim.PushBack({ 102,482,41,45 });
	iceR.anim.PushBack({ 276,482,41,45 });
	iceR.anim.PushBack({ 426,482,41,45 });
	iceR.anim.PushBack({ 591,482,41,45 });
	iceR.anim.PushBack({ 742,482,41,45 });
	iceR.anim.PushBack({ 908,482,41,45 });
	iceR.anim.PushBack({ 1074,482,41,45 });
	iceR.anim.speed= 0.1f;
	
	
}

j1Particles::~j1Particles(){}

bool j1Particles::Start()
{
	LOG("Loading particles");

	return true;
}

bool j1Particles::Awake(pugi::xml_node& config)
{
	bool ret = true;
	return ret;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, fPoint speed)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->speed.x = speed.x;
			p->speed.y = speed.y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

 bool j1Particles::Update(float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(App->player->graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		}
	}

	return true;
}
bool j1Particles::CleanUp()
{
	LOG("Unloading particles");
	
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}


Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;


	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}