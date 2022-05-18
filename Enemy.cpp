#include "Enemy.h"
#include "GameBase.h"
using namespace std;
Enemy::Enemy(int _type) 
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
    posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
    
    if (type == IN_AIR_ENEMY) posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT +1) + ENEMY_MIN_HEIGHT;

    else 
    {
        if (type == ON_GROUND_ENEMY)  posY = GROUND - 8;

        else  posY = GROUND + 10;
    }
}
Enemy::~Enemy()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = 0;
}
void Enemy :: Move(const int &acceleration)
{
	if (type == ON_GROUND_ENEMY )	posX += -(GROUND_SPEED + acceleration);

	else
    {
        if (type == SLIME_ENEMY)  posX += -(ENEMY_SPEED + acceleration);
        else posX += -(FLY_SPEED + acceleration);
    }
        
	if( posX + MAX_ENEMY_WIDTH < 0)
	{
		posX = rand() % (SCREEN_WIDTH + ENEMY_POSITION_RANGE) + SCREEN_WIDTH;
		if (type == IN_AIR_ENEMY)
		{
			posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT +1) + ENEMY_MIN_HEIGHT;
		}

	}
}
int  Enemy::GetPosX()
{
	return posX;
}

int Enemy::GetPosY()
{
	return posY;
}

int Enemy::GetWidth()
{
	return eWidth;
}

int Enemy::GetHeight()
{
	return eHeight;
}
int Enemy::GetType()
{
	if (type == IN_AIR_ENEMY)
	{
		return IN_AIR_ENEMY;
	}
	else
	{
		return ON_GROUND_ENEMY;
	}
}

int Enemy::GetSpeed(const int& acceleration)
{
	return ENEMY_SPEED + acceleration;
}
bool Enemy :: CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x + 22;
    int right_a = object1.x + object1.w - 22;
    int top_a = object1.y +12;
    int bottom_a = object1.y + object1.h - 12;
    int left_b;
    int right_b;
    int top_b;
    int bottom_b;

    if (type == ON_GROUND_ENEMY)
    {
        left_b = object2.x + 23;
        right_b = object2.x + object2.w - 23;
        top_b = object2.y + 10;
        bottom_b = object2.y + object2.h ;
    }
    if (type == IN_AIR_ENEMY)
    {
        left_b = object2.x + 12;
        right_b = object2.x + object2.w - 12;
        top_b = object2.y + 12 ;
        bottom_b = object2.y + object2.h -12;
    }
    else 
    {
        left_b = object2.x + 30;
        right_b = object2.x + object2.w - 30;
        top_b = object2.y + 15;
        bottom_b = object2.y + object2.h ;
    }
    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}
