#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Particles.h"
#include "j1FadeToBlack.h"
#include "ModuleCollision.h"
#include "j1Enemies.h"
#include "Brofiler\Brofiler.h"


j1Player::j1Player() : j1Module()
{

	name.create("player");
	//IDLE
	idle.PushBack({ 70,17,46,69 });

	//RUN
	//run.PushBack({ 146,17,46,69 });
	runR.PushBack({ 221,17,47,69 });
	runR.PushBack({ 47,107,39,68 });
	runR.PushBack({ 127,106,43,69 });
	runR.PushBack({ 208,106,45,68 });
	runR.PushBack({ 287,105,43,69 });
	runR.PushBack({ 127,106,46,69 });
	runR.PushBack({ 208,106,46,69 });
	runR.PushBack({ 287,105,46,69 });
	runR.speed = 0.10f;


	runL.PushBack({ 2082,17,47,69 });
	runL.PushBack({ 2264,107,39,68 });
	runL.PushBack({ 2180,106,43,69 });
	runL.PushBack({ 2097,106,45,68 });
	runL.PushBack({ 2020,105,43,69 });
	runL.PushBack({ 2180,106,43,69 });
	runL.PushBack({ 2097,106,45,68 });
	runL.PushBack({ 2020,105,43,69 });
	runL.speed = 0.10f;

	//JUMP

	jumpR.PushBack({ 42,186,46,78 });
	jumpR.PushBack({ 106,187,44,78});
	jumpR.PushBack({ 170,189,44,78 });
	
	jumpR.speed=0.10f;
	jumpR.loop = 0.0f;

	jumpL.PushBack({ 2262,186,46,78 });
	jumpL.PushBack({ 2200,187,44,78 });
	jumpL.PushBack({ 2136,189,44,78 });

	jumpL.speed = 0.10f;
	jumpL.loop = 0.0f;

	//Levitate
	levitate.PushBack({ 622,241,46,78 });
	
	levitate.PushBack({ 689,241,46,78 });
	levitate.PushBack({ 767,244,46,78 });
	levitate.PushBack({833,248,46,78});
	levitate.speed = 0.02f;
	levitate_last_frame = { 833,248,46,78 };

	//ICE
	attack.PushBack({ 29,377,49,69 });
	attack.PushBack({ 84,377,49,69 });
	attack.PushBack({ 149,379,49,69 });
	attack.PushBack({ 256,375,50,69});
	attack.PushBack({ 359,373,50,69 });
	attack.PushBack({ 484,373,50,69 });
	attack.PushBack({ 630,372,50,69 });
	attack.PushBack({ 53,457,50,69 });
	attack.PushBack({ 228,457,50,69 });
	attack.PushBack({ 378,457,50,69 });
	attack.PushBack({ 541,455,50,69 });
	attack.PushBack({ 692,454,50,69 });
	attack.PushBack({ 858,455,50,69 });
	attack.PushBack({ 1017,457,50,69 });

	attack_frame = { 256,375,50,69 };
	attack_last_frame = { 1017,457,50,69 };
	attack.speed = 0.1f;

	//THUNDER
	meleeR.PushBack({ 442,98,46,69 });
	meleeR.PushBack({ 501,98,55,69 });
	meleeR.PushBack({ 558,98,73,69 });
	meleeR.PushBack({ 702,92,76,69 });
	meleeR.PushBack({ 848,97,73,69 });
	melee_frameR = { 558,98,73,69 };
	melee_last_frameR = { 848,97,73,69 };
	meleeR.speed = 0.15f;

	meleeL.PushBack({ 1862,98,46,69 });
	meleeL.PushBack({ 1794,98,55,69 });
	meleeL.PushBack({ 1719,98,73,69 });
	meleeL.PushBack({ 1564,104,76,69 });
	meleeL.PushBack({ 1421,109,73,69 });
	melee_frameL = { 1719,98,73,69 };
	melee_last_frameL = { 1421,109,73,69 };
	meleeL.speed = 0.15f;

	


	//FIRE
	shotR.PushBack({ 22,550,46,69 });
	shotR.PushBack({ 83,551,49,70 });
	shotR.PushBack({ 152,553,59,71 });
	shotR.PushBack({ 232,554,56,70 });
	shotR.PushBack({ 315,555,49,69 });
	shotR.PushBack({ 385,556,46,69 });
	shotR.speed = 0.15f;
	shoot_frameR = { 152,553,59,71 };
	shoot_last_frameR = { 385,556,46,69 };

	shotL.PushBack({ 2282,550,46,69 });
	shotL.PushBack({ 2218,551,49,70 });
	shotL.PushBack({ 2139,553,59,71 });
	shotL.PushBack({ 2062,554,56,70 });
	shotL.PushBack({ 1986,555,49,69 });
	shotL.PushBack({ 1919,556,46,69 });
	shotL.speed = 0.15f;
	shoot_frameL = { 2139,553,59,71 };
	shoot_last_frameL = { 1919,556,46,69 };
	

	//DEATH
	death.PushBack({ 38,282,46,69 });
	death.PushBack({ 93,289,45,62 });
	death.PushBack({ 147,315,45,62 });
	death.PushBack({ 230,315,45,62 });
	death.PushBack({ 314,312,75,38 });
	
}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	startPos = App->map->spawn;
	LOG("SpawnCoords %d %d",App->map->spawn.x, App->map->spawn.y);
	position = startPos;
	speed = 1;
	LOG("Loading player textures");
	
	attributes = App->tex->Load("player/Attributes.png");
	graphics = App->tex->Load("player/Player.png");
	collider = App->collision->AddCollider({ position.x, position.y, 46, 69 }, COLLIDER_PLAYER, this);

	
	return ret;
}

bool j1Player::PreUpdate()
{
	BROFILER_CATEGORY("j1PlayerPreUpdate", Profiler::Color::DodgerBlue);
	bool ret = true;
	return ret;
}

bool j1Player::Update(float dt)
{

	BROFILER_CATEGORY("j1PlayerUpdate", Profiler::Color::DodgerBlue);
	startPos.x = App->map->spawn.x;
	startPos.y = App->map->spawn.y;
	if (firstUpdate == true) {
		position = startPos;
		App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		App->render->camera.y = position.y - (App->win->screen_surface->h);
		collider = App->collision->AddCollider({ position.x, position.y, 46, 69 }, COLLIDER_PLAYER, this);
		App->enemies->AddEnemy(Final_Boss, position.x + 60, position.y + 5);
		//App->enemies->AddEnemy(Knight, position.x + 60, position.y -30);
		/*if (App->scene->map=2) {
			App->enemies->AddEnemy(Final_Boss, position.x + 60, position.y - 30);
		}*/
		spawnEnemies = true;
		firstUpdate = false;
	}
	gid=App->map->Get_gid(position.x, position.y);
	bool ret = true;
	current_animation = &idle;
	flip = SDL_FLIP_NONE;
	
	if (mana2 >= 80) {
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && jumping == false && current_animation == &idle && Iceattack==false)
		{
			Iceattack = true;
			//mana2 -= 80;
			
			
		}
	}
	if (mana2 >= 20) {
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT && current_animation != &meleeR)
		{
			//mana2 -= 20;
			attackingMelee = true;
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				flip = SDL_FLIP_HORIZONTAL;
			}
		}
	}
	if (mana2 >= 40) {
		if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_REPEAT && current_animation != &shotR)
		{

			//mana2 -= 40;
			shooting = true;
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				flip = SDL_FLIP_HORIZONTAL;
			}
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && Iceattack == false && attackingMelee==false &&shooting==false)
	{
		current_animation = &runL;
		if (App->map->data.maplayers.end->data->data[gid - 1] != 1132) {
			position.x -= 150*dt;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
		flip = SDL_FLIP_HORIZONTAL;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && Iceattack == false && attackingMelee == false && shooting == false)
	{
		current_animation = &runR;
		if (App->map->data.maplayers.end->data->data[gid+1]!=1132) {
			position.x +=200*dt;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
	}
	
	
	

	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_REPEAT)
	{
		current_animation = &death;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && current_animation != &jumpL && current_animation != &jumpR && current_animation != &attack)
	{
		jumping = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN && jumping == true)
	{
		levitating = true;
	}

	//if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	//{
	//	App->cap = !App->cap;
	//}
	

	if (jumping == true) {
		current_animation = &jumpR;
		if (cont < 50 && cont2!=1) {
			position.y = position.y - dt*100;
			App->render->camera.y = App->render->camera.y + dt*100;
			if (cont == 49) {
				cont2 = 1;
			}
			cont++;
		}
		if (levitating == true) {
			current_animation = &levitate;
			if (levitate.GetCurrentFrame().x == levitate_last_frame.x && levitate.GetCurrentFrame().y == levitate_last_frame.y) {
				levitate.Reset();
				levitating = false;
			}
		}
		if (cont > 0 && cont2 != 0 && levitating==false) {
			if (App->map->data.maplayers.end->data->data[gid+150] != 1132) {
				position.y = position.y + 200*dt;
				App->render->camera.y = App->render->camera.y - dt*200;
				if (App->map->data.maplayers.end->data->data[gid + 150] == 1087) {
					App->collision->EraseCollider(collider);
					firstUpdate = true;
				}
			}
			if (App->map->data.maplayers.end->data->data[gid + 150] == 1132) {
				cont = 0;
				cont2 = 0;
				jumpR.Reset();
				jumping = false;
			}
		}
	}
	if (Iceattack == true)
	{
		current_animation = &attack;
		if (current_animation->GetCurrentFrame().x == attack_frame.x &&current_animation->GetCurrentFrame().y == attack_frame.y) {
			Ice();
		}
		if (current_animation->GetCurrentFrame().x == attack_last_frame.x &&current_animation->GetCurrentFrame().y == attack_last_frame.y)
		{
			Iceattack = false;
		}
	}
	else {
		attack.Reset();
	}

	if (attackingMelee == true) {
		if (flip == SDL_FLIP_HORIZONTAL)
		{
			current_animation = &meleeL;
			if (melee_frameL.x == meleeL.GetCurrentFrame().x && melee_frameL.y == meleeL.GetCurrentFrame().y) {
				ThunderL();
			}
			if (melee_last_frameL.x == meleeL.GetCurrentFrame().x && melee_last_frameL.y == meleeL.GetCurrentFrame().y) {
				attackingMelee = false;
			}
		}
		else {
			current_animation = &meleeR;
			if (melee_frameR.x == meleeR.GetCurrentFrame().x && melee_frameR.y == meleeR.GetCurrentFrame().y) {
				ThunderR();
			}
			if (melee_last_frameR.x == meleeR.GetCurrentFrame().x && melee_last_frameR.y == meleeR.GetCurrentFrame().y) {
				attackingMelee = false;
			}
		}	
	}
	else {
		meleeR.Reset();
		meleeL.Reset();
	}

	if (shooting == true) {
		if (flip == SDL_FLIP_HORIZONTAL)
		{
			current_animation = &shotL;
			if (shoot_frameL.x == shotL.GetCurrentFrame().x && shoot_frameL.y == shotL.GetCurrentFrame().y) {
				ShotL();
			}
			if (shoot_last_frameL.x == shotL.GetCurrentFrame().x && shoot_last_frameL.y == shotL.GetCurrentFrame().y) {
				shooting = false;
			}
		}
		else {
			current_animation = &shotR;
			if (shoot_frameR.x == shotR.GetCurrentFrame().x && shoot_frameR.y == shotR.GetCurrentFrame().y) {
				ShotR();
			}
			if (shoot_last_frameR.x == shotR.GetCurrentFrame().x && shoot_last_frameR.y == shotR.GetCurrentFrame().y) {
				shooting = false;
			}
		}
	}
	else {
		shotR.Reset();
		shotL.Reset();
	}
	if (App->map->data.maplayers.end->data->data[gid + 150] != 1132 && jumping == false) {
		current_animation = &jumpR;
		position.y = position.y + dt*100;
		App->render->camera.y = App->render->camera.y - dt * 100;
		if (App->map->data.maplayers.end->data->data[gid + 150 ] == 1087) {
			App->collision->EraseCollider(collider);
			firstUpdate = true;
		}
	}

	if (App->map->data.maplayers.end->data->data[gid] == 1087) {
		dead = true;
		App->collision->EraseCollider(collider);
		firstUpdate = true;
	}

	if (App->map->data.maplayers.end->data->data[gid + 1] == 1131) {
		if (App->scene->map == 1)
		{
			App->map->CleanUp();
			/*App->enemies->CleanUp();*/
			App->fade->FadeToBlack(1);
			App->map->Load("Map3.tmx");
			firstUpdate = true;
			App->collision->EraseCollider(collider);
			App->scene->map = 0;
		}
		
		else
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map3.tmx"); 
			firstUpdate = true;
			App->collision->EraseCollider(collider);
			App->scene->map = 0;
		}
	}
	collider->SetPos(position.x , position.y);
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()),1);
	
	
	return ret;
}

bool j1Player::PostUpdate()
{
	BROFILER_CATEGORY("j1PlayerPostUpdate", Profiler::Color::DodgerBlue);
	bool ret = true;
	return ret;
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	SDL_DestroyTexture(graphics);

	//App->textures->Unload(graphics);
	App->collision->EraseCollider(collider);

	return true;
}

void j1Player::ShotR()
{
	App->particles->AddParticle(App->particles->fire_ballR, position.x +25, position.y + 25, COLLIDER_ATTACK, NULL, { 5,0 });
}

void j1Player::ShotL()
{
	App->particles->AddParticle(App->particles->fire_ballL, position.x - 25, position.y + 25, COLLIDER_ATTACK, NULL, { -5,0 });
}

void j1Player::ThunderR()
{
	App->particles->AddParticle(App->particles->thunderR, position.x + 73, position.y + 40, COLLIDER_ATTACK, NULL, { 0,0 });
}
void j1Player::ThunderL()
{
	App->particles->AddParticle(App->particles->thunderL, position.x - 51, position.y + 40, COLLIDER_ATTACK, NULL, { 0,0 });
}
void j1Player::Ice()
{
	App->particles->AddParticle(App->particles->iceR, position.x + 45, position.y + 25, COLLIDER_ATTACK, NULL, { 0,0 });
	App->particles->AddParticle(App->particles->iceL, position.x - 41, position.y + 25, COLLIDER_ATTACK, NULL, { 0,0 });
}

bool j1Player::Save(pugi::xml_node& save) const
{
	bool ret = false;
	if (save.child("pos") == NULL || save.child("map") == NULL) {
		save.append_child("pos").append_attribute("x") = position.x;
		save.child("pos").append_attribute("y") = position.y;
		save.append_child("map").append_attribute("z") = App->scene->map;
	}
	else {
		save.child("pos").attribute("x") = position.x;
		save.child("pos").attribute("y") = position.y;
		save.child("map").attribute("z") = App->scene->map;
	}

	ret = true;
	return ret;
}

bool j1Player::Load(pugi::xml_node& save)
{
	bool ret = false;

	if (save.child("pos") != NULL || save.child("map") != NULL) {
		position.x = save.child("pos").attribute("x").as_float();
		position.y = save.child("pos").attribute("y").as_float();
		App->scene->map = save.child("map").attribute("z").as_int();
		if (App->scene->map == 1)
		{
			App->map->Load("Map1.tmx");
		}
		if (App->scene->map == 0)
		{
			App->map->Load("Map3.tmx");
		}
	}
	ret = true;
	return ret;	
}

void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_ENEMY) {
		dead = true;
		App->collision->EraseCollider(collider);
		firstUpdate = true;
	}
}

