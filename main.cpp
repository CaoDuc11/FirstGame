
#include"GameBase.h"
#include"Enemy.h"
#include"Character.h"

using namespace std;

int main (int argc, char* argv[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    Character character;

    srand(time(NULL));
    int time = 0;
    int score = 0;
    int acceleration = 0;
    int frame_Character = 0;
    int frame_Enemy = 0;

    SDL_Event e;
    Enemy enemy1(ON_GROUND_ENEMY);
    Enemy enemy2(ON_GROUND_ENEMY);
    Enemy enemy3(IN_AIR_ENEMY);

    initSDL(window, renderer);
    
    
    //Load Backgrornd
    SDL_Texture* Background =loadTexture("BackgroundUpdate.png", renderer);
    SDL_Rect BackgroundRect;
    BackgroundRect.x = 0;
    BackgroundRect.y = 0;
    BackgroundRect.w = 2051;
    BackgroundRect.h = 720;
    
    SDL_Rect BackgroundP2Rect;
    BackgroundP2Rect.y = 0;
    BackgroundP2Rect.w = 2051;
    BackgroundP2Rect.h = 720;

    //Load main character
    SDL_Texture* Character = loadTexture("DinoRed.png", renderer);
    SDL_Rect DinoRect;
    SDL_Rect RedRect;
    RedRect.x = 0;
    RedRect.y = GROUND;
    RedRect.w = 111;
    RedRect.h = 111;
    
    DinoRect.x = 0;
    DinoRect.y = 0;
    DinoRect.w = 57;
    DinoRect.h = 57;
    
    
    bool gamerun = 1, Quit = 0;
    while (!Quit) 
    {
            while(SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) {
                    Quit = true;
                    gamerun = false;
                    quitSDL(window, renderer);
                    break;
                }
                if (e.type == SDL_KEYUP && character.OnGround()) {
                    character.status = JUMP;
                }

             }
            //Animations of Dino
            SDL_RenderClear(renderer);
            if (DinoRect.x < 285) {
                DinoRect.x += 57;
            }
            else DinoRect.x = 0;

            RedRect.x = character.GetPosX();
            RedRect.y = character.GetPosY();
            character.Move();
            
            
            //Animations of Background
            BackgroundRect.x += -10;
            BackgroundP2Rect.x = BackgroundRect.x + BackgroundRect.w;
            if (BackgroundP2Rect.x <= 0) BackgroundRect.x = 0;

            SDL_RenderCopy(renderer, Background, NULL, &BackgroundRect);
            SDL_RenderCopy(renderer, Background, NULL, &BackgroundP2Rect);
            SDL_RenderCopy(renderer, Character, &DinoRect, &RedRect);
            SDL_RenderPresent(renderer);
            
            
        }
    
    
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}