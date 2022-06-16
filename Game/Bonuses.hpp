/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bonuses
*/

#ifndef BONUSES_HPP_
#define BONUSES_HPP_

#include <map>

#include "Button.hpp"
#include "Engine.hpp"

enum BonusesType { SPEED, BOMB_UP, BOMB_RANGE, WALL_PATH };

class Bonuses
{
  public:
    Bonuses(std::pair<float, float> pos);
    Bonuses(const Bonuses& other) noexcept = default;
    Bonuses(Bonuses&& other) noexcept = default;
    ~Bonuses() noexcept = default;

    Bonuses& operator=(const Bonuses&) noexcept = default;
    Bonuses& operator=(Bonuses&&) noexcept = default;
    void display(Engine& engine);
    CollisionBox& getCollideBox();
    [[nodiscard]] BonusesType getType() const;
    [[nodiscard]] std::pair<float, float> getPos() const;

  protected:
  private:
    BonusesType type = SPEED;
    std::pair<float, float> pos;
    CollisionBox collideBox;
    std::map<BonusesType, std::string> textures = {{SPEED, "skate"},
        {BOMB_UP, "bomb_up"},
        {BOMB_RANGE, "fire"},
        {WALL_PATH, "soft_block_pass"}};
};

#endif /* !BONUSES_HPP_ */
