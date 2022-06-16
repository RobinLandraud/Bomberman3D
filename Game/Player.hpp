/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <cmath>

#include "ACharacter.hpp"

class Player : public ACharacter
{
  public:
    Player(Map&,
        std::vector<KeyList> binding,
        Settings::Skin skin,
        std::string& skinAsset,
        std::string playerIqm,
        std::vector<std::string> animIqm,
        std::pair<float, float>,
        float speed,
        Engine& engine);
    Player(const Player& other) noexcept = default;
    Player(Player&& other) noexcept = default;
    ~Player() noexcept = default;

    Player& operator=(const Player&) noexcept = default;
    Player& operator=(Player&&) noexcept = default;

    void display() override;
    void setAxe(std::tuple<float, float, float, float>);
    [[nodiscard]] std::tuple<float, float, float, float> getAxe() const;
    Model3D& getModel() override;
    Settings::Skin getSkin() const;
    std::pair<float, float> getNextPos() override;

  protected:
  private:
    Settings::Skin skin;
    Engine& engine;
    Model3D model;
    std::tuple<float, float, float, float> axe = {1.0f, 0.0f, 0.0f, -90.0f};
    std::vector<KeyList> binding = {};
    std::map<Settings::Skin, std::string> skins;
    std::string playerIqm;
    std::vector<std::string> animIqm;
};

#endif /* !PLAYER_HPP_ */
