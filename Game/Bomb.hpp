/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bomb
*/

#ifndef Bomb_HPP_
#define Bomb_HPP_

#include <iostream>
#include <vector>

#include "Clock.hpp"
#include "Map.hpp"

class Bomb
{
  public:
    Bomb(std::pair<float, float> pos, float timeUntilExplode, int strength);
    ~Bomb() noexcept = default;
    Bomb(const Bomb& other) noexcept = default;
    Bomb(Bomb&& other) noexcept = default;

    Bomb& operator=(const Bomb&) noexcept = default;
    Bomb& operator=(Bomb&& other) noexcept = default;

    void update();
    [[nodiscard]] bool hasExploded() const;
    std::pair<float, float> getPos() const;
    [[nodiscard]] int getStrength() const;
    void explode();
    CollisionBox& getCollideBox();
    [[nodiscard]] bool getOwnerInside() const;
    void setOwnerInside(bool);

  protected:
  private:
    CollisionBox collideBox;
    std::pair<float, float> pos;
    int strength = 0;
    bool hasExplode = false;
    Clock clock;
    bool ownerInside = true;
};

#endif /* !Bomb_HPP_ */
