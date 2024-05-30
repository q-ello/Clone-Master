#include "NPC.h"

void NPC::takeDamage(int dmg)
{
    if (rand() % 10 <= hitChance_)
    {
        HP_ = HP_ < dmg ? 0 : HP_ - dmg;
        if (HP_ == 0)
        {
            std::cout << name_ << " has been defeated." << std::endl;
            return;
        }

        std::cout << name_ << " was quite shaken." << std::endl;
        return;
    }

    std::cout << name_ << " managed to dodge." << std::endl;
}

std::string NPC::getDescription() const
{
    if (HP_ > 0)
    {
        return inRoomAwake_;
    }

    return inRoomUnconscious_;
}
