
#include"GameBase.h"
#include"Enemy.h"
#include"Character.h"

using namespace std;

int main (int argc, char* argv[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    
    SDL_Texture* Background =loadTexture("Background.png", renderer);
    SDL_Rect BackgroundRect;
    SDL_QueryTexture(Background, NULL, NULL, &BackgroundRect.w, &BackgroundRect.h);
    BackgroundRect.x = 0;
    BackgroundRect.y = 0;
    BackgroundRect.w = 2051;
    BackgroundRect.h = 720;
  
    
    SDL_Texture* Character = loadTexture("DinoRed.png", renderer);
    SDL_Rect DinoRect;
    SDL_Rect RedRect;
    RedRect.x = 0;
    RedRect.y = 0;
    RedRect.w = 104;
    RedRect.h = 104;
    
    DinoRect.x = 0;
    DinoRect.y = 0;
    DinoRect.w = 57;
    DinoRect.h = 57;
    while(1)
    {
        SDL_RenderClear(renderer);
        if (DinoRect.x < 285) {
            DinoRect.x += 57;
            SDL_Delay(100);
        } 
        else DinoRect.x = 0;
        BackgroundRect.x += -50;
        SDL_RenderCopy(renderer, Background, NULL, &BackgroundRect);


        SDL_RenderCopy(renderer, Character, &DinoRect, &RedRect);
        SDL_RenderPresent(renderer);
    }
    
    
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}