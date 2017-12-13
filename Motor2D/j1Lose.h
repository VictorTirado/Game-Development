#ifndef __j1LOSE_H__
#define __j1LOSE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Lose : public j1Module
{
public:

	j1Lose();

	// Destructor
	virtual ~j1Lose();

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

	void j1Lose::GUIInteract(GUI* g);

	int buttonClicked = 0;

private:
	SDL_Texture* debug_tex = NULL;

public:
	GUI* text_lose = NULL;
	GUI* text_highscore2 = NULL;
	GUI* text_points = NULL;
	GUI* return_intro2 = NULL;
	GUI* return_exit2 = NULL;
	GUI* background = NULL;


	bool close = false;
};

#endif // __j1WINLOSE_H__