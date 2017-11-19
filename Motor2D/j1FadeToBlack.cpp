#include <math.h>
#include "p2Log.h"

#include"j1Window.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "Brofiler\Brofiler.h"


j1FadeToBlack::j1FadeToBlack()
{
	
}

j1FadeToBlack::~j1FadeToBlack()
{

}

bool j1FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
	unsigned int width = 0, size = 0, height = 0, scale = 0;

	App->win->GetWindowSize(width, height);
	scale = App->win->GetScale();

	screen = { 0, 0,  static_cast<int>(width * size),  static_cast<int>(height * size) };
}


bool j1FadeToBlack::Update(float dt)
{
	BROFILER_CATEGORY("j1FadeToBlackUpdate", Profiler::Color::Black);
	if (current_step == fade_step::none)
		return true;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
	case fade_step::fade_to_black:
	{
		if (now >= total_time)
		{
			//off->CleanUp();
			//on->Start();
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = fade_step::fade_from_black;
		}
	} break;

	case fade_step::fade_from_black:
	{
		normalized = 1.0f - normalized;

		if (now >= total_time)
			current_step = fade_step::none;

	} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

bool j1FadeToBlack::FadeToBlack(/*j1Module* module_off, j1Module* module_on,*/ float time)
{
	bool ret = false;
	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		//on = module_on;
		//off = module_off;
		ret = true;
	}
	return ret;
}

bool j1FadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}