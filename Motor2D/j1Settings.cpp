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
#include "j1Intro.h"
#include "Brofiler\Brofiler.h"

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
	
	return true;
}

// Called each loop iteration
bool j1Settings::PreUpdate()
{
	BROFILER_CATEGORY("j1SettingsPreUpdate", Profiler::Color::PapayaWhip);
	return true;
}

// Called each loop iteration
bool j1Settings::Update(float dt)
{
	BROFILER_CATEGORY("j1SettingsUpdate", Profiler::Color::PapayaWhip);
	if (first_update == true)
	{
		
		background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
		label = App->gui->AddLabel(300, 45, { 362, 336, 367, 89 }, NULL, this);
		music_up = App->gui->AddButton(550, 270, { 0,4,182,56 },"             +", { 255,255,255 }, App->font->default, NULL, this);
		music_down = App->gui->AddButton(450, 270, { 0,4,182,56 },"-             ", { 255,255,255 }, App->font->default, NULL, this);
		slider_music = App->gui->AddLabel(500, 270, { 0,65,182,56 }, NULL, this);
		fx_up = App->gui->AddButton(550, 370, { 0,4,182,56 }, "             +", { 255,255,255 }, App->font->default, NULL, this);
		fx_down = App->gui->AddButton(450, 370, { 0,4,182,56 }, "-             ", { 255,255,255 }, App->font->default, NULL, this);
		slider_fx  = App->gui->AddLabel(500, 370, { 0,65,182,56 }, NULL, this);

		text_settings = App->gui->AddText(400, 70, "SETTINGS", { 255,255,255 }, App->font->default, NULL, this);
		text_music = App->gui->AddText(250, 370, "Fx volume:", { 255,255,255 }, App->font->default, NULL, this);
		text_fx = App->gui->AddText(250, 270, "Music volume:", { 255,255,255 }, App->font->default, NULL, this);
		return_intro = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Return", { 255,255,255 }, App->font->default, NULL, this);
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
bool j1Settings::PostUpdate()
{
	BROFILER_CATEGORY("j1SettingsPostUpdate", Profiler::Color::PapayaWhip);
	bool ret = true;

	

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

	
	if (g == return_intro)
	{
		
		App->fade->FadeToBlack(2.0f);
		App->intro->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(background);
		App->gui->destroyElement(music_down);
		App->gui->destroyElement(music_up);
		App->gui->destroyElement(slider_music);
		App->gui->destroyElement(fx_down);
		App->gui->destroyElement(fx_up);
		App->gui->destroyElement(slider_fx);
		App->gui->destroyElement(label);
		App->gui->destroyElement(text_settings);
		App->gui->destroyElement(text_music);
		App->gui->destroyElement(text_fx);
		App->gui->destroyElement(return_intro);
	}
	if (g == music_up)
	{
		if (App->audio->active == true) {
			musicVolume += 8;
			Mix_VolumeMusic(musicVolume);
		}
	}
	if (g == music_down)
	{
		if (musicVolume > 0) {
			musicVolume -= 8;
		}
		Mix_VolumeMusic(musicVolume);
	}

	if (g == fx_up)
	{
		if (App->audio->active == true) {
			fxVolume += 8;
			Mix_VolumeChunk(Mix_GetChunk(1), fxVolume);
		}
	}
	if (g == fx_down)
	{
		if (fxVolume > 0) {
			fxVolume -= 8;
		}
		Mix_VolumeChunk(Mix_GetChunk(1) , fxVolume);
	}
}
