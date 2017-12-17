#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "GUI.h"
#include "GUILABEL.h"
#include "GUITEXT.h"
#include "GUIBUTTON.h"
#include "j1Scene.h"
#include "Brofiler\Brofiler.h"
#include "j1Audio.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	BROFILER_CATEGORY("j1GuiPreUpdate", Profiler::Color::BlanchedAlmond);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			GUI_Elements[i]->Interact(queue[i].state);
		}
	}

	return true;
}

bool j1Gui::Update(float dt)
{
	BROFILER_CATEGORY("j1GuiUpdate", Profiler::Color::BlanchedAlmond);
	App->input->GetMousePosition(mousePosition.x, mousePosition.y);

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			GUI_Elements[i]->Draw(queue[i].texture);
		}
	}

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			if (queue[i].father != NULL) {
				queue[i].x = queue[i].father->position.x + queue[i].xInFather;
				queue[i].y = queue[i].father->position.y + queue[i].yInFather;
				GUI_Elements[i]->position.x = queue[i].father->position.x + queue[i].xInFather;
				GUI_Elements[i]->position.y = queue[i].father->position.y + queue[i].yInFather;
			}
		}
	}

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			if (mousePosition.x>queue[i].x && mousePosition.x<queue[i].x + queue[i].w && mousePosition.y>queue[i].y && mousePosition.y<queue[i].y + queue[i].h) {
				LOG("MouseIsOnButton %i", queue[i].num);
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					queue[i].state = 2;
					queue[i].prevState = 2;
				}
				else {
					queue[i].state = 1;
				}
			}
			else {
				queue[i].state = 0;
			}
		}
	}

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != nullptr) {
			if (queue[i].state == 1 && queue[i].prevState == 2) {
				App->audio->PlayFx(1);
				queue[i].callback->GUIInteract(GUI_Elements[i]);
				queue[i].state = 0;
				queue[i].prevState = 0;
			}
		}
	}

	debugDraw();

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	BROFILER_CATEGORY("j1GuiPostUpdate", Profiler::Color::BlanchedAlmond);
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (GUI_Elements[i] != nullptr)
		{
			delete GUI_Elements[i];
			GUI_Elements[i] = nullptr;
		}
		queue[i].type = NON_TYPE;
	}

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

GUI* j1Gui::CreateGUI(const GUIinfo& info) {
	uint i = 0;
	for (; GUI_Elements[i] != nullptr && i < MAX_UI_ELEMENTS; ++i);

	if (i != MAX_UI_ELEMENTS)
	{
		switch (info.type)
		{
		case GUI_Types::BUTTON:
			return GUI_Elements[i] = new GUI_Button(info.x, info.y, info.anim);
			break;
		case GUI_Types::LABEL:
			return GUI_Elements[i] = new GUI_Label(info.x, info.y, info.anim);
			break;
		case GUI_Types::TEXT:
			return GUI_Elements[i] = new GUI_Text(info.x, info.y, info.anim);
			break;
		case GUI_Types::CHECKBOX:
			
			break;
		}
	}
}

GUI* j1Gui::AddLabel(int x, int y, SDL_Rect anim, GUI* father, j1Module* callback) {
	GUI* ret = nullptr;

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NON_TYPE)
		{
			queue[i].type = LABEL;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
				queue[i].xInFather = x;
				queue[i].yInFather = y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
				queue[i].xInFather = 0;
				queue[i].yInFather = 0;
			}
			queue[i].w = anim.w;
			queue[i].h = anim.h;
			queue[i].num = numLabels;
			queue[i].anim = anim;
			queue[i].texture = atlas;
			queue[i].father = father;
			queue[i].callback = callback;
			queue[i].state = 0;
			queue[i].prevState = 0;
			numLabels++;
			ret = CreateGUI(queue[i]);
			break;
		}
	}
	return ret;
}

GUI* j1Gui::AddText(int x, int y, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father, j1Module* callback) {
	GUI* ret = nullptr;
	int w = 0, h = 0;
	App->font->CalcSize(text.GetString(), w, h, App->font->default);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NON_TYPE)
		{
			queue[i].type = TEXT;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
				queue[i].xInFather = x;
				queue[i].yInFather = y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
				queue[i].xInFather = 0;
				queue[i].yInFather = 0;
			}
			queue[i].w = w;
			queue[i].h = h;
			queue[i].num = numTexts;
			queue[i].anim = { 0,0,w,h };
			queue[i].texture = App->font->Print(text.GetString(), color, font);
			queue[i].father = father;
			queue[i].callback = callback;
			queue[i].callback = callback;			numTexts++;
			queue[i].state = 0;
			queue[i].prevState = 0;
			numTexts++;
			ret = CreateGUI(queue[i]);
			break;
		}
	}

	return ret;
}
GUI* j1Gui::AddButton(int x, int y, SDL_Rect anim, p2SString text, SDL_Color color, _TTF_Font* font, GUI* father, j1Module* callback) {
	GUI* ret = nullptr;
	int text_w = 0, text_h = 0;
	App->font->CalcSize(text.GetString(), text_w, text_h, App->font->default);
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].type == GUI_Types::NON_TYPE)
		{
			queue[i].type = BUTTON;
			if (father != NULL) {
				queue[i].x = father->position.x + x;
				queue[i].y = father->position.y + y;
				queue[i].xInFather = x;
				queue[i].yInFather = y;
			}
			else {
				queue[i].x = x;
				queue[i].y = y;
				queue[i].xInFather = 0;
				queue[i].yInFather = 0;
			}
			queue[i].w = anim.w;
			queue[i].h = anim.h;
			queue[i].num = numButtons;
			queue[i].anim = anim;
			queue[i].texture = atlas;
			queue[i].state = 0;
			queue[i].father = father;
			queue[i].callback = callback;
			queue[i].state = 0;
			queue[i].prevState = 0;
			ret = CreateGUI(queue[i]);
			for (uint j = 0; j < numButtons; j++) {
				buttons[j] = i;
				break;
			}
			numButtons++;
			if (text != NULL) {
				App->gui->AddText((anim.w / 2) - (text_w / 2), (anim.h / 2) - (text_h / 2), text, color, font, GUI_Elements[i], callback);
			}
			break;
		}
	}
	return ret;
}
void j1Gui::destroyElement(GUI* element) {
	
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (queue[i].father == element)
		{
			if (queue[i].type == BUTTON) {
				numButtons--;
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == BUTTON && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			if (queue[i].type == LABEL) {
				numLabels--;
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == LABEL && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			if (queue[i].type == TEXT) {
				numTexts--;
				App->tex->UnLoad(queue[i].texture);
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == TEXT && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			delete GUI_Elements[i];
			GUI_Elements[i] = nullptr;
			queue[i].type = NON_TYPE;
		}
	}

	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i)
	{
		if (GUI_Elements[i] == element)
		{
			if (queue[i].type == BUTTON) {
				numButtons--;
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == BUTTON && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			if (queue[i].type == LABEL) {
				numLabels--;
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == LABEL && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			if (queue[i].type == TEXT) {
				numTexts--;
				App->tex->UnLoad(queue[i].texture);
				for (uint j = 0; j < MAX_UI_ELEMENTS; ++j) {
					if (queue[j].type == TEXT && queue[j].num>queue[i].num) {
						queue[j].num -= 1;
					}
				}
			}
			delete GUI_Elements[i];
			GUI_Elements[i] = nullptr;
			queue[i].type = NON_TYPE;
		}
	}
}

void j1Gui::moveElement(GUI* element, int x, int y) {
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] == element) {
			GUI_Elements[i]->position.x = x;
			GUI_Elements[i]->position.y = y;
			queue[i].x = x;
			queue[i].y = y;
		}
	}
}

void j1Gui::changeTexture(GUI* element, SDL_Rect anim) {
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] == element) {
			if (queue[i].type == LABEL) {
				AddLabel(queue[i].x,queue[i].y, anim, queue[i].father,queue[i].callback);
				destroyElement(GUI_Elements[i]);
			}
		}
	}
}

void j1Gui::debugDraw() {
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_UI_ELEMENTS; ++i) {
		if (GUI_Elements[i] != NULL) {
			App->render->DrawQuad({queue[i].x, queue[i].y, queue[i].w, queue[i].h }, 255, 0, 0, alpha, false, false);
		}
	}
}