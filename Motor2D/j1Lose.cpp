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
#include "Brofiler\Brofiler.h"

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
	BROFILER_CATEGORY("j1LosePreUpdate", Profiler::Color::LemonChiffon);
	return true;
}

// Called each loop iteration
bool j1Lose::Update(float dt)
{
	BROFILER_CATEGORY("j1LoseUpdate", Profiler::Color::LemonChiffon);
	char playerCoins[(((sizeof App->player->coins_achieved) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerCoins, "%d", App->player->coins_achieved);
	char playerScore[(((sizeof App->player->score) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerScore, "%d", App->player->score);

	if (first_update == true)
	{
		App->audio->PlayMusic("audio/music/IntroSong.ogg");
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
		App->gui->destroyElement(App->scene->maxMana_text);
		App->gui->destroyElement(App->scene->currentMana);
		App->gui->destroyElement(App->scene->slash);
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
	BROFILER_CATEGORY("j1LosePostUpdate", Profiler::Color::LemonChiffon);
	bool ret = true;

	

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
	
	if (g == return_exit2)
	{
		close = true;
	}

	if (g == return_intro2)
	{
		App->scene->first_update = true;
		this->active = false;
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
		App->gui->destroyElement(text_coins_score);
		App->gui->destroyElement(text_coins);

	}
}