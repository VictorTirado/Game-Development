#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Lose.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"

j1Lose::j1Lose() : j1Module()
{
	name.create("Lose");
}

// Destructor
j1Lose::~j1Lose()
{}

// Called before render is available
bool j1Lose::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Lose::Start()
{

	
	return true;
}

// Called each loop iteration
bool j1Lose::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Lose::Update(float dt)
{
	char playerCoins[(((sizeof App->player->coins_achieved) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerCoins, "%d", App->player->coins_achieved);
	char playerScore[(((sizeof App->player->score) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerScore, "%d", App->player->score);

	if (first_update == true)
	{
	
		background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
		label = App->gui->AddLabel(310, 45, { 366, 336, 363, 88 }, NULL, this);
		text_lose = App->gui->AddText(400, 70, "YOU LOSE", { 0,0,0 }, App->font->default, NULL, this);
		text_highscore2 = App->gui->AddText(300, 150, "HIGHSCORE:", { 0,0,0 }, App->font->default, NULL, this);
		text_points = App->gui->AddText(550, 150, playerScore, { 0,0,0 }, App->font->default, NULL, this);
		text_coins_score = App->gui->AddText(300, 250, "BOOKS ACHIEVED:", { 0,0,0 }, App->font->default, NULL, this);
		text_coins = App->gui->AddText(650, 250, playerCoins, { 0,0,0 }, App->font->default, NULL, this);

		return_intro2 = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Play again", { 255,255,255 }, App->font->default, NULL, this);
		return_exit2 = App->gui->AddButton(500, 650, { 0,4,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
		first_update = false;
	}
	
	bool ret = true;
	if (close == true)
	{
		ret = false;
	}
	// Gui ---

	return ret;
}

// Called each loop iteration
bool j1Lose::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Lose::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Lose::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	if (g == return_exit2)
	{
		close = true;
	}

	if (g == return_intro2)
	{
		App->scene->first_update = true;
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		this->active = false;
		if (App->scene->map == 0)
		{
			App->scene->dragonSpawn = false;
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map1.tmx"); //Map1
			App->player->firstUpdate = true;
			App->scene->map = 1;
			App->player->collider->to_delete = true;
			App->player->spawnEnemies = true;
			App->player->dead = true;
		}
		else
		{
			App->scene->map = 0;
			App->player->firstUpdate = true;
			App->player->collider->to_delete = true;
			App->player->spawnEnemies = true;
			App->player->dead = true;
		}
		App->scene->active = true;
		App->player->active = true;
		App->player->lifes = 3;
		App->player->mana2 = 100;
		first_update = true;
		App->gui->destroyElement(background);
		App->gui->destroyElement(label);
		App->gui->destroyElement(text_lose);
		App->gui->destroyElement(text_highscore2);
		App->gui->destroyElement(text_points);
		App->gui->destroyElement(return_intro2);
		App->gui->destroyElement(return_exit2);
	}
}