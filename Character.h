#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Header.h"


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

	int GetPosX();

	int GetPosY();
	
	int status;

private:
	int posX, posY;
	
};

#endif 
