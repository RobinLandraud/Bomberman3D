/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>

#include "AScene.hpp"
#include "Bomb.hpp"
#include "Bot.hpp"
#include "Clock.hpp"
#include "Engine.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Settings.hpp"

namespace indie
{
class Game : public Ascene
{
  public:
    explicit Game(Engine& engine, Settings& settings);
    Game(const Game& other) noexcept = default;
    Game(Game&& other) noexcept = default;
    ~Game() noexcept = default;

    Game& operator=(const Game&) noexcept = default;
    Game& operator=(Game&&) noexcept = default;

    void launchGame();
    void resetGame();
    void displayScene() override;
    SceneEvent updateScene() override;
    Map& getMap();
    void initPlayers();
    void printLifes(ACharacter& character,
        std::pair<float, float> pos,
        Settings::Skin color);
    void drawBomb();
    void drawGUI(ACharacter& character, int count, Settings::Skin color);
    Clock getClocky();
    void setClocky(Clock clocky_tmp);
    void setCurrentSongString(std::string& name);
    std::string& getCurrentSongString();

  protected:
  private:
    std::vector<std::pair<float, float>> guiLifePos = {
        {50, 50}, {1600, 50}, {50, 700}, {1600, 700}};
    std::vector<Model3D> charsModels = {};
    std::vector<Player> players = {};
    std::vector<Bot> bots = {};
    Map map;
    Clock clock;
    Clock clocky;
    Clock clocka;
    std::vector<std::string> gameSongs = {
        "ice_bb_song", "volcano", "underground", "forest", "highway"};
    std::string currentSong;
    std::vector<std::string> mapPaths = {"./assets/maps/map1.txt"};
    float toto = 180.0f;
};
}

#endif /* !GAME_HPP_ */