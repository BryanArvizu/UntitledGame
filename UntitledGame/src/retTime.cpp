#include "retTime.h"
#include <GLFW/glfw3.h>

ret::Time* ret::Time::instance = 0;

bool ret::Time::Start()
{
    if (!instance)
    {
        instance = new Time;
        return true;
    }
    return false;
}

double ret::Time::GetTime()
{
    return instance->time;
}

double ret::Time::GetDeltaTime()
{
    return instance->deltaTime;
}

void ret::Time::Update()
{
    instance->lastTime = instance->time;
    instance->time = glfwGetTime();
    instance->deltaTime = instance->time - instance->lastTime;
}


