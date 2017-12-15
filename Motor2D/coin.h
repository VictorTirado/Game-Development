#ifndef _COIN_H__ 
#define _COIN_H__

#include "j1Enemy.h"

class Book : public j1Enemy
{
private:
	Animation idle;

public:
	Book(int x, int y);
	void OnCollision(Collider* collider);

};
#
#endif