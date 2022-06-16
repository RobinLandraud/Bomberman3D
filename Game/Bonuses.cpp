/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bonuses
*/

#include "Bonuses.hpp"

Bonuses::Bonuses(std::pair<float, float> pos)
    : type(static_cast<BonusesType>(rand() % 4))
    , pos(pos)
    , collideBox(pos, {0.6, 0.6})
{
}

void Bonuses::display(Engine& engine)
{
    Engine::drawBlock(engine.getTexture(textures.at(type)),
        {pos.first, 1.0f, pos.second},
        collideBox.w,
        1,
        collideBox.h,
        WHITE);
}

BonusesType Bonuses::getType() const
{
    return this->type;
}

CollisionBox& Bonuses::getCollideBox()
{
    return this->collideBox;
}

std::pair<float, float> Bonuses::getPos() const
{
    return this->pos;
}