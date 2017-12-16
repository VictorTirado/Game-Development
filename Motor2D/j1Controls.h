#ifndef __j1CONTROLS_H__
#define __j1CONTROLS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Controls : public j1Module
{
public:

	j1Controls();

	// Destructor
	virtual ~j1Controls();

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

	void j1Controls::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex = NULL;

public:
	GUI* button_menu = NULL;
	GUI* text_A = NULL;
	GUI* letter_Q = NULL;
	GUI* letter_E = NULL;
	GUI* letter_R = NULL;
	GUI* letter_W = NULL;
	GUI* letter_A = NULL;
	GUI* letter_S = NULL;
	GUI* letter_D = NULL;
	GUI* text_E = NULL;
	GUI* text_R = NULL;
	GUI* background = NULL;

	bool first_update = true;
	bool close = false;
};

#endif // __j1CONTROLS_H__