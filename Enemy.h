#ifndef ENEMY_H_
#define ENEMY_H_

#include"GameBase.h"

#define ENEMY_MAX_HEIGHT 280
#define ENEMY_MIN_HEIGHT 400

#define ENEMY_POSITION_RANGE 650

using namespace std;
class Enemy
{
public:
	Enemy(int _type = 0);

	~Enemy();

	void Move(const int& acceleration);

	int GetType();

	int GetSpeed(const int& acceleration);

	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int eWidth, eHeight;

	int type;
};

#endif 

