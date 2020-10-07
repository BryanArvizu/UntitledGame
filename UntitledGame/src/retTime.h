#pragma once
namespace ret {
    class Time
    {
    private:
        static Time* instance;

        Time() : time(0), lastTime(0), deltaTime(0) {}
        double time;
        double lastTime;
        double deltaTime;
    public:
        static bool Start();
        static double GetTime();
        static double GetDeltaTime();
        static void Update();
    };
}

