#ifndef __BASICENEMY_H__
#define __BASICENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;
	int shot_type = 0;

public:
	fPoint position;
	bool hittable = true;
	fPoint relative_position;
public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* c1, Collider* c2);

};

#endif // __ENEMY_H__