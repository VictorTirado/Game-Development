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
#include "j1Intro.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1Settings.h"
#include "j1Credits.h"

j1Intro::j1Intro() : j1Module()
{
	name.create("intro");
}

// Destructor
j1Intro::~j1Intro()
{}

// Called before render is available
bool j1Intro::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Intro::Start()
{

	


	

	return true;
}

// Called each loop iteration
bool j1Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Intro::Update(float dt)
{
	if (first_update == true)
	{
		label1 = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
		label2 = App->gui->AddLabel(40, 30, { 52, 387, 150, 150 }, NULL, this);
		label3 = App->gui->AddLabel(310, 23, { 362, 336, 367, 89 }, NULL, this);
		label4 = App->gui->AddLabel(700, 400, { 408, 484, 201, 236 }, NULL, this);
		text_menu = App->gui->AddText(440, 45, "MENU", { 255,255,255 }, App->font->default, NULL, this);
		text_history = App->gui->AddText(50, 230, "       This is the", { 85,56,22 }, App->font->default, NULL, this);
		text_history2 = App->gui->AddText(50, 270, "  beginning of a", { 85,56,22 }, App->font->default, NULL, this);
		text_history3 = App->gui->AddText(50, 310, "great adventure", { 85,56,22 }, App->font->default, NULL, this);

		button_start = App->gui->AddButton(400, 150, { 0,4,182,56 }, "Play", { 255,255,255 }, App->font->default, NULL, this);
		button_continue = App->gui->AddButton(400, 220, { 0,0,182,56 }, "Continue", { 255,255,255 }, App->font->default, NULL, this);
		button_settings = App->gui->AddButton(400, 290, { 0,0,182,56 }, "Settings", { 255,255,255 }, App->font->default, NULL, this);
		button_credits = App->gui->AddButton(400, 360, { 0,0,182,56 }, "Credits", { 255,255,255 }, App->font->default, NULL, this);
		button_exit = App->gui->AddButton(400, 430, { 0,0,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);

		first_update = false;
	}
	bool ret = true;
	if (close == true)
	{
		ret = false;
	}

	return ret;
}

// Called each loop iteration
bool j1Intro::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Intro::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Intro::GUIInteract(GUI* g)
{

	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	if (g == button_start)
	{
		App->fade->FadeToBlack(2.0f);
		App->scene->active = true;
		App->player->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(label1);
		App->gui->destroyElement(label2);
		App->gui->destroyElement(label3);
		App->gui->destroyElement(label4);
		App->gui->destroyElement(text_menu);
		App->gui->destroyElement(text_history);
		App->gui->destroyElement(text_history2);
		App->gui->destroyElement(text_history3);
		App->gui->destroyElement(button_start);
		App->gui->destroyElement(button_continue);
		App->gui->destroyElement(button_settings);
		App->gui->destroyElement(button_credits);
		App->gui->destroyElement(button_exit);
	}
	if (g == button_continue)
	{
		App->fade->FadeToBlack(2.0f);
		App->scene->active = true;
		App->player->active = true;
		this->active = false;
		first_update = true;
		App->LoadGame();
		App->player->spawnEnemies = true;
		App->player->dead = true;
		App->gui->destroyElement(label1);
		App->gui->destroyElement(label2);
		App->gui->destroyElement(label3);
		App->gui->destroyElement(label4);
		App->gui->destroyElement(text_menu);
		App->gui->destroyElement(text_history);
		App->gui->destroyElement(text_history2);
		App->gui->destroyElement(text_history3);
		App->gui->destroyElement(button_start);
		App->gui->destroyElement(button_continue);
		App->gui->destroyElement(button_settings);
		App->gui->destroyElement(button_credits);
		App->gui->destroyElement(button_exit);
	}
	if (g == button_settings)
	{
		App->fade->FadeToBlack(2.0f);
		App->settings->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(label1);
		App->gui->destroyElement(label2);
		App->gui->destroyElement(label3);
		App->gui->destroyElement(label4);
		App->gui->destroyElement(text_menu);
		App->gui->destroyElement(text_history);
		App->gui->destroyElement(text_history2);
		App->gui->destroyElement(text_history3);
		App->gui->destroyElement(button_start);
		App->gui->destroyElement(button_continue);
		App->gui->destroyElement(button_settings);
		App->gui->destroyElement(button_credits);
		App->gui->destroyElement(button_exit);
	}
	if (g == button_credits)
	{
		App->fade->FadeToBlack(2.0f);
		App->credits->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(label1);
		App->gui->destroyElement(label2);
		App->gui->destroyElement(label3);
		App->gui->destroyElement(label4);
		App->gui->destroyElement(text_menu);
		App->gui->destroyElement(text_history);
		App->gui->destroyElement(text_history2);
		App->gui->destroyElement(text_history3);
		App->gui->destroyElement(button_start);
		App->gui->destroyElement(button_continue);
		App->gui->destroyElement(button_settings);
		App->gui->destroyElement(button_credits);
		App->gui->destroyElement(button_exit);
	}
	if (g == button_exit)
	{
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		close = true;
	}


}
