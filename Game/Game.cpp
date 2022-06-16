/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Game
*/

#include "Game.hpp"

#include <string>

#include "Engine.hpp"
#include "Model3D.hpp"
#include "Settings.hpp"

namespace indie
{
Game::Game(Engine& engine, Settings& settings)
    : Ascene(engine, settings)
    , clock(1)
    , map(engine)
    , clocky(15)
    , clocka(0.01)
    , currentSong(gameSongs.at(rand() % gameSongs.size()))
{
    map.parseMap(mapPaths.at(0));
    srand(time(nullptr));
}

void Game::launchGame()
{
    clocky.reset();
    map.getEngine().initCameraMode(CAMERA_FREE);
    initPlayers();
    if (players.size() == 2) {
        players.at(0).setOtherChars({players.at(1), bots.at(0), bots.at(1)});
        players.at(1).setOtherChars({players.at(0), bots.at(0), bots.at(1)});
        bots.at(0).setOtherChars({players.at(0), players.at(1), bots.at(1)});
        bots.at(1).setOtherChars({players.at(0), players.at(1), bots.at(0)});
    } else {
        players.at(0).setOtherChars({bots.at(0), bots.at(1), bots.at(2)});
        bots.at(0).setOtherChars({players.at(0), bots.at(1), bots.at(2)});
        bots.at(1).setOtherChars({players.at(0), bots.at(0), bots.at(2)});
        bots.at(2).setOtherChars({players.at(0), bots.at(0), bots.at(1)});
    }
}

void Game::setCurrentSongString(std::string& name)
{
    currentSong = name;
}

std::string& Game::getCurrentSongString()
{
    return (this->currentSong);
}

void Game::resetGame()
{
    std::string gameMenuSound = "main_menu_bb";
    map.parseMap(mapPaths.at(0));
    srand(time(nullptr));
    clock.reset();
    engine.getAudioEngine().pauseSound(currentSong);
    currentSong = gameSongs.at(rand() % gameSongs.size());
    engine.getAudioEngine().playSound(gameMenuSound);
    engine.setFramesCounter(0, 0);
    engine.setFramesCounter(0, 1);
    engine.setFramesCounter(0, 2);
    engine.setFramesCounter(0, 3);
    engine.setFramesCounter(0, 4);
    toto = 180.0f;
    map.getEngine().setCameraValue({5.0f, 15.0f, 10.0f},
        {5.0f, -40.0f, -5.0f},
        {0.0f, 1.0f, 0.0f},
        toto,
        CAMERA_ORTHOGRAPHIC);
    map.getEngine().updateCamera();
    clocky.reset();
    clocka.reset();
    players.clear();
    bots.clear();
}

void Game::initPlayers()
{
    int index = 0;
    std::string textureName = "deadpoolGrey";
    std::string playerIqm = "assets/player.iqm";
    std::vector<std::string> animIqm = {
        "assets/runninganim.iqm", "assets/standinganim.iqm"};
    std::vector<std::vector<KeyList>> bind = {
        {K_W, K_S, K_A, K_D, K_Q}, {K_UP, K_DOWN, K_LEFT, K_RIGHT, K_ENTER}};
    std::map<Settings::Skin, std::string> skins = {
        {Settings::Skin::S_RED, "deadpool"},
        {Settings::Skin::S_BLUE, "deadpoolBlue"},
        {Settings::Skin::S_YELLOW, "deadpoolYellow"},
        {Settings::Skin::S_GREEN, "deadpoolGreen"},
        {Settings::Skin::S_PURPLE, "deadpoolPurple"}};
    for (Settings::Skin player : this->settings.getPlayers()) {
        this->players.emplace_back(Player(this->map,
            bind.at(index),
            player,
            skins.at(player),
            playerIqm,
            animIqm,
            this->map.getSpawns().at(index),
            static_cast<float>(this->settings.getSpeed()),
            engine));
        index++;
    }
    for (Settings::Difficulty bot : this->settings.getBots()) {
        this->bots.emplace_back(Bot(this->map,
            bot,
            textureName,
            playerIqm,
            animIqm,
            this->map.getSpawns().at(index),
            static_cast<float>(this->settings.getSpeed()),
            engine));
        index++;
    }
}

void Game::drawGUI(ACharacter& character, int count, Settings::Skin color)
{
    printLifes(character, guiLifePos.at(count), color);
}

void Game::printLifes(
    ACharacter& character, std::pair<float, float> pos, Settings::Skin color)
{
    float x = pos.first;
    float y = pos.second;
    std::vector<std::string> textureNames = {
        "table", "heart", "bombIcon", "explosion"};
    switch (color) {
        case Settings::Skin::S_BLUE:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, BLUE);
            break;
        case Settings::Skin::S_RED:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, RED);
            break;
        case Settings::Skin::S_GREEN:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, GREEN);
            break;
        case Settings::Skin::S_PURPLE:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, PURPLE);
            break;
        case Settings::Skin::S_YELLOW:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, YELLOW);
            break;
        case Settings::Skin::S_GREY:
            engine.drawTexture(
                textureNames.at(0), {pos.first, pos.second}, 0, 0.25, GRAY);
        default: break;
    }
    y += 30;
    for (int i = 0; i < character.getLife(); i++) {
        engine.drawTexture(textureNames.at(1), {x + 20, y}, 0, 0.2, GRAY);
        x += 50;
    }
    x = pos.first;
    y += 40;
    for (int i = 0; i < character.getNbBomb(); i++) {
        engine.drawTexture(textureNames.at(2), {x + 20, y}, 0, 0.5, WHITE);
        x += 50;
    }
    x = pos.first;
    y += 60;
    for (int i = 0; i < character.getBombStrength(); i++) {
        engine.drawTexture(textureNames.at(3), {x + 20, y}, 0, 0.5, WHITE);
        x += 50;
        if (x >= (pos.first + 150.0f)) {
            x = pos.first;
            y += 60;
        }
    }
}

void Game::displayScene()
{
    int count = 0;
    ClearBackground(SKYBLUE);
    std::string soundName = currentSong;
    if (clocky.loop()) {
        clocky.pause();
    }
    if (clocky.is_running() == Clock::PAUSE) {
        map.getEngine().setCameraValue({5.0f, 15.0f, 10.0f},
            {5.0f, -40.0f, -5.0f},
            {0.0f, 1.0f, 0.0f},
            45.0f,
            CAMERA_PERSPECTIVE);
    } else {
        map.getEngine().setCameraValue({5.0f, 15.0f, 10.0f},
            {5.0f, -40.0f, -5.0f},
            {0.0f, 1.0f, 0.0f},
            toto,
            CAMERA_ORTHOGRAPHIC);
        if (clocka.loop()) {
            toto = toto - 0.10f;
            engine.setFramesCounter(engine.getFramesCounter(0) + 1, 0);
            if (engine.getFramesCounter(0) > 700) {
                for (int i = 1; i <= 4; i++) {
                    engine.setFramesCounter(engine.getFramesCounter(i) + 1, i);
                }
            }
        }
        engine.drawHUDStart();
    }
    if (!AudioEngine::isSoundPlaying(
            engine.getAudioEngine().getSound(soundName)))
        engine.getAudioEngine().playSound(currentSong);
    for (Player& player : this->players) {
        if (clocky.is_running() == Clock::PAUSE)
            drawGUI(static_cast<ACharacter&>(player), count, player.getSkin());
        count++;
    }
    for (Bot& bot : this->bots) {
        if (clocky.is_running() == Clock::PAUSE)
            drawGUI(
                static_cast<ACharacter&>(bot), count, Settings::Skin::S_GREY);
        count++;
    }
    map.getEngine().initMode3D();
    map.update();
    map.drawBlocks();
    drawBomb();
    for (Player& player : this->players) {
        if (player.getLife() > 0)
            player.display();
    }
    for (Bot& bot : this->bots) {
        if (bot.getLife() > 0)
            bot.display();
    }
    map.getEngine().updateCamera();
    Engine::endMode3D();
}

Game::SceneEvent indie::Game::updateScene()
{
    int playerDead = 0;
    int botDead = 0;
    int playerIndex = 0;
    for (int i = 0; i < this->players.size(); i++) {
        players.at(i).update(getEngine().getEvent(), getEngine());
        if (players.at(i).getLife() <= 0) {
            playerDead += 1;
            playerIndex = i;
        }
    }
    for (auto& bot : this->bots) {
        bot.update(getEngine().getEvent(), getEngine());
        if (bot.getLife() <= 0) {
            botDead += 1;
        }
    }
    if (playerDead == this->players.size())
        return OPT1;
    if (botDead != this->bots.size())
        return NONE;
    if (this->players.size() == 1)
        return OPT2;
    if (playerDead == 1) {
        if (playerIndex == 1)
            return OPT2;
        return OPT3;
    }
    return NONE;
}

Map& Game::getMap()
{
    return this->map;
}

void Game::drawBomb()
{
    for (auto& player : players) {
        for (auto& bomb : player.getBombs()) {
            Engine::drawnSphere(
                {bomb.getPos().first, 1.0f, bomb.getPos().second}, 0.3, WHITE);
        }
    }
    for (auto& bot : bots) {
        for (auto& bomb : bot.getBombs()) {
            Engine::drawnSphere(
                {bomb.getPos().first, 1.0f, bomb.getPos().second}, 0.3, WHITE);
        }
    }
}
}

Clock indie::Game::getClocky()
{
    return (clocky);
}

void indie::Game::setClocky(Clock clocky_tmp)
{
    clocky = clocky_tmp;
}