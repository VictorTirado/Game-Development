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
	GUI* music_up = NULL;
	GUI* music_down = NULL;
	GUI* slider_music = NULL;
	GUI* fx_up = NULL;
	GUI* fx_down = NULL;
	GUI* slider_fx = NULL;
	GUI* label = NULL;
	GUI* text_music = NULL;
	GUI* text_settings = NULL;
	GUI* text_fx = NULL;
	GUI* return_intro = NULL;
	GUI* background = NULL;

	bool first_update = true;
	int musicVolume = 64;
	bool close = false;
};

#endif // __j1SETTINGS_H__