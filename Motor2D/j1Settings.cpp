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
#include "j1Settings.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"

j1Settings::j1Settings() : j1Module()
{
	name.create("settings");
}

// Destructor
j1Settings::~j1Settings()
{}

// Called before render is available
bool j1Settings::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Settings::Start()
{
	background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
	text_settings = App->gui->AddText(400, 70, "SETTINGS", { 255,255,255 }, App->font->default, NULL, this);
	text_music = App->gui->AddText(250, 270, "Fx volume:", { 255,255,255 }, App->font->default, NULL, this);
	text_fx = App->gui->AddText(250, 370, "Music volume:", { 255,255,255 }, App->font->default, NULL, this);
	return_intro = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Return", { 255,255,255 }, App->font->default, NULL, this);
	return true;
}

// Called each loop iteration
bool j1Settings::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Settings::Update(float dt)
{
	bool ret = true;
	if (close == true)
	{
		ret = false;
	}
	// Gui ---

	return ret;
}

// Called each loop iteration
bool j1Settings::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Settings::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Settings::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");

	
	if (g == return_intro)
	{
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		close = true;
	}
}
