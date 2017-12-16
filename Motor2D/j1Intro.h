#ifndef __j1INTRO_H__
#define __j1INTRO_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Intro : public j1Module
{
public:

	j1Intro();

	// Destructor
	virtual ~j1Intro();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void j1Intro::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex;
	GuiImage* banner;
	GuiText* text;
public:
	GUI* text_menu = NULL;
	GUI* text_history = NULL;
	GUI* text_history2 = NULL;
	GUI* text_history3 = NULL;
	GUI* button_start = NULL;
	GUI* button_continue = NULL;
	GUI* button_settings = NULL;
	GUI* button_controls = NULL;
	GUI* button_credits = NULL;
	GUI* button_exit = NULL;
	GUI* label1 = NULL;
	GUI* label2 = NULL;
	GUI* label3 = NULL;
	GUI* label4 = NULL;

	bool first_update = true;
	bool close = false;
};

#endif // __j1INTRO_H__