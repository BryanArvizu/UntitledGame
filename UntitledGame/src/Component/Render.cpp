#include "Render.h"

#include <iostream>

void ret::Render::Start()
{
    std::cout << "ELLO MATE" << std::endl;
    auto renderer = ret::RetEngine::Get()->renderer;
    if(renderer != nullptr)
        renderer->Add(this);
}
