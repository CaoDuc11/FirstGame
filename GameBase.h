#ifndef GAME_BASE_
#define GAME_BASE_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "Enemy.h"
#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4


#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 520
#define MAX_HEIGHT 300

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 5
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 10
#define ENEMY_SPEED 5
#define FLY_SPEED 8
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

using namespace std;
const  string WINDOW_TITLE = "FIGHT AND RUN";
const   int SCREEN_WIDTH = 1100;
const   int SCREEN_HEIGHT = 720;

void logSDLError(std::ostream& os, const std::string& msg, bool fatal);

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);


#endif 

