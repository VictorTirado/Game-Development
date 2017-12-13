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

	background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
	text_lose = App->gui->AddText(400, 70, "YOU LOSE", { 255,255,255 }, App->font->default, NULL, this);
	text_highscore2  = App->gui->AddText(300, 150, "HIGHSCORE:", { 255,255,255 }, App->font->default, NULL, this);
	text_points = App->gui->AddText(550, 150, "", { 255,255,255 }, App->font->default, NULL, this);
	//App->gui->AddLabel(40, 30, { 834, 868, 937, 576 }, NULL, this);
	return_intro2 = App->gui->AddButton(700, 650, { 0,4,182,56 }, "Play again", { 255,255,255 }, App->font->default, NULL, this);
	return_exit2 = App->gui->AddButton(500, 650, { 0,4,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
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

	}

	if (g == return_intro2)
	{
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		close = true;
	}
}