#include "Character.h"

Character::Character() 
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;
	
	status = 0;
}
bool Character::OnGround()
{
	return posY == GROUND;
}
void Character::Move()
{
	if ( status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -JUMP_SPEED;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
	if( status == FALL && posY < GROUND)
	{
		posY += FALL_SPEED;
	}
}
int Character::GetPosX()
{
	return posX;
}
int Character::GetPosY()
{
	return posY;
}