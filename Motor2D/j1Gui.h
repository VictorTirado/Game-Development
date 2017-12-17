#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "SDL_TTF\include\SDL_ttf.h"

#define CURSOR_WIDTH 2
#define MAX_UI_ELEMENTS 100


enum GUI_Types {
	NON_TYPE,
	BUTTON,
	LABEL,
	TEXT,
	CHECKBOX
};

enum GUI_INTERACTION {

};

class GUI;

struct GUIinfo {
	GUI_Types type = GUI_Types::NON_TYPE;
	int x, y, h, w, xInFather, yInFather;
	SDL_Rect anim;
	SDL_Texture* texture = NULL;
	int state;
	int prevState;
	int num;
	GUI* father = NULL;
	GUI* same = NULL;
	j1Module* callback = NULL;
};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
	// Gui creation functions
	GUI* AddLabel(int x, int y, SDL_Rect anim, GUI* father, j1Module* callback);
	GUI* AddText(int x, int y, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father, j1Module* callback);
	GUI* AddButton(int x, int y, SDL_Rect anim, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father, j1Module* callback);
	

	void destroyElement(GUI* element);

	void moveElement(GUI* element, int x, int y);

	void changeTexture(GUI* element, SDL_Rect anim);

	const SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas = NULL;
	p2SString atlas_file_name;
	GUIinfo queue[MAX_UI_ELEMENTS];
	int buttons[MAX_UI_ELEMENTS];
	GUI* GUI_Elements[MAX_UI_ELEMENTS];
	SDL_Texture* texture_text = NULL;
	iPoint mousePosition;
	int numButtons = 0;
	int numLabels = 0;
	int numTexts = 0;
	int buttonsIterator = 0;
	bool debug = false;

	GUI* CreateGUI(const GUIinfo& info);
	void debugDraw();
};

#endif // __j1GUI_H__