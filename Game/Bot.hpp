/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bot
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include "ACharacter.hpp"

class Bot : public ACharacter
{
  public:
    Bot(Map&,
        Settings::Difficulty,
        std::string& skinAsset,
        std::string playerIqm,
        std::vector<std::string> animIqm,
        std::pair<float, float>,
        float speed,
        Engine& engine);
    Bot(const Bot& other) noexcept = default;
    Bot(Bot&& other) noexcept = default;
    ~Bot() noexcept = default;

    Bot& operator=(const Bot&) noexcept = default;
    Bot& operator=(Bot&&) noexcept = default;

    void display() override;
    void setAxe(std::tuple<float, float, float, float>);
    [[nodiscard]] std::tuple<float, float, float, float> getAxe() const;
    Model3D& getModel() override;
    std::pair<float, float> getNextPos() override;
    std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
    getBlockAroundMe(int length);
    void setNextDirs();
    std::vector<Direction> getPath(std::pair<int, int> pos,
        int tempX,
        int tempY,
        std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
            tab,
        std::vector<Direction> possibleNextDirs,
        Direction prevMove);
    bool poseBomb(
        std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
            tab,
        std::pair<int, int> playerPos);
    void respawn(bool isDead, Engine& engine) override;
    static std::pair<int, int> getCurrentPosInTab(
        std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
            tab,
        std::pair<int, int> currentPos);

  protected:
  private:
    Settings::Difficulty difficulty;
    Engine& engine;
    Model3D model;
    std::tuple<float, float, float, float> axe = {1.0f, 0.0f, 0.0f, -90.0f};
    std::vector<Direction> nextDirs = {};
    std::pair<int, int> oldPos = {0, 0};
    std::string playerIqm;
    std::vector<std::string> animIqm;
    static int preciseFloor(float);
};

#endif /* !BOT_HPP_ */
