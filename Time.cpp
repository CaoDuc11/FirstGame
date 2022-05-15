#include "Time.h"
#include "GameBase.h"


Time :: Time()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
}
Time::~Time()
{

}

void Time::start()
{
    is_started = true;
    is_paused = false;
    start_tick = SDL_GetTicks();
}

void Time::stop()
{
    is_paused = false;
    is_started = false;
}

void Time::pause()
{
    if (is_paused == true && is_started == true)
    {
        is_paused = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}

void Time::unpause()
{
    if (is_paused == true)
    {
        is_paused = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}

int Time::getTicks()
{
    if (is_started == true)
    {
        if (is_paused == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool Time::Is_Started()
{
    return is_started;
}

bool Time::Is_Paused()
{
    return is_paused;
}