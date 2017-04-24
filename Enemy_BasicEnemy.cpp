#include "Application.h"
#include "Enemy_BasicEnemy.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"

#include "ModuleInput.h"

BasicEnemy::BasicEnemy(int x, int y) : Enemy(x, y)
{
	up.PushBack({ 116,36,22,21 });
	down.PushBack({ 76,36,22,21 });
	left.PushBack({ 155,35,22,21 });
	right.PushBack({ 74,75,22,21 });
	right_up.PushBack({ 157,73,22,21 });
	right_down.PushBack({ 116,105,22,21 });
	left_up.PushBack({ 156,173,22,21 });
	left_down.PushBack({ 74,107,22,21 });

	collider = App->collision->AddCollider({ 0, 0, 26, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASIC, (Module*)App->enemies);
	collider->life_units = 1;

	original_pos.x = x;
	original_pos.y = y;

	path.PushBack({ -0.3f, +2.469f }, 66);
	path.PushBack({ 0.0f, 0.0f }, 68);
	path.PushBack({ -0.05f, -1.63f }, 100);
	path.loop = false;
}

void BasicEnemy::Move()
{
	if (position.x + 22 < App->player->position.x) {

		if (position.y > App->player->position.y + 28) {
			animation = &right_up;
		}

		else if (position.y + 21 < App->player->position.y) {
			animation = &right_down;
		}

		else {
			animation = &right;
		}
	}
	else if (position.x > App->player->position.x + 28) {

		if (position.y > App->player->position.y + 28) {
			animation = &left_up;
		}

		else if (position.y + 21 < App->player->position.y) {
			animation = &left_down;
		}

		else {
			animation = &left;
		}
	}
	else if (position.y - 21 > App->player->position.y) {
		animation = &up;
	}
	else {
		animation = &down;
	}
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		position = original_pos + path.GetCurrentPosition();
	}
	original_pos.y -= 1;
	position = original_pos + path.GetCurrentPosition();

}
