#include "Store.h"

int Squad::getOverallDamage()
{
    int dmg = 0;

    for (auto it = entities_.begin(); it != entities_.end(); it++)
    {
        dmg += (*it)->damage();
    }

    return dmg;
}