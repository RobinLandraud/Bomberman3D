/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <memory.h>

#include <cmath>
#include <utility>

#include "Bomb.hpp"
#include "Button.hpp"
#include "Clock.hpp"
#include "Engine.hpp"
#include "Event.hpp"
#include "Map.hpp"
#include "Settings.hpp"

class ACharacter
{
  public:
    enum Direction { UP, DOWN, LEFT, RIGHT, BOMB, NONE };
    ACharacter(Map& map, std::pair<float, float> pos, float speed);
    ACharacter(const ACharacter& other) noexcept = default;
    ACharacter(ACharacter&& other) noexcept = default;
    ~ACharacter() noexcept = default;

    ACharacter& operator=(const ACharacter&) noexcept = default;
    ACharacter& operator=(ACharacter&&) noexcept = default;

    void update(Event& event, Engine& engine);
    virtual void display();

    void setNbBomb(int nbBomb);
    [[nodiscard]] bool hasLaunchBomb() const;
    [[nodiscard]] int getNbBomb() const;
    [[nodiscard]] int getMaxBomb() const;
    [[nodiscard]] int getLife() const;
    [[nodiscard]] int getBombStrength() const;
    void setDirection(Direction dir);
    [[nodiscard]] Direction getDirection() const;
    [[nodiscard]] std::pair<float, float> getPos() const;
    std::vector<Bomb>& getBombs();
    void setOtherChars(
        std::tuple<ACharacter&, ACharacter&, ACharacter&> newOthers);
    std::tuple<ACharacter&, ACharacter&, ACharacter&> getOtherChars();
    [[nodiscard]] std::pair<float, float> getSpawn() const;
    void setPos(std::pair<float, float>);
    void updateBombs();
    std::vector<Bomb> getAllBomb();
    [[nodiscard]] bool getIsInvisible() const;
    void setIsInvisible(bool invisible);
    virtual std::pair<float, float> getNextPos();
    std::pair<bool, bool> checkCollide(
        std::pair<float, float> pos, std::vector<std::vector<Block>> blocks);
    virtual void respawn(bool isDead, Engine& engine);
    void collideBonuses();
    virtual Model3D& getModel() = 0;

  protected:
    std::unique_ptr<std::tuple<ACharacter&, ACharacter&, ACharacter&>>
        otherChars;
    Direction direction;
    std::pair<float, float> spawn = {0, 0};
    std::pair<float, float> pos = {0, 0};
    CollisionBox collideBox;
    Clock clockBomb;
    Clock inviTime;
    Map& map;
    bool isInvisible = false;
    bool isGhost = false;
    Clock ghostTime;
    std::vector<Bomb> bombs = {};
    std::vector<Bomb> allBomb = {};
    int bombStrength = 1;
    int nbBomb = 1;
    int maxBomb = 1;
    float speed = 1;
    bool isAlive = true;
    bool launchBomb = false;
    int dropBomb();
    int life = 3;

  private:
};

#endif /* !CHARACTER_HPP_ */
