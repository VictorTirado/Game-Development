#ifndef __j1WIN_H__
#define __j1WIN_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Win : public j1Module
{
public:

	j1Win();

	// Destructor
	virtual ~j1Win();

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

	void j1Win::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex = NULL;

public:
	GUI* text_win = NULL;
	GUI* text_highscore = NULL;
	GUI* text_points = NULL;
	GUI* return_intro = NULL;
	GUI* return_exit = NULL;
	GUI* background = NULL;

	bool first_update = true;
	bool close = false;
};

#endif // __j1WIN_H__