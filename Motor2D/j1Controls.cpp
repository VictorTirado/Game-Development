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
#include "j1Intro.h"

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
		image_controls = App->gui->AddLabel(310, 45, { 366, 336, 363, 88 }, NULL, this);
		text_controls = App->gui->AddText(400, 70, "CONTROLS", { 0,0,0 }, App->font->default, NULL, this);
		letter_Q = App->gui->AddText(50, 200, "Q: Ice attack", { 0,0,0 }, App->font->default, NULL, this);
		letter_E = App->gui->AddText(50, 250, "E: Melee attack", { 0,0,0 }, App->font->default, NULL, this);
		letter_R = App->gui->AddText(50, 300, "R: Distance attack", { 0,0,0 }, App->font->default, NULL, this);
		letter_SPACE = App->gui->AddText(50, 350, "Space: Jump", { 0,0,0 }, App->font->default, NULL, this);
		letter_A = App->gui->AddText(50, 400, "A: Move left", { 0,0,0 }, App->font->default, NULL, this);
		letter_D = App->gui->AddText(50, 450, "D: Move right", { 0,0,0 }, App->font->default, NULL, this);
		letter_W = App->gui->AddText(50, 500, "W(if god mode): Fly  ", { 0,0,0 }, App->font->default, NULL, this);
		letter_S = App->gui->AddText(50, 550, "S(if god mode): Descend", { 0,0,0 }, App->font->default, NULL, this);

		debug_F1 = App->gui->AddText(600, 200, "F1: Return first level", { 0,0,0 }, App->font->default, NULL, this);
		debug_F2 = App->gui->AddText(600, 250, "F2: Start actual level", { 0,0,0 }, App->font->default, NULL, this);
		debug_F5 = App->gui->AddText(600, 300, "F5: Save", { 0,0,0 }, App->font->default, NULL, this);
		debug_F6 = App->gui->AddText(600, 350, "F6: Load", { 0,0,0 }, App->font->default, NULL, this);
		debug_F8 = App->gui->AddText(600, 400, "F8: Debug UI", { 0,0,0 }, App->font->default, NULL, this);
		debug_F9 = App->gui->AddText(600, 450, "F9: View colliders", { 0,0,0 }, App->font->default, NULL, this);
		debug_F10 = App->gui->AddText(600, 500, "F10: God mode", { 0,0,0 }, App->font->default, NULL, this);
		debug_F11 = App->gui->AddText(600, 550, "F11: Enable/ Disable FPS", { 0,0,0 }, App->font->default, NULL, this);

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
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
	if (g == return_intro)
	{
		App->intro->active = true;
		this->active = false;
		first_update = true;
		App->gui->destroyElement(button_menu);
		App->gui->destroyElement(image_controls);
		App->gui->destroyElement(text_controls);
		App->gui->destroyElement(letter_Q);
		App->gui->destroyElement(letter_E);
		App->gui->destroyElement(letter_R);
		App->gui->destroyElement(letter_A);
		App->gui->destroyElement(letter_SPACE);
		App->gui->destroyElement(letter_D);
		App->gui->destroyElement(letter_W);
		App->gui->destroyElement(letter_S);
		App->gui->destroyElement(debug_F1);
		App->gui->destroyElement(debug_F2);
		App->gui->destroyElement(debug_F5);
		App->gui->destroyElement(debug_F6);
		App->gui->destroyElement(debug_F8);
		App->gui->destroyElement(debug_F9);
		App->gui->destroyElement(debug_F10);
		App->gui->destroyElement(debug_F11);
		App->gui->destroyElement(background);
		App->gui->destroyElement(return_intro);
	}
}