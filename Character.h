#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GameBase.h"


#define JUMP 1
#define FALL 2
#define RUN	0

class Character
{
public:
	static const int JUMP_SPEED = 20;
	static const int FALL_SPEED = 20;

	Character();

	bool OnGround();

	void Move();

	void HandleEvent(SDL_Event& e, Mix_Chunk* gJump);

	int GetPosX();

	int GetPosY();
	
	

private:
	int posX, posY;
	int status;
	
};

#endif 
