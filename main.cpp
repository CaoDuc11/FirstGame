
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
    int acceleration = 10;
    int frame_Character = 0;
    int frame_Enemy = 0;

    SDL_Event e;
    Enemy enemy1(ON_GROUND_ENEMY);
    Enemy enemy2(ON_GROUND_ENEMY);
    Enemy enemy3(IN_AIR_ENEMY);

    initSDL(window, renderer);
    
    
    //Load Backgrornd
    SDL_Texture* Background =loadTexture("BackgroundUpdate.png", renderer);
    SDL_Rect BackgroundRect = { 0, 0 , 2051, 720};
    
    SDL_Rect BackgroundP2Rect;
    BackgroundP2Rect.y = 0;
    BackgroundP2Rect.w = 2051;
    BackgroundP2Rect.h = 720;

    //Load main character
    SDL_Texture* Character = loadTexture("DinoRed.png", renderer);
    SDL_Texture* RedCharacter = loadTexture("unnamed.png", renderer);
    SDL_Rect DinoRect= { 0, 0, 57, 57};
    SDL_Rect RedRect = { 300, GROUND , 100, 100};
    SDL_Rect JumpRect = { 300, GROUND, 75, 75 };

    //Load cactus
    SDL_Texture* cactus = loadTexture("cactus.png", renderer);
    SDL_Rect ene1 = { 0, GROUND, 90, 90 };
    SDL_Rect ene2 = { 0, GROUND + 30, 60, 60 };

    //Load bat
    SDL_Texture* bat = loadTexture("bat.png", renderer);
    SDL_Rect BatRect = { 0, 0, 43,30 };
    SDL_Rect ene3 = { 0, 0, 60, 50 };
    
    bool gamerun = 1, Quit = 0;
    while (!Quit) 
    {       
            UpdateGameTimeAndScore(time, acceleration, score);
            while(SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) {
                    Quit = true;
                    gamerun = false;
                    quitSDL(window, renderer);
                    break;
                }
                if (e.key.keysym.sym == SDLK_SPACE && character.OnGround()) {
                    character.status = JUMP;
                }

             }
            SDL_RenderClear(renderer);
            //Animations of Dino
            
            if (DinoRect.x < 180) {
                DinoRect.x += 57;
                SDL_Delay(20);
            }
            else DinoRect.x = 0;

            JumpRect.x = character.GetPosX();
            JumpRect.y = character.GetPosY();
            character.Move();
            
            
            //Animations of Background
            BackgroundRect.x += -GROUND_SPEED;
            BackgroundP2Rect.x = BackgroundRect.x + BackgroundRect.w;
            if (BackgroundP2Rect.x <= 0) BackgroundRect.x = 0;

            SDL_RenderCopy(renderer, Background, NULL, &BackgroundRect);
            SDL_RenderCopy(renderer, Background, NULL, &BackgroundP2Rect);

            //Animations of Enemies
            
            enemy1.Move( acceleration);
            ene1.x = enemy1.GetPosX();
            SDL_RenderCopy(renderer, cactus, 0, &ene1);

            enemy2.Move( acceleration);
            ene2.x = enemy2.GetPosX();
            SDL_RenderCopy(renderer, cactus, 0, &ene2);

            enemy3.Move( acceleration);
            ene3.x = enemy3.GetPosX();
            ene3.y = enemy3.GetPosY();
            if (BatRect.x < 162) {
                BatRect.x += 43;
                SDL_Delay(20);
            }
            else BatRect.x = 0;
            SDL_RenderCopy(renderer, bat, &BatRect, &ene3);
            
          
            //Dinosaur
            if (character.OnGround()) 
            {
                if (enemy1.CheckCollision(RedRect, ene1) || enemy2.CheckCollision(RedRect, ene2) || enemy3.CheckCollision(RedRect, ene3))  Quit = true;
                
                SDL_RenderCopy(renderer, Character, &DinoRect, &RedRect);
            }  
            else 
            {
                if (enemy1.CheckCollision(JumpRect, ene1) || enemy2.CheckCollision(JumpRect, ene2) || enemy3.CheckCollision(JumpRect, ene3)) Quit = true;
                  
                SDL_RenderCopy(renderer, RedCharacter, 0, &JumpRect);
            } 
             SDL_RenderPresent(renderer);
        
            
    }
    
    
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}