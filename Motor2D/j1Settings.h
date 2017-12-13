#ifndef __j1SETTINGS_H__
#define __j1SETTINGS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Settings : public j1Module
{
public:

	j1Settings();

	// Destructor
	virtual ~j1Settings();

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

	void j1Settings::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex;
	
public:
	GUI* text_music;
	GUI* text_settings;
	GUI* text_fx;
	GUI* return_intro;
	GUI* background;

	bool first_update = true;
	bool close = false;
};

#endif // __j1SETTINGS_H__