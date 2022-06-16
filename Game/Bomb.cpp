/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(std::pair<float, float> pos, float timeUntilExplode, int strength)
    : pos(pos)
    , strength(strength)
    , clock(timeUntilExplode)
    , collideBox(pos, {0.6, 0.6})
{
}

void Bomb::update()
{
    this->clock.refresh();
    if (static_cast<int>(this->clock.loop()) == 1)
        explode();
}

void Bomb::explode()
{
    hasExplode = true;
}

bool Bomb::hasExploded() const
{
    return this->hasExplode;
}

std::pair<float, float> Bomb::getPos() const
{
    return this->pos;
}

int Bomb::getStrength() const
{
    return this->strength;
}

CollisionBox& Bomb::getCollideBox()
{
    return this->collideBox;
}

bool Bomb::getOwnerInside() const
{
    return this->ownerInside;
}

void Bomb::setOwnerInside(bool isInside)
{
    this->ownerInside = isInside;
}