#include "Character.h"
#include "GameBase.h"
Character::Character() 
{
	posX = 300;
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
void Character::HandleEvent(SDL_Event& e, Mix_Chunk* gJump)
{
	if (e.key.keysym.sym == SDLK_UP && OnGround())
	{
		Mix_PlayChannel(MIX_CHANNEL, gJump, 0);
		status = JUMP;
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