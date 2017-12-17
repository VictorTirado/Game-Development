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
#include "j1Pause.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1Intro.h"
#include "Brofiler\Brofiler.h"

j1Pause::j1Pause() : j1Module()
{
	name.create("pause");
}

// Destructor
j1Pause::~j1Pause()
{}

// Called before render is available
bool j1Pause::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Pause::Start()
{


	return true;
}

// Called each loop iteration
bool j1Pause::PreUpdate()
{
	BROFILER_CATEGORY("j1PausePreUpdate", Profiler::Color::Tan);
	return true;
}

// Called each loop iteration
bool j1Pause::Update(float dt)
{
	BROFILER_CATEGORY("j1PauseUpdate", Profiler::Color::Tan);
	if (first_update == true) {
		bg = App->gui->AddLabel(365, 178, { 71, 577, 262, 282 }, NULL, this);
		button_load = App->gui->AddButton(400, 200, { 0,4,182,56 }, "Load", { 255,255,255 }, App->font->default, NULL, this);
		button_save = App->gui->AddButton(400, 260, { 0,4,182,56 }, "Save", { 255,255,255 }, App->font->default, NULL, this);
		button_continue = App->gui->AddButton(400, 320, { 0,4,182,56 }, "Continue", { 255,255,255 }, App->font->default, NULL, this);
		button_exit = App->gui->AddButton(400, 380, { 0,4,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
		
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
bool j1Pause::PostUpdate()
{
	BROFILER_CATEGORY("j1PausePostUpdate", Profiler::Color::Tan);
	bool ret = true;

	

	return ret;
}

// Called before quitting
bool j1Pause::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Pause::GUIInteract(GUI* g)
{
	if (g == button_save)
	{
		App->SaveGame();
	}
	if (g == button_load)
	{
		App->LoadGame();
	}
	if (g == button_continue)
	{
		this->active = false;
		App->gui->destroyElement(bg);
		App->gui->destroyElement(button_load);
		App->gui->destroyElement(button_save);
		App->gui->destroyElement(button_continue);
		App->gui->destroyElement(button_exit);
		first_update = true;
	}
	if (g == button_exit)
	{

		close = true;
	}
}