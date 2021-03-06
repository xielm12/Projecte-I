#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleLevel2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include"ModulePlayer.h"
#include"ModulePlayer2.h"
#include "ModuleWelcome.h"
#include "ModuleAudio.h"
#include "ModuleEnemySpaceship.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleEnemies_Ground.h"
#include "ModuleLevel1(assets).h"
#include "ModuleHallOfAces.h"
#include "ModuleParticles.h"


ModuleLevel1::ModuleLevel1()
{
	ground = {0, 0, 352, 3705};

}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("assets/textures/TileMap-LvL1.png");


	App->level_1_assets->Enable();

	App->stop_music = true;
	App->render->camera.x = -64;
	App->render->camera.y = 0;

//	path.PushBack({ 0,0.5f }, 5000);

	App->audio->Play("assets/music/1-4.ogg");

	App->collision->debug = false;

	if (App->welcome->player1) {
		App->player->Enable();
	}
	if (App->welcome->player2) {
		App->player2->Enable();
	}

	speed = 1;

	top_pos = App->render->camera.y-10;
	bottom_pos = App->render->camera.y + App->render->camera.h;

	top = App->collision->AddCollider({ 0, top_pos , 352 ,10 }, COLLIDER_WALL_UP);
	bottom = App->collision->AddCollider({ 0, bottom_pos , 352 ,10 }, COLLIDER_WALL_DOWN);


	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 126, -100);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 181, -300);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 162, -100);


	//	App->enemies_ground->AddEnemy(ENEMY_TYPES::TURRET, 48, -337);

	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 140, -210);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 256, -400);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 200, -970);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 256, -1020);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 256, -1070);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 148, -1020);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 100, -1090);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 50, -1090);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 230, -1600);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 260, -1630);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 240, -1660);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 270, -1690);
	App->enemies->AddEnemy(ENEMY_TYPES::BASICENEMY, 230, -1710);

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_SHIP, 140, -520);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_SHIP, 130, -1120);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_SHIP, 140, -1800);

	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 150, -680);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 120, -850);
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSHIP, 120, -2000);

	App->enemies_ground->AddEnemy(ENEMY_TYPES::TURRET, 67, -1535);
	App->enemies_ground->AddEnemy(ENEMY_TYPES::TURRET, 131, -1563);

	App->enemies_ground->AddEnemy(ENEMY_TYPES::TURRET, 230, -1611);
	App->enemies_ground->AddEnemy(ENEMY_TYPES::TURRET, 294, -1643);


	return ret;
}

// Load assets
bool ModuleLevel1::CleanUp()
{


	if (App->player->player_points > hi_score) {
		hi_score = App->player->player_points;
	}

	else if (App->player2->player_points > hi_score) {
		hi_score = App->player2->player_points;
	}

	App->textures->Unload(graphics);

	App->player->Disable();
	App->player2->Disable();

	//top->to_delete = true;
	//bottom->to_delete = true;

	App->enemies->FreeEnemies();
	App->enemies_ground->FreeEnemies();


//	speed = 0;


	LOG("Unloading Level 1");

	return true;
}

// Update: draw background
update_status ModuleLevel1::Update()
{

	

	//Scroll

	if (move)
	{
		App->render->camera.y += speed;
		top_pos -= speed;
		bottom_pos -= speed;

		top->SetPos(0, top_pos);
		bottom->SetPos(0, bottom_pos);
	}
/*

	movement = path.GetCurrentPosition();

	App->render->camera.y = movement.y;

	top_pos = -movement.y;
	bottom_pos = -movement.y + App->render->camera.h;

	top->SetPos(0, top_pos);
	bottom->SetPos(0, bottom_pos);
	*/


	if (App->input->keyboard[SDL_SCANCODE_F1]) {
		App->fade->FadeToBlack(this, App->welcome, 2.0f);
		top->to_delete = true;
		bottom->to_delete = true;
	}

	if (App->render->camera.y > 3400) {
		speed = 0;
		App->player->speed = 0;
		App->player2->speed = 0;
		App->render->camera.y += 0;
		App->fade->FadeToBlack(this, App->HallOfAces, 2.0f);
		top->to_delete = true;
		bottom->to_delete = true;

	}

	if (App->input->keyboard[SDL_SCANCODE_F6])
	{
		App->fade->FadeToBlack(this, App->HallOfAces, 2.0f);
		top->to_delete = true;
		bottom->to_delete = true;
	}

	move = !move;

	// Draw everything --------------------------------------	

	App->render->Blit(graphics, 0, -3449, &ground);

	return UPDATE_CONTINUE;
} 