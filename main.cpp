
#include"GameBase.h"
#include"Enemy.h"
#include"Character.h"
#include"Time.h"
#include"TextObject.h"
using namespace std;

Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gTing = nullptr;

TTF_Font* gFontText = nullptr;

SDL_Texture* g_img_Menu = nullptr;
SDL_Texture* g_img_Information = nullptr;
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
    if (time % 2 == 0)
    {
        score += SCORE_INCREASEMENT;
        if (score % 100 == 0) Mix_PlayChannel( MIX_CHANNEL, gTing, 0);
    }

    time += TIME_INCREASEMENT;

    return time;
}
int ConvertToInt( string d)
{   
    int n = 0;
    for (int i = 0; i < d.length(); i++)
    {
        n = n * 10 + (d[i] - '0');
    }
    return n;
}
void SaveScore(  const string score, const string path)
{
    fstream HighScoreFile;
    HighScoreFile.open(path, ios::out);
    HighScoreFile.clear();
    HighScoreFile << score;
}
string GetHighScoreAndUpdate( const string path,  const int score)
{
    fstream HighScoreFile;
    HighScoreFile.open(path, ios::in);
    
    string old_high_score;
    HighScoreFile >> old_high_score;
    
    string highScore = to_string( score);

    int old_HI = ConvertToInt( old_high_score);
    if (score > old_HI)
    {
        SaveScore(highScore, path); 
        return highScore;
    }
    else  return old_high_score;
}
bool LoadMediaAndTtf()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return  false;

    bool success = true; 
    gMusic = Mix_LoadMUS("nen.wav");
    if (gMusic == nullptr)
    {
        LogError("Failed to load background music", MIX_ERROR);
        success = false;
    }

    gMenuMusic = Mix_LoadMUS("Menu.mp3");
    if (gMenuMusic == nullptr)
    {
        LogError("Failed to load menu music", MIX_ERROR);
        success = false;
    }
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
    
    if (TTF_Init() == -1) return false;
    gFontText = TTF_OpenFont( "font//ARCADE.ttf", 48);
    if (gFontText == nullptr)
    {
        LogError("Failed to load font", TTF_ERROR);
        success = false;
    }
    return success;
}
int ShowMenu(SDL_Renderer* renderer, TTF_Font* font)
{
    g_img_Menu = loadTexture("Menu.jpg", renderer);
    if (g_img_Menu == nullptr) return 2;

    const int kMenuItemNum = 3;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 500;

    pos_arr[2].x = 200;
    pos_arr[2].y = 600;

    TextObject text_Menu[kMenuItemNum];
    text_Menu[0].SetText("Play Game");
    text_Menu[0].setColor(TextObject::WHITE_TEXT);



    text_Menu[1].SetText("Information");
    text_Menu[1].setColor(TextObject::WHITE_TEXT);

    text_Menu[2].SetText("Exit");
    text_Menu[2].setColor(TextObject::WHITE_TEXT);

    int xm = 0, ym = 0;
    bool selected[kMenuItemNum] = { 0, 0, 0 };
    SDL_Event m;
    while (true)
    {
        
        while (SDL_PollEvent(&m))
        {
            SDL_RenderCopy(renderer, g_img_Menu, NULL, NULL);
            for (int i = 0; i < kMenuItemNum; i++)
            {
                text_Menu[i].loadFromRenderedText(font, renderer);
                text_Menu[i].RenderText(renderer, pos_arr[i].x, pos_arr[i].y);
                pos_arr[i].w = text_Menu[i].getWidth();
                pos_arr[i].h = text_Menu[i].getHeight();
            }
          
            switch (m.type)
            {
            case SDL_QUIT:
                return 2;
            case SDL_MOUSEMOTION:
            {
                xm = m.motion.x;
                ym = m.motion.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, pos_arr[i]))
                    {

                        if (selected[i] == false)
                        {
                            selected[i] = 1;
                            text_Menu[i].setColor(TextObject::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            text_Menu[i].setColor(TextObject::WHITE_TEXT);
                        }
                    }
                            
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m.button.x;
                ym = m.button.y;
                for (int i = 0; i < kMenuItemNum; i++)
                {
                    if (CheckFocusWithRect(xm, ym, pos_arr[i]))
                    {
                        return i;
                    }
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 2;
                }
            }
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return 2;
}
int ShowInformation( SDL_Renderer* renderer, TTF_Font* font)
{
    g_img_Information = loadTexture("Information.jpg", renderer);
    SDL_Rect pos_arr;
    pos_arr.x = 15;
    pos_arr.y = SCREEN_HEIGHT - 100;

    TextObject text_back;
    text_back.SetText("Back");
    text_back.setColor(TextObject::WHITE_TEXT);
    int xm = 0, ym = 0;
    bool selected = 0;
    SDL_Event m;
    while (true)
    {

        while (SDL_PollEvent(&m))
        {
            SDL_RenderCopy(renderer, g_img_Information, NULL, NULL);
            text_back.loadFromRenderedText(font, renderer);
            text_back.RenderText(renderer, pos_arr.x, pos_arr.y);
            pos_arr.w = text_back.getWidth();
            pos_arr.h = text_back.getHeight();
         
            switch (m.type)
            {
            case SDL_QUIT:
                return 0;
            case SDL_MOUSEMOTION:
            {
                xm = m.motion.x;
                ym = m.motion.y;
                if (CheckFocusWithRect(xm, ym, pos_arr))
                {

                    if (selected == false)
                    {
                        selected = 1;
                        text_back.setColor(TextObject::RED_TEXT);
                    }
                }
                else
                {
                    if (selected == true)
                    {
                        selected = 0;
                        text_back.setColor(TextObject::WHITE_TEXT);
                    }
                }   
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                xm = m.button.x;
                ym = m.button.y;
                if (CheckFocusWithRect(xm, ym, pos_arr))
                {                                                                                                                                           
                    return 1;
                }
            }
            break;
            case SDL_KEYDOWN:
            {
                if (m.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 0;
                }
            }
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }


}

int main (int argc, char* argv[] )
{
    if( LoadMediaAndTtf())
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        initSDL(window, renderer);

        bool Quit = 0;
        bool Quit_Menu = false;
        Mix_PlayMusic(gMenuMusic, -1);
        while( !Quit_Menu)
        {
            int checkExit = ShowMenu(renderer, gFontText);
            while (checkExit != 0 && Quit == false)
            {
                if (checkExit == 2)
                {
                    Quit = true;
                    Quit_Menu = true;
                } 
                else
                {
                    if (checkExit == 1)
                    {
                        checkExit = ShowInformation(renderer, gFontText);
                        if (checkExit == 2)
                        {
                            Quit = true;
                            Quit_Menu = true;
                        }
                        else
                        {
                            SDL_RenderClear(renderer);
                            checkExit = ShowMenu(renderer, gFontText);
                        }
                    }
                }
            }
            Quit_Menu = true;
        }
        Mix_PlayMusic(gMusic, -1);
        Character character;
        Time fps;
        TextObject score_text;
        score_text.setColor( TextObject :: WHITE_TEXT);

        TextObject HIscore_text;
        HIscore_text.setColor(TextObject::WHITE_TEXT);
        
        srand(time(NULL));
        int time = 0;
        int score = 0;
        int acceleration = 5;

        SDL_Event e;
        Enemy enemy1(ON_GROUND_ENEMY);
        Enemy enemy2(ON_GROUND_ENEMY);
        Enemy enemy3(IN_AIR_ENEMY);

       
        
       
       
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
       while (!Quit)
       {
           
           fps.start();
           UpdateGameTimeAndScore(time, acceleration, score);

           while (SDL_PollEvent(&e) != 0)
           {
               if (e.type == SDL_QUIT) {
                   Quit = true;
                   break;
               }
               character.HandleEvent(e, gJump);

           }

           SDL_RenderClear(renderer);


           //Animations of Background
           BackgroundRect.x += -(GROUND_SPEED + acceleration);
           BackgroundP2Rect.x = BackgroundRect.x + BackgroundRect.w;
           if (BackgroundP2Rect.x <= 0) BackgroundRect.x = 0;

           SDL_RenderCopy(renderer, Background, NULL, &BackgroundRect);
           SDL_RenderCopy(renderer, Background, NULL, &BackgroundP2Rect);

           //ShowHighScore
           string val_str_HIscore = GetHighScoreAndUpdate("HighScore.txt", score);
           string str_HIscore("HighScore: ");
           str_HIscore += val_str_HIscore;
           HIscore_text.SetText(str_HIscore);
           HIscore_text.loadFromRenderedText(gFontText, renderer);
           HIscore_text.RenderText(renderer, SCREEN_WIDTH - 600, 15);


           //ShowScore
           string val_str_score = to_string(score);
           string str_score("Score: ");
           str_score += val_str_score;
           score_text.SetText(str_score);
           score_text.loadFromRenderedText(gFontText, renderer);
           score_text.RenderText(renderer, SCREEN_WIDTH - 250, 15);


           //Animations of Dino
           JumpRect.x = character.GetPosX();
           JumpRect.y = character.GetPosY();
           character.Move();

           //Moving of Cactus
           enemy1.Move(acceleration);
           ene1.x = enemy1.GetPosX();
           SDL_RenderCopy(renderer, cactus, 0, &ene1);

           enemy2.Move(acceleration);
           ene2.x = enemy2.GetPosX();
           SDL_RenderCopy(renderer, cactus, 0, &ene2);

           //Moving of Bat
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
                   Mix_PauseMusic();
                   Mix_PlayChannel(MIX_CHANNEL, gLose, 0);
                   Quit = true;

               }

           }
           else
           {
               SDL_RenderCopy(renderer, RedCharacter, 0, &JumpRect);
               if (enemy1.CheckCollision(JumpRect, ene1) || enemy2.CheckCollision(JumpRect, ene2) || enemy3.CheckCollision(JumpRect, ene3))
               {
                   Mix_PauseMusic();
                   Mix_PlayChannel(MIX_CHANNEL, gLose, 0);
                   Quit = true;

               }
           }

           //Animations of Dino
           if (DinoRect.x < 180) {
               DinoRect.x += 57;
           }
           else DinoRect.x = 0;

           //Animations of Bat
           if (BatRect.x < 162)
           {
               BatRect.x += 43;
           }
           else BatRect.x = 0;

           //Fix FPS
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
       score_text.Free();

       enemy1.~Enemy();
       enemy2.~Enemy();
       enemy3.~Enemy();
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
