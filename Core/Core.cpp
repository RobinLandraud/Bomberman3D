/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** core
*/

#include "Core.hpp"

#include "Engine.hpp"

indie::Core::Core()
    : engine(Engine(screenWidth, screenHeight))
    , charSceneSolo(engine, settings, ChooseCharScene::TypeMode::SOLO)
    , charSceneMulti(engine, settings, ChooseCharScene::TypeMode::MULTI)
    , game(engine, settings)
    , mainMenu(engine, settings)
    , endScene(engine, settings)
    , clock(0.04)
    , currentScreen(LOGO)
{
}

void indie::Core::resetGame()
{
    this->game.resetGame();
}

void indie::Core::drawMain()
{
    Ascene::SceneEvent eventScene = mainMenu.updateScene();
    if (eventScene == Ascene::SceneEvent::OPT1
        || eventScene == Ascene::SceneEvent::OPT3)
        setCurrentScene(SOLO);
    else if (eventScene == Ascene::SceneEvent::OPT2)
        setCurrentScene(MULTI);
    else if (eventScene == Ascene::SceneEvent::CLOSE)
        this->needToClose = true;
    mainMenu.displayScene();
}

void indie::Core::drawSolo()
{
    std::string menuSoundName = "main_menu_bb";
    Ascene::SceneEvent eventScene = charSceneSolo.updateScene();
    if (eventScene == Ascene::SceneEvent::PREV)
        setCurrentScene(MAIN);
    else if (eventScene == Ascene::SceneEvent::NEXT) {
        game.getClocky().reset();
        setCurrentScene(GAME);
        game.launchGame();
        game.getEngine().getSFX().pauseSound(menuSoundName);
        game.getEngine().getSFX().playSound(
            game.getCurrentSongString());
    }
    charSceneSolo.displayScene();
}

void indie::Core::drawMulti()
{
    std::string menuSoundName = "main_menu_bb";
    Ascene::SceneEvent eventScene = charSceneMulti.updateScene();
    if (eventScene == Ascene::SceneEvent::PREV)
        setCurrentScene(MAIN);
    else if (eventScene == Ascene::SceneEvent::NEXT) {
        game.getClocky().reset();
        setCurrentScene(GAME);
        game.launchGame();
        game.getEngine().getSFX().pauseSound(menuSoundName);
        game.getEngine().getSFX().playSound(
            game.getCurrentSongString());
    }
    charSceneMulti.displayScene();
}

void indie::Core::drawGame()
{
    Ascene::SceneEvent eventScene = Ascene::SceneEvent::NONE;
    if (clock.loop() && game.getClocky().is_running() == Clock::PAUSE) {
        eventScene = game.updateScene();
    }
    if (eventScene != Ascene::SceneEvent::NONE) {
        if (eventScene == Ascene::SceneEvent::OPT1)
            endScene.setMessage("!  YOU LOSE  !", Settings::Skin::S_RED);
        if (eventScene == Ascene::SceneEvent::OPT2)
            endScene.setMessage("!PLAYER 1 WIN!", Settings::Skin::S_BLUE);
        if (eventScene == Ascene::SceneEvent::OPT3)
            endScene.setMessage("!PLAYER 2 WIN!", Settings::Skin::S_BLUE);
        setCurrentScene(END);
    }
    game.displayScene();
}

void indie::Core::drawEnd()
{
    Ascene::SceneEvent eventScene = endScene.updateScene();
    if (eventScene == Ascene::SceneEvent::CLOSE) {
        resetGame();
        setCurrentScene(MAIN);
    }
    endScene.displayScene();
}

void indie::Core::drawScene()
{
    ClearBackground(RAYWHITE);
    Ascene::SceneEvent eventScene = Ascene::SceneEvent::NONE;
    switch (currentScreen) {
        case LOGO:
        case MAIN: drawMain(); break;
        case SOLO: drawSolo(); break;
        case MULTI: drawMulti(); break;
        case GAME: drawGame(); break;
        case END:
        default: drawEnd(); break;
    }
}

void indie::Core::setCurrentScene(GameScene next)
{
    currentScreen = next;
}

void indie::Core::mainLoop()
{
    while (!Engine::windowShouldClose() && !this->needToClose) {
        Engine::beginDraw();
        Engine::clearBackground();
        getEngine().getEvent().updateEvents();
        drawScene();
        Engine::endDraw();
    }
    Engine::stopWindowDisplay();
}

Engine& indie::Core::getEngine()
{
    return engine;
}