#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
class GUI;

class j1Scene : public j1Module
{
public:
	bool dragonSpawn = false;

	j1Scene();

	// Destructor
	virtual ~j1Scene();

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

	void j1Scene::GUIInteract(GUI* g);


	GUI* fire = NULL;
	GUI* thunder = NULL;
	GUI* ice = NULL;
	GUI* health = NULL;
	GUI* coins = NULL;
	GUI* mana_emptyBar = NULL;
	GUI* mana_Bar = NULL;
	GUI* books = NULL;
	GUI* multiplicator = NULL;
	GUI* score_text = NULL;
	GUI* score_num = NULL;
	GUI* total_time = NULL;
	GUI* sand_clock = NULL;

	int map = 0;
	int buttonClicked = 0;
	bool first_update = true;
private:
	//int map=0;
};

#endif // __j1SCENE_H__