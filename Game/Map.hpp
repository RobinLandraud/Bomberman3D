/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <vector>

#include "Bonuses.hpp"
#include "Clock.hpp"
#include "Engine.hpp"

enum BlockType { AIR, BOX, OBSTACLE, EXPLODE };

class Block
{
  public:
    Block(std::pair<float, float> pos, BlockType type);
    Block(const Block& other) noexcept = default;
    Block(Block&& other) noexcept = default;
    ~Block() noexcept = default;

    Block& operator=(const Block&) noexcept = default;
    Block& operator=(Block&&) noexcept = default;
    [[nodiscard]] BlockType getType() const;
    void setType(BlockType type);
    [[nodiscard]] std::pair<float, float> getPos() const;
    CollisionBox& getCollideBox();
    void updateBlock();
    void startClock();

  protected:
  private:
    BlockType type = AIR;
    std::pair<float, float> pos;
    std::vector<Clock> clocks = {};
    CollisionBox collideBox;
};

class Map
{
  public:
    explicit Map(Engine& engine);
    Map(const Map& other) noexcept = default;
    Map(Map&& other) noexcept = default;
    ~Map() noexcept = default;

    Map& operator=(const Map&) noexcept = default;
    Map& operator=(Map&&) noexcept = default;

    void update();
    void parseMap(std::string& path);
    void fillMap();
    void drawBlocks();
    Block& getBlock(std::pair<float, float>);
    Engine& getEngine();
    std::vector<std::pair<float, float>> getSpawns();
    std::vector<std::vector<Block>> getBlocks();
    void giveMeWhatExplode(int strength, std::pair<float, float> pos);
    void addBonuses(std::pair<float, float> pos);
    std::vector<Bonuses> getBonuses();
    void removeBonuses(Bonuses& bonuse);

  protected:
  private:
    Engine& engine;
    std::vector<std::vector<Block>> blocks = {};
    std::vector<std::string> maptxt;
    std::vector<std::pair<float, float>> spawns = {};
    std::vector<Bonuses> bonuses = {};
    float sizeBlock = 1;
};

#endif /* !MAP_HPP_ */
