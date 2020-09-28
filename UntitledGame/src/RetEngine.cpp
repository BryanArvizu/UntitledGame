#include "RetEngine.h"


ret::RetEngine::RetEngine()
{
    window_ = new ret::Window();
}

int ret::RetEngine::Run()
{
    while (window_->IsActive())
    {
        UpdateEntities();
    }

    return 0;
}

void ret::RetEngine::UpdateEntities()
{
    for (unsigned int i = 0; i < entities_.size(); i++)
    {
        if (entities_[i].isEnabled())
            entities_[i].Update();
    }
}