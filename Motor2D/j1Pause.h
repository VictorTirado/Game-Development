#ifndef __j1PAUSE_H__
#define __j1PAUSE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Pause : public j1Module
{
public:
	bool dragonSpawn = false;

	j1Pause();

	// Destructor
	virtual ~j1Pause();

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

	void j1Pause::GUIInteract(GUI* g);


	GUI* button_save = NULL;
	GUI* button_load = NULL;
	GUI* button_continue = NULL;
	GUI* button_exit = NULL;
	GUI* bg = NULL;

	int buttonClicked = 0;
	bool first_update = true;
	bool close = false;
private:
	
};

#endif // __j1PAUSE_H__