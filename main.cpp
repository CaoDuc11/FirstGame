
#include"GameBase.h"
#include"Enemy.h"
#include"Character.h"
#include"Time.h"

using namespace std;

Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gTing = nullptr;

int UpdateGameTimeAndScore(int& time, int& speed, int& score)
{
    if (time == TIME_MAX)
    {
        speed += SPEED_INCREASEMENT;
    }

    if (time > TIME_MAX)
    {
        time = 0;
    }
    if (time % 5 == 0)
    {
        score += SCORE_INCREASEMENT;
        if (score % 100 == 0) Mix_PlayChannel( MIX_CHANNEL, gTing, 0);
    }

    time += TIME_INCREASEMENT;

    return time;
}
bool LoadMedia()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return  false;

    bool success = true; 
    gClick = Mix_LoadWAV("mouse_click.wav");
    if (gClick == nullptr)
    {
        LogError("Failed to load mouse click sound", MIX_ERROR);
        success = false;
    }

    gJump = Mix_LoadWAV("jump_sound.wav");
    if (gJump == nullptr)
    {
        LogError("Failed to load jumping sound", MIX_ERROR);
        success = false;
    }

    gLose = Mix_LoadWAV("lose_sound.wav");
    if (gLose == nullptr)
    {
        LogError("Failed to load lose sound", MIX_ERROR);
        success = false;
    }
    gTing = Mix_LoadWAV("ting.wav");
    if (gTing == nullptr)
    {
        LogError("Failed to load ting sound", MIX_ERROR);
        success = false;
    }
    return success = true;
}
int main (int argc, char* argv[] )
{
    if( LoadMedia())
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        Character character;
        Time fps;

        srand(time(NULL));
        int time = 0;
        int score = 0;
        int acceleration = 10;

        SDL_Event e;
        Enemy enemy1(ON_GROUND_ENEMY);
        Enemy enemy2(ON_GROUND_ENEMY);
        Enemy enemy3(IN_AIR_ENEMY);

        initSDL(window, renderer);


        //Load Background
        SDL_Texture* Background = loadTexture("BackgroundUpdate.png", renderer);
        SDL_Rect BackgroundRect = { 0, 0 , 2051, 720 };

        SDL_Rect BackgroundP2Rect;
        BackgroundP2Rect.y = 0;
        BackgroundP2Rect.w = 2051;
        BackgroundP2Rect.h = 720;

        //Load main character
        SDL_Texture* Character = loadTexture("DinoRed.png", renderer);
        SDL_Texture* RedCharacter = loadTexture("unnamed.png", renderer);
        SDL_Rect DinoRect = { 0, 0, 57, 57 };
        SDL_Rect RedRect = { 300, GROUND , 100, 100 };
        SDL_Rect JumpRect = { 300, GROUND, 72, 72 };

        //Load cactus
        SDL_Texture* cactus = loadTexture("cactus.png", renderer);
        SDL_Rect ene1 = { 0, GROUND, 90, 90 };
        SDL_Rect ene2 = { 0, GROUND + 30, 60, 60 };

        //Load bat
        SDL_Texture* bat = loadTexture("bat.png", renderer);
        SDL_Rect BatRect = { 0, 0, 43,30 };
        SDL_Rect ene3 = { 0, 0, 60, 50 };

        bool Quit = 0;
        while (!Quit)
        {
            fps.start();
            UpdateGameTimeAndScore(time, acceleration, score);
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) {
                    Quit = true;
                    quitSDL(window, renderer);
                    break;
                }
                character.HandleEvent(e, gJump);

            }

            SDL_RenderClear(renderer);
            
            //Animations of Background
            BackgroundRect.x += -GROUND_SPEED;
            BackgroundP2Rect.x = BackgroundRect.x + BackgroundRect.w;
            if (BackgroundP2Rect.x <= 0) BackgroundRect.x = 0;

            SDL_RenderCopy(renderer, Background, NULL, &BackgroundRect);
            SDL_RenderCopy(renderer, Background, NULL, &BackgroundP2Rect);
            
            //Animations of Dino

            

            JumpRect.x = character.GetPosX();
            JumpRect.y = character.GetPosY();
            character.Move();


            //Animations of Cactus

            enemy1.Move(acceleration);
            ene1.x = enemy1.GetPosX();
            SDL_RenderCopy(renderer, cactus, 0, &ene1);

            enemy2.Move(acceleration);
            ene2.x = enemy2.GetPosX();
            SDL_RenderCopy(renderer, cactus, 0, &ene2);

            //Animation of Bat
            enemy3.Move(acceleration);
            ene3.x = enemy3.GetPosX();
            ene3.y = enemy3.GetPosY();
            

            SDL_RenderCopy(renderer, bat, &BatRect, &ene3);


            //Dinosaur && Collision
            if (character.OnGround())
            {
                SDL_RenderCopy(renderer, Character, &DinoRect, &RedRect);
                if (enemy1.CheckCollision(RedRect, ene1) || enemy2.CheckCollision(RedRect, ene2) || enemy3.CheckCollision(RedRect, ene3))
                {
                    Mix_PlayChannel( MIX_CHANNEL, gLose, 0);
                    Quit = true;

                }

            }
            else
            {
                SDL_RenderCopy(renderer, RedCharacter, 0, &JumpRect);
                if (enemy1.CheckCollision(JumpRect, ene1) || enemy2.CheckCollision(JumpRect, ene2) || enemy3.CheckCollision(JumpRect, ene3)) 
                {
                    Mix_PlayChannel( MIX_CHANNEL, gLose, 0);
                    Quit = true;

                }
            }
            
            if (DinoRect.x < 180) {
                DinoRect.x += 57;
            }
            else DinoRect.x = 0;

            if (BatRect.x < 162)
            {
                BatRect.x += 43;
            }
            else BatRect.x = 0;
            int realtime = fps.getTicks();
            int one_frame = 1000 / FPS;
            if (realtime < one_frame)
            {
                int delay_time = one_frame - realtime;
                if (delay_time >= 0) SDL_Delay(delay_time);
            }
            else SDL_Delay(one_frame);

            SDL_RenderPresent(renderer);
            
        }
        waitUntilKeyPressed();
        quitSDL(window, renderer);
        return 0;
    }
    else
    {
        cout << "Unable to load Media";
        return 0;
    }
       
        
}
