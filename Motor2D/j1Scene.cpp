#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "j1Enemies.h"
#include "Brofiler\Brofiler.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
		App->map->Load("Map1.tmx"); //Map1
		map = 1;
		//App->audio->PlayMusic("audio/music/Song.ogg");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("j1ScenePreUpdate", Profiler::Color::SaddleBrown);
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("j1SceneUpdate", Profiler::Color::SaddleBrown);
	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y -= 50;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y += 50;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x -= 50;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x += 50;
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		App->cap = !App->cap;
	}
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && App->fade->IsFading() == false) {
		if (map == 0)
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map1.tmx"); //Map1
			App->player->firstUpdate = true;
			map = 1;
			App->player->collider->to_delete = true;
		}
		else
		{
			map = 0;
			App->player->firstUpdate = true;
			App->player->collider->to_delete = true;
			
		}
		
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && App->fade->IsFading() == false) {
		App->player->firstUpdate = true;
		App->player->collider->to_delete = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {

		App->player->collider->to_delete = true;
	}
	
	App->map->Draw();


	int mousex;
	int mousey;
	App->input->GetMousePosition(mousex, mousey);
	/*p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d MousePosition:%dx%d Mana:%d Lifes:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					mousex, mousey, App->player->mana2,
					App->player->lifes);*/
	
	//App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("j1ScenePostUpdate", Profiler::Color::SaddleBrown);
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
