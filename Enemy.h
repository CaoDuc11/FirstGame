#ifndef ENEMY_H_
#define ENEMY_H_

#include"GameBase.h"

#define ENEMY_MAX_HEIGHT 250
#define ENEMY_MIN_HEIGHT 400

#define ENEMY_POSITION_RANGE 1000

using namespace std;
class Enemy
{
public:
	Enemy(int _type = 0);

	~Enemy();

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

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

	SDL_Texture* EnemyTexture;
};

#endif 

