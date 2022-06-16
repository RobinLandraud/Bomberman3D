/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** AScene2D
*/

#include "AScene2D.hpp"

#include <utility>
#include <vector>

#include "Engine.hpp"

indie::AScene2D::AScene2D(Engine& engine, Settings& settings)
    : Ascene(engine, settings)
{
    this->headerButtons.insert({std::string("prev"),
        Button(engine.getTextures().at(std::string("prev")), {150, 35}, 0.6)});
    this->headerButtons.insert({std::string("ok"),
        Button(engine.getTextures().at(std::string("ok")), {1650, 35}, 0.6)});
}

std::map<std::string, Button>& indie::AScene2D::getButtonsTab()
{
    return this->buttons;
}

std::map<std::string, Button>& indie::AScene2D::getHeaderButtonsTab()
{
    return this->headerButtons;
}

void indie::AScene2D::displayHeader()
{
    std::vector<std::string> textureNames = {"header", "bm-icon"};
    getEngine().drawTexture(textureNames.at(0), {0, 0}, 0, 1.25, WHITE);
    getEngine().drawTexture(textureNames.at(1), {850, 20}, 0, 0.4, WHITE);
    Engine::drawButtons(this->headerButtons);
}

indie::ChooseCharScene::ChooseCharScene(
    Engine& engine, Settings& settings, TypeMode mode)
    : indie::AScene2D(engine, settings)
{
    std::vector<std::string> textureNames = {"life", "dot1", "dot2"};
    std::vector<std::string> iconChoices = {"iconPlayerRed",
        "iconPlayerBlue",
        "iconPlayerGreen",
        "iconPlayerYellow",
        "iconPlayerPurple"};
    PlayerBox::TypeBox type = PlayerBox::TypeBox::BOT;
    if (mode == MULTI)
        type = PlayerBox::TypeBox::PLAYER;
    getButtonsTab().insert({textureNames.at(0),
        Button({engine.getTexture(textureNames.at(1)), 1},
            {engine.getTexture(textureNames.at(2)), 1},
            {700, 900},
            WHITE,
            false)});
    getButtonsTab().insert({std::string("time"),
        Button({engine.getTexture(textureNames.at(1)), 1},
            {engine.getTexture(textureNames.at(2)), 1},
            {1100, 900},
            WHITE,
            true)});
    boxes.emplace_back(
        PlayerBox(engine, {150, 300}, 0.4, PlayerBox::TypeBox::PLAYER));
    boxes.at(0).addChoice(iconChoices.at(0), 0.2);
    boxes.at(0).addChoice(iconChoices.at(1), 0.2);
    boxes.at(0).addChoice(iconChoices.at(2), 0.2);
    boxes.at(0).addChoice(iconChoices.at(3), 0.2);
    boxes.at(0).addChoice(iconChoices.at(4), 0.2);
    boxes.emplace_back(PlayerBox(engine, {550, 300}, 0.4, type));
    boxes.at(1).addChoice(iconChoices.at(0), 0.2);
    boxes.at(1).addChoice(iconChoices.at(1), 0.2);
    boxes.at(1).addChoice(iconChoices.at(2), 0.2);
    boxes.at(1).addChoice(iconChoices.at(3), 0.2);
    boxes.at(1).addChoice(iconChoices.at(4), 0.2);
    boxes.emplace_back(
        PlayerBox(engine, {950, 300}, 0.4, PlayerBox::TypeBox::BOT));
    boxes.emplace_back(
        PlayerBox(engine, {1350, 300}, 0.4, PlayerBox::TypeBox::BOT));
}

void indie::ChooseCharScene::displayBoxes()
{
    for (PlayerBox& box : this->boxes) {
        box.display();
    }
}

void indie::ChooseCharScene::displayScene()
{
    std::vector<std::string> textureNames = {"sky-bg", "heart", "clock"};
    getEngine().drawTexture(textureNames.at(0), {0, 0}, 0, 1, WHITE);
    displayHeader();
    displayBoxes();
    getEngine().drawTexture(textureNames.at(1), {800, 900}, 0, 0.5, WHITE);
    getEngine().drawTexture(textureNames.at(2), {1000, 900}, 0, 0.9, WHITE);
    Engine::drawButtons(getButtonsTab());
}

void indie::ChooseCharScene::saveSettings()
{
    getSettings().clearAll();
    for (PlayerBox& box : this->boxes) {
        if (box.getTypeBox() == PlayerBox::TypeBox::PLAYER) {
            getSettings().addPlayer(
                static_cast<Settings::Skin>(box.getChoice()));
        } else if (box.getTypeBox() == PlayerBox::TypeBox::BOT) {
            getSettings().addBot(
                static_cast<Settings::Difficulty>(box.getDifficulty()));
        }
    }
    if (this->getButtonsTab().at("time").is_activated()) {
        getSettings().setGameMode(Settings::GameMode::TIMER);
    } else {
        getSettings().setGameMode(Settings::GameMode::LIFE);
    }
}

indie::AScene2D::SceneEvent indie::ChooseCharScene::updateScene()
{
    std::string clickSoundName = "click";
    Event& event = getEngine().getEvent();
    for (PlayerBox& box : boxes) {
        box.updateBox(getEngine().getEvent());
    }
    if (event.getMouseInfo().left
        && getButtonsTab().at("time").getCollisionBox().isColide(
            event.getMouseInfo().pos)
        && !getButtonsTab().at("time").is_activated()) {
        getButtonsTab().at("time").click();
        if (getButtonsTab().at("life").is_activated()) {
            engine.getAudioEngine().playSound(clickSoundName);
            getButtonsTab().at("life").click();
        }
    }
    if (event.getMouseInfo().left
        && getButtonsTab().at("life").getCollisionBox().isColide(
            event.getMouseInfo().pos)
        && !getButtonsTab().at("life").is_activated()) {
        getButtonsTab().at("life").click();
        if (getButtonsTab().at("time").is_activated()) {
            engine.getAudioEngine().playSound(clickSoundName);
            getButtonsTab().at("time").click();
        }
    }
    if (event.getMouseInfo().left
        && getHeaderButtonsTab().at("ok").getCollisionBox().isColide(
            event.getMouseInfo().pos)) {
        saveSettings();
        engine.getAudioEngine().playSound(clickSoundName);
        return NEXT;
    }
    if (event.getMouseInfo().left
        && getHeaderButtonsTab().at("prev").getCollisionBox().isColide(
            event.getMouseInfo().pos)) {
        getSettings().clearAll();
        engine.getAudioEngine().playSound(clickSoundName);
        return PREV;
    }
    return NONE;
}

indie::MainMenu::MainMenu(Engine& engine, Settings& settings)
    : AScene2D(engine, settings)
{
    this->getButtonsTab().insert({std::string("solo"),
        Button(
            engine.getTextures().at(std::string("button1")), {400, 500}, 2)});
    this->getButtonsTab().insert({std::string("multi"),
        Button(
            engine.getTextures().at(std::string("button1")), {400, 700}, 2)});
    this->getButtonsTab().insert({std::string("continue"),
        Button(
            engine.getTextures().at(std::string("button1")), {1100, 500}, 2)});
    this->getButtonsTab().insert({std::string("quit"),
        Button(
            engine.getTextures().at(std::string("button1")), {1100, 700}, 2)});
}

indie::AScene2D::SceneEvent indie::MainMenu::updateScene()
{
    std::string clickSoundName = "click";
    for (auto& button : getButtonsTab()) {
        if (button.second.getCollisionBox().isColide(
                getEngine().getEvent().getMouseInfo().pos)) {
            button.second.setZoom(1.05);
            if (getEngine().getEvent().getMouseInfo().left) {
                if (button.first.compare("solo") == 0) {
                    engine.getAudioEngine().playSound(clickSoundName);
                    return indie::AScene2D::SceneEvent::OPT1;
                }
                if (button.first.compare("multi") == 0) {
                    engine.getAudioEngine().playSound(clickSoundName);
                    return indie::AScene2D::SceneEvent::OPT2;
                }
                if (button.first.compare("continue") == 0) {
                    engine.getAudioEngine().playSound(clickSoundName);
                    return indie::AScene2D::SceneEvent::OPT3;
                }
                if (button.first.compare("quit") == 0) {
                    engine.getAudioEngine().playSound(clickSoundName);
                    return indie::AScene2D::SceneEvent::CLOSE;
                }
            }
        } else {
            button.second.setZoom(1);
        }
    }
    return SceneEvent::NONE;
}

void indie::MainMenu::displayScene()
{
    std::vector<std::string> textureNames = {"sky-bg", "header", "bm-icon"};
    getEngine().drawTexture(textureNames.at(0), {0, 0}, 0, 1, WHITE);
    getEngine().drawTexture(textureNames.at(1), {0, 0}, 0, 1.25, WHITE);
    getEngine().drawTexture(textureNames.at(2), {800, 20}, 0, 0.6, WHITE);
    Engine::drawButtons(getButtonsTab());
    Engine::drawText(buttonName.at(0), WHITE, {450, 550}, 40);
    Engine::drawText(buttonName.at(1), WHITE, {450, 750}, 40);
    Engine::drawText(buttonName.at(2), WHITE, {1150, 550}, 40);
    Engine::drawText(buttonName.at(3), WHITE, {1150, 750}, 40);
}

indie::EndScene::EndScene(Engine& engine, Settings& settings)
    : AScene2D(engine, settings)
{
}

indie::AScene2D::SceneEvent indie::EndScene::updateScene()
{
    Event& event = getEngine().getEvent();
    if (event.getMouseInfo().left
        && (getHeaderButtonsTab().at("ok").getCollisionBox().isColide(
                event.getMouseInfo().pos)
            || getHeaderButtonsTab().at("prev").getCollisionBox().isColide(
                event.getMouseInfo().pos))) {
        return indie::AScene2D::SceneEvent::CLOSE;
    }
    return indie::AScene2D::SceneEvent::NONE;
}

void indie::EndScene::displayScene()
{
    std::string textureName = "sky-bg";
    getEngine().drawTexture(textureName, {0, 0}, 0, 1, WHITE);
    displayHeader();
    switch (color) {
        case Settings::Skin::S_RED:
            Engine::drawText(message, RED, {600, 600}, 100);
            break;
        default: Engine::drawText(message, BLUE, {600, 600}, 100); break;
    }
}

void indie::EndScene::setMessage(std::string message, Settings::Skin color)
{
    this->message = std::move(message);
    this->color = color;
}
