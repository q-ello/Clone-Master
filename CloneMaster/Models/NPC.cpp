#include "NPC.h"

NPC::NPC(const std::string& name, int dmg, int hitChance, const std::string& inRoomAwake, const std::string& inRoomUnconscious, const std::string& incorrectItemResponse, const std::string& requiredItem, const std::string& hasItemResponse, int HP, const std::string& greeting, bool canBeCloned, bool isRecrutable)
    : name_{ name }
    , dmg_{ dmg }
    , hitChance_{ hitChance }
    , inRoomAwake_{ inRoomAwake }
    , inRoomUnconscious_{ inRoomUnconscious }
    , incorrectItemResponse_{ incorrectItemResponse }
    , requiredItem_{ requiredItem }
    , hasItemResponse_{ hasItemResponse }
    , HP_{ HP }
    , greeting_{ greeting }
    , canBeCloned_{ canBeCloned }
    , isRecrutable_{ isRecrutable }
{
    if (inRoomAwake == "")
    {
        inRoomAwake_ = name_ + " is standing in the room.";
        inRoomUnconscious_ = "There is an unconscious body of " + name_;
    }
}

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
