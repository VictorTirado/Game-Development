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


j1Player::j1Player() : j1Module()
{

	name.create("player");
	//IDLE
	idle.PushBack({ 70,17,46,69 });

	//RUN
	//run.PushBack({ 146,17,46,69 });
	run.PushBack({ 221,17,47,69 });
	run.PushBack({ 47,107,39,68 });
	run.PushBack({ 127,106,43,69 });
	run.PushBack({ 208,106,45,68 });
	run.PushBack({ 287,105,43,69 });
	run.PushBack({ 127,106,46,69 });
	run.PushBack({ 208,106,46,69 });
	run.PushBack({ 287,105,46,69 });
	run.speed = 0.10f;

	//JUMP

	jump.PushBack({ 42,186,46,78 });
	jump.PushBack({ 106,187,44,78});
	jump.PushBack({ 170,189,44,78 });
	
	jump.speed=0.10f;
	jump.loop = 0.0f;

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
	attack.speed = 0.1f;

	//THUNDER
	melee.PushBack({ 442,98,46,69 });
	melee.PushBack({ 501,98,55,69 });
	melee.PushBack({ 558,98,100,69 });
	melee.PushBack({ 675,104,127,69 });
	melee.PushBack({ 821,109,100,69 });
	melee.speed = 0.15f;

	


	//FIRE
	shot.PushBack({ 22,550,46,69 });
	shot.PushBack({ 83,551,49,70 });
	shot.PushBack({ 152,553,59,71 });
	shot.PushBack({ 232,554,56,70 });
	shot.PushBack({ 315,555,49,69 });
	shot.PushBack({ 385,556,46,69 });
	shot.speed = 0.15f;
	shoot_frame = { 152,553,59,71 };
	shoot_last_frame = { 385,556,46,69 };

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
	bool ret = true;
	return ret;
}

bool j1Player::Update(float dt)
{

	
	startPos.x = App->map->spawn.x;
	startPos.y = App->map->spawn.y;
	if (firstUpdate == true) {
		position = startPos;
		App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		App->render->camera.y = position.y - (App->win->screen_surface->h);
		collider = App->collision->AddCollider({ position.x, position.y, 46, 69 }, COLLIDER_PLAYER, this);
		App->enemies->AddEnemy(Gargoile, position.x + 60, position.y + 5);
		//App->enemies->AddEnemy(Knight, position.x + 60, position.y -30);
		//App->enemies->AddEnemy(Final_Boss, position.x + 60, position.y - 30);
		firstUpdate = false;
	}
	gid=App->map->Get_gid(position.x/*-75*/, position.y);
	bool ret = true;
	current_animation = &idle;
	flip = SDL_FLIP_NONE;
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && current_animation)
	{
		current_animation = &run;
		if (App->map->data.maplayers.end->data->data[gid - 1] != 1132) {
			position.x -= 5 * speed;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
		flip = SDL_FLIP_HORIZONTAL;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && current_animation != &attack)
	{
		current_animation = &run;
		if (App->map->data.maplayers.end->data->data[gid+1]!=1132) {
			position.x += 5 * speed;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
	}
	if (mana2 >= 80) {
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT && jumping == false)
		{
			//mana2 -= 80;
			current_animation = &attack;
			Ice();
		}
	}
	if (mana2 >= 20) {
		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT && current_animation != &melee)
		{
			//mana2 -= 20;
			attackingMelee = true;
			Thunder();
		}
	}
	if (mana2 >= 40) {
		if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_REPEAT && current_animation != &shot)
		{
			//mana2 -= 40;
			shooting = true;
			//current_animation = &shot;
			//Shot();
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_REPEAT)
	{
		current_animation = &death;
	}
	if (mana2 >= 30) {
		if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
		{
			mana2 -= 30;
			current_animation = &levitate;
		}
	}
	


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && current_animation != &jump && current_animation != &attack)
	{
		jumping = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN)
	{
		levitating = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP)
	{
		levitating = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		App->cap = !App->cap;
	}
	

	if (jumping == true) {
		current_animation = &jump;
		if (cont < 50 && cont2!=1) {
			position.y = position.y - speed*4;
			App->render->camera.y = App->render->camera.y + speed*4;
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
				position.y = position.y + speed * 4;
				App->render->camera.y = App->render->camera.y - speed * 4;
				if (App->map->data.maplayers.end->data->data[gid + 150] == 1087) {
					App->collision->EraseCollider(collider);
					firstUpdate = true;
				}
			}
			if (App->map->data.maplayers.end->data->data[gid + 150] == 1132) {
				cont = 0;
				cont2 = 0;
				jump.Reset();
				jumping = false;
			}
		}
	}

	if (attackingMelee == true) {
		current_animation = &melee;
		Thunder();
		if (melee.Finished() == true) {
			attackingMelee = false;
		}
	}
	else
		melee.Reset();

	if (shooting == true) {
		current_animation = &shot;
		if (shoot_frame.x == shot.GetCurrentFrame().x && shoot_frame.y == shot.GetCurrentFrame().y) {
			Shot();
		}
		if (shoot_last_frame.x == shot.GetCurrentFrame().x && shoot_last_frame.y == shot.GetCurrentFrame().y) {
			shooting = false;
		}
	}
	else {
		shot.Reset();
	}
	if (App->map->data.maplayers.end->data->data[gid + 150] != 1132 && jumping == false) {
		current_animation = &jump;
		position.y = position.y + speed * 4;
		App->render->camera.y = App->render->camera.y - speed * 4;
		if (App->map->data.maplayers.end->data->data[gid + 150 ] == 1087) {
			App->collision->EraseCollider(collider);
			firstUpdate = true;
		}
	}

	if (App->map->data.maplayers.end->data->data[gid] == 1087) {
		App->collision->EraseCollider(collider);
		firstUpdate = true;
	}

	if (App->map->data.maplayers.end->data->data[gid + 1] == 54) {
		if (App->scene->map == 1)
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map2.tmx");
			firstUpdate = true;
			App->collision->EraseCollider(collider);
			App->scene->map = 0;
		}
		
		else
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map1.tmx"); //Map1
			firstUpdate = true;
			App->collision->EraseCollider(collider);
			App->scene->map = 1;
		}
	}
	collider->SetPos(position.x , position.y);
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()),1, flip);
	
	
	return ret;
}

bool j1Player::PostUpdate()
{
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

void j1Player::Shot()
{
	App->particles->AddParticle(App->particles->fire_ball, position.x +25, position.y + 25, COLLIDER_ATTACK, NULL, { 5,0 });
}

void j1Player::Thunder()
{
	App->particles->AddParticle(App->particles->thunder, position.x + 60, position.y + 40, COLLIDER_ATTACK, NULL, { 0,0 });
}
void j1Player::Ice()
{
	App->particles->AddParticle(App->particles->iceR, position.x + 45, position.y + 25, COLLIDER_ATTACK, NULL, { 0,0 });
	App->particles->AddParticle(App->particles->iceL, position.x - 41, position.y + 25, COLLIDER_ATTACK, NULL, { 0,0 });
}

bool j1Player::Save(pugi::xml_node& save) const
{
	bool ret = false;
	if (save.child("pos") == NULL) {
		save.append_child("pos").append_attribute("x") = position.x;
		save.child("pos").append_attribute("y") = position.y;
	}
	else {
		save.child("pos").attribute("x") = position.x;
		save.child("pos").attribute("y") = position.y;
	}

	ret = true;
	return ret;
}

bool j1Player::Load(pugi::xml_node& save)
{
	bool ret = false;

	if (save.child("pos") != NULL) {
		position.x = save.child("pos").attribute("x").as_float();
		position.y = save.child("pos").attribute("y").as_float();
	}
	ret = true;
	return ret;	
}

void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_ENEMY) {
		App->collision->EraseCollider(collider);
		firstUpdate = true;
	}
}

