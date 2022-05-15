#ifndef TIME_H
#define TIME_H



class Time
{
public:
    Time();
    ~Time();

    void start();
    void stop();
    void pause();
    void unpause();

    int getTicks();

    bool Is_Started();
    bool Is_Paused();

private:
    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;
};



#endif
