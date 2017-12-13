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
#include "j1Credits.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1Intro.h"

j1Credits::j1Credits() : j1Module()
{
	name.create("credits");
}

// Destructor
j1Credits::~j1Credits()
{}

// Called before render is available
bool j1Credits::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Credits::Start()
{
	
	
	return true;
}

// Called each loop iteration
bool j1Credits::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Credits::Update(float dt)
{
	if (first_update == true) {
		background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);

		license = App->gui->AddLabel(40, 30, { 834, 868, 937, 576 }, NULL, this);
		return_intro = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Return", { 255,255,255 }, App->font->default, NULL, this);
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
bool j1Credits::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Credits::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Credits::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");


	if (g == return_intro)
	{
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		App->fade->FadeToBlack(2.0f);
		App->intro->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(background);
		App->gui->destroyElement(license);
		App->gui->destroyElement(return_intro);
	}
}
