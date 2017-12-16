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
#include "j1Controls.h"
#include "j1Fonts.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"

j1Controls::j1Controls() : j1Module()
{
	name.create("controls");
}

// Destructor
j1Controls::~j1Controls()
{}

// Called before render is available
bool j1Controls::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Controls::Start()
{


	return true;
}

// Called each loop iteration
bool j1Controls::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Controls::Update(float dt)
{
	

	if (first_update == true)
	{
		background = App->gui->AddLabel(0, 0, { 799, 23, 1024, 768 }, NULL, this);
		letter_Q = App->gui->AddLabel(310, 45, { 366, 336, 363, 88 }, NULL, this);
		letter_E = App->gui->AddText(400, 70, "Q: Ice attack", { 0,0,0 }, App->font->default, NULL, this);
		letter_R = App->gui->AddText(300, 150, "E: Melee attack:", { 0,0,0 }, App->font->default, NULL, this);
		letter_W = App->gui->AddText(550, 150, "R: Distance attack", { 0,0,0 }, App->font->default, NULL, this);
		letter_A = App->gui->AddText(300, 250, "Space: Jump", { 0,0,0 }, App->font->default, NULL, this);
		letter_S = App->gui->AddText(650, 250, "A: Move left", { 0,0,0 }, App->font->default, NULL, this);

		letter_D = App->gui->AddText(300, 250, "BOOKS ACHIEVED:", { 0,0,0 }, App->font->default, NULL, this);
		//return_exit2 = App->gui->AddButton(500, 650, { 0,4,182,56 }, "Exit", { 255,255,255 }, App->font->default, NULL, this);
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
bool j1Controls::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Controls::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Controls::GUIInteract(GUI* g)
{
	/*LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	if (g == )
	{
		close = true;
	}

	if (g == )
	{
		App->scene->first_update = true;
		LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
		this->active = false;
		App->scene->active = true;
		App->player->active = true;
		App->player->lifes = 3;
		App->player->mana2 = 100;
		first_update = true;
		

	}*/
}