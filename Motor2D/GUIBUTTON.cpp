#include "j1App.h"
#include "GUIBUTTON.h"
#include "SDL\include\SDL_timer.h"
#include "p2Log.h"
#include "j1GUI.h"

GUI_Button::GUI_Button(int x, int y, SDL_Rect anim) : GUI(x, y)
{
	idle.PushBack(anim);
	
	ButtonClicked.PushBack({ 0,65,182,56 });
	Mouse_on_Button.PushBack({ 402,232,182,56 });

	animation = &idle;
}

void GUI_Button::Interact(int state) {
	if (state == 1) {
		animation = &Mouse_on_Button;
	}
	else if (state == 2) {
		animation = &ButtonClicked;
	}
	else {
		animation = &idle;
	}
}
