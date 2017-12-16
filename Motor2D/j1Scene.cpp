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
#include "j1Gui.h"
#include "j1Fonts.h"
#include "j1Pause.h"

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
		App->enemies->AddEnemy(Books, 650, 450);
		App->map->Load("Map1.tmx"); //Map1
		map = 1;
		App->audio->PlayMusic("audio/music/Song.ogg");
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
	
	//playerCoins = static_cast<std::ostringstream*>(&(std::ostringstream() << App->player->coins_achieved))->str();

	char playerCoins[(((sizeof App->player->coins_achieved) * CHAR_BIT) + 2) / 3 + 2];
	 sprintf_s(playerCoins, "%d", App->player->coins_achieved);
	char playerScore[(((sizeof App->player->score) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerScore, "%d", App->player->score);
	char playerTime[(((sizeof App->player->time) * CHAR_BIT) + 2) / 3 + 2];
	sprintf_s(playerTime, "%.2f", App->player->time);

	int manaBar_max_length = 274;
	int manaBar_length = (manaBar_max_length*App->player->mana2) / 100;

	if (first_update == true) {
		mana_emptyBar = App->gui->AddLabel(80, 15, { 264, 1054, 274, 50 }, NULL, this);
		mana_Bar = App->gui->AddLabel(500, 40, { 264, 986, 274, 50 }, NULL, this);
		books = App->gui->AddLabel(520, 10, { 27, 197, 69, 74 }, NULL, this);
		multiplicator = App->gui->AddLabel(590, 32, { 108, 221, 30, 24 }, NULL, this);
		coins = App->gui->AddText(630, 25, playerCoins, { 255,255,255 }, App->font->default, NULL, this);
		score_text = App->gui->AddText(670, 25, "Score:", { 255,255,255 }, App->font->default, NULL, this);
		score_num = App->gui->AddText(760, 25, playerScore, { 255,255,255 }, App->font->default, NULL, this);
		sand_clock = App->gui->AddLabel(840, 20, { 201, 983, 41, 55 }, NULL, this);
		total_time = App->gui->AddText(890, 20, playerTime, { 255,255,255 }, App->font->default, NULL, this);
		if (App->player->lifes == 3) {
			health = App->gui->AddLabel(10, 10, { 596, 984, 67, 67 }, NULL, this);	
		}
		if (App->player->lifes == 2)
		{
			health = App->gui->AddLabel(10, 10, { 596, 1054, 67, 67 }, NULL, App->scene);
		}
		if (App->player->lifes == 1)
		{
			health = App->gui->AddLabel(10, 10, { 595, 1131, 67, 67 }, NULL, App->scene);
		}
		
		fire = App->gui->AddLabel(410, 10, { 621,35,46,45 }, NULL, App->scene);
		thunder = App->gui->AddLabel(360, 10, { 480, 99, 50, 50 }, NULL, App->scene);
		ice = App->gui->AddLabel(460, 10, { 676,36,46,45 }, NULL, App->scene);

		first_update = false;
	}

	App->gui->destroyElement(mana_Bar);
	App->gui->destroyElement(coins);
	App->gui->destroyElement(score_num);
	App->gui->destroyElement(total_time);
	mana_Bar = App->gui->AddLabel(80, 15, { 264, 986, manaBar_length, 50 }, NULL, this);
	coins = App->gui->AddText(630, 25, playerCoins, { 255,255,255 }, App->font->default, NULL, this);
	score_num = App->gui->AddText(760, 25, playerScore, { 255,255,255 }, App->font->default, NULL, this);
	total_time = App->gui->AddText(890, 30, playerTime, { 255,255,255 }, App->font->default, NULL, this);
	
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		App->LoadGame();
		App->player->spawnEnemies = true;
		App->player->dead = true;

	}
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
			dragonSpawn = false;
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Map1.tmx"); //Map1
			App->player->firstUpdate = true;
			map = 1;
			App->player->collider->to_delete = true;
			App->player->spawnEnemies = true;
			App->player->dead = true;
		}
		else
		{
			map = 0;
			App->player->firstUpdate = true;
			App->player->collider->to_delete = true;
			App->player->spawnEnemies = true;
			App->player->dead = true;
		}
		
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && App->fade->IsFading() == false) {
		App->player->firstUpdate = true;
		App->player->collider->to_delete = true;
		App->player->spawnEnemies = true;
		App->player->dead = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		App->player->GodMode = !App->player->GodMode;
	}

	if (App->player->mana2 < App->player->cost_fire && App->player->coins_achieved >= 1)
	{
		//App->gui->changeTexture(App->scene->fire, {413,153,50,50});
		App->gui->destroyElement(fire);
		fire = App->gui->AddLabel(410, 10, { 413,153,50,50 }, NULL, this);
	}
	else if (App->player->mana2 >= App->player->cost_fire && App->player->coins_achieved >= 1) {
		//App->gui->changeTexture(App->scene->fire, { 413, 99, 50, 50 });
		App->gui->destroyElement(fire);
		fire = App->gui->AddLabel(410, 10, { 413,99,50,50 }, NULL, this);
	}
	if (App->player->mana2 < App->player->cost_thunder)
	{
		//App->gui->changeTexture(App->scene->thunder, { 486,153,50,50 });
		App->gui->destroyElement(thunder);
		thunder = App->gui->AddLabel(360, 10, { 486,153,50,50 }, NULL, this);
	}
	else if (App->player->mana2 >= App->player->cost_thunder) {
		//App->gui->changeTexture(App->scene->thunder, { 480, 99, 50, 50 });
		App->gui->destroyElement(thunder);
		thunder = App->gui->AddLabel(360, 10, { 480,99,50,50 }, NULL, this);
	}

	if (App->player->mana2 < App->player->cost_ice && App->player->coins_achieved >= 1)
	{
		//App->gui->changeTexture(App->scene->ice, { 550,153,50,50 });
		App->gui->destroyElement(ice);
		ice = App->gui->AddLabel(460, 10, { 550,153,50,50 }, NULL, this);
	}
	else if (App->player->mana2 >= App->player->cost_ice && App->player->coins_achieved >= 1) {
		//App->gui->changeTexture(App->scene->ice, { 546, 97, 50, 50 });
		App->gui->destroyElement(ice);
		ice = App->gui->AddLabel(460, 10, { 546,97,50,50 }, NULL, this);
	}
	
	App->map->Draw();


	int mousex;
	int mousey;
	App->input->GetMousePosition(mousex, mousey);

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("j1ScenePostUpdate", Profiler::Color::SaddleBrown);
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		App->pause->active = true;
	}
		

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::GUIInteract(GUI* g)
{
	LOG("HIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
}
