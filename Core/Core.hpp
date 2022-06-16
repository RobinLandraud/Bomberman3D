/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** core
*/

#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#include "AScene2D.hpp"
#include "AudioEngine.hpp"
#include "Engine.hpp"
#include "Game.hpp"
#include "Settings.hpp"

namespace indie
{
class Core
{
  public:
    enum GameScene { LOGO = 0, MAIN, SOLO, MULTI, GAME, PAUSE, END };
    Core();
    ~Core() = default;
    void drawScene();
    void mainLoop();
    void setCurrentScene(GameScene);
    Engine& getEngine();
    void resetGame();
    void drawMain();
    void drawSolo();
    void drawMulti();
    void drawGame();
    void drawEnd();

  protected:
  private:
    int screenWidth = 1920;
    int screenHeight = 1080;
    GameScene currentScreen;
    Engine engine;
    Settings settings;
    std::map<GameScene, AScene2D> scenes;
    ChooseCharScene charSceneSolo;
    ChooseCharScene charSceneMulti;
    EndScene endScene;
    Game game;
    MainMenu mainMenu;
    Clock clock;
    bool needToClose = false;
};
}