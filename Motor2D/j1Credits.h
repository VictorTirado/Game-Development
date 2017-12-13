#ifndef __j1CREDITS_H__
#define __j1CREDITS_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Credits : public j1Module
{
public:

	j1Credits();

	// Destructor
	virtual ~j1Credits();

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

	void j1Credits::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex;

public:
	GUI* text_music;
	GUI* text_settings;
	GUI* text_fx;
	GUI* return_intro;
	GUI* background;


	bool close = false;
};

#endif // __j1CREDITS_H__