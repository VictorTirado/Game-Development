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
#include "j1Win.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"

j1Win::j1Win() : j1Module()
{
	name.create("Win");
}

// Destructor
j1Win::~j1Win()
{}

// Called before render is available
bool j1Win::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Win::Start()
{

	
	return true;
}

// Called each loop iteration
bool j1Win::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Win::Update(float dt)
{
	char playerCoins[(((sizeof App->player->coins_achieved) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerCoins, "%d", App->player->coins_achieved);
	char playerScore[(((sizeof App->player->score) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerScore, "%d", App->player->score);
	if (first_update == true)
	{
		App->gui->destroyElement(App->scene->fire);
		App->gui->destroyElement(App->scene->thunder);
		App->gui->destroyElement(App->scene->ice);
		App->gui->destroyElement(App->scene->health);
		App->gui->destroyElement(App->scene->coins);
		App->gui->destroyElement(App->scene->mana_emptyBar);
		App->gui->destroyElement(App->scene->mana_Bar);
		App->gui->destroyElement(App->scene->books);
		App->gui->destroyElement(App->scene->multiplicator);
		App->gui->destroyElement(App->scene->score_text);
		App->gui->destroyElement(App->scene->score_num);
		App->gui->destroyElement(App->scene->total_time);
		App->gui->destroyElement(App->scene->sand_clock);
		background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
		label = App->gui->AddLabel(310, 45, { 362, 336, 367, 89 }, NULL, this);
		text_win = App->gui->AddText(400, 70, "YOU WIN!", { 0,0,0 }, App->font->default, NULL, this);
		text_highscore = App->gui->AddText(300, 150, "HIGHSCORE:", { 0,0,0 }, App->font->default, NULL, this);
		text_coins_score = App->gui->AddText(300, 250, "BOOKS ACHIEVED:", { 0,0,0 }, App->font->default, NULL, this);
		text_points = App->gui->AddText(550, 150, playerScore, { 0,0,0 }, App->font->default, NULL, this);
		text_coins = App->gui->AddText(650, 250, playerCoins, { 0,0,0 }, App->font->default, NULL, this);
		return_intro = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Play again", { 255,255,255 }, App->font->default, NULL, this);
		return_exit = App->gui->AddButton(500, 650, { 0,4,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
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
bool j1Win::PostUpdate()
{
	bool ret = true;

	/*if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

	return ret;
}

// Called before quitting
bool j1Win::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Win::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");

	if (g == return_exit)
	{
		close = true;
	}
	if (g == return_intro)
	{
		App->scene->first_update = true;
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		this->active = false;
		App->scene->active = true;
		App->player->active = true;
		App->player->lifes = 3;
		App->player->mana2 = 100;
		first_update = true;
		App->gui->destroyElement(background);
		App->gui->destroyElement(label);
		App->gui->destroyElement(text_coins_score);
		App->gui->destroyElement(text_win);
		App->gui->destroyElement(text_coins);
		App->gui->destroyElement(text_highscore);
		App->gui->destroyElement(text_points);
		App->gui->destroyElement(return_intro);
		App->gui->destroyElement(return_exit);
	}
}
