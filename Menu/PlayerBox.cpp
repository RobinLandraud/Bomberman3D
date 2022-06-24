/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** PlayerBox
*/

#include "PlayerBox.hpp"

PlayerBox::PlayerBox(
    Engine& engine, std::pair<float, float> pos, float scale, TypeBox type)
    : choices({})
    , pos(pos)
    , difficulty(1)
    , scale(scale)
    , posChoice(0)
    , type(type)
    , engine(engine)
{
    std::vector<std::string> textureNames = {"prev", "next"};
    buttons.emplace_back(Button(engine.getMaterial().getTexture(textureNames.at(0)),
        {pos.first + (50 * scale), pos.second + (1000 * scale)},
        0.3));
    buttons.emplace_back(Button(engine.getMaterial().getTexture(textureNames.at(1)),
        {pos.first + (680 * scale), pos.second + (1000 * scale)},
        0.3));
}

void PlayerBox::addChoice(std::string& choice, float scale)
{
    choices.emplace_back(choice, scale);
}

void PlayerBox::setPosChoice(int pos)
{
    if (pos < 0)
        posChoice = choices.size() - 1;
    else if (pos >= choices.size())
        posChoice = 0;
    else
        posChoice = pos;
}

void PlayerBox::setDifficulty(int dif)
{
    if (dif < 0)
        difficulty = 2;
    else if (dif > 2)
        difficulty = 0;
    else
        difficulty = dif;
}

std::string& PlayerBox::getDifficultyTxt()
{
    return difs.at(difficulty);
}

int PlayerBox::getDifficulty() const
{
    return difficulty;
}

PlayerBox::TypeBox PlayerBox::getTypeBox() const
{
    return type;
}

unsigned int PlayerBox::getChoice() const
{
    return posChoice;
}

void PlayerBox::display()
{
    std::vector<std::string> textureNames = {
        "bgchar2", "table", "iconPlayerGrey"};
    engine.getMaterial().drawTexture(
        textureNames.at(0), {pos.first, pos.second}, 0, scale, WHITE);
    engine.getMaterial().drawTexture(textureNames.at(1),
        {pos.first + (scale * 50), pos.second},
        0,
        float(scale * 0.76),
        WHITE);
    Engine::drawButtons(this->buttons);
    if (type == BOT) {
        engine.getMaterial().drawTexture(textureNames.at(2),
            {pos.first + (967 * scale / 2) - (90),
                pos.second + ((1295 * scale / 2) * 4 / 5) - (90)},
            0,
            0.2,
            WHITE);
        Engine::drawText(getDifficultyTxt(),
            BLACK,
            {pos.first + (250 * scale), pos.second + (1050 * scale)},
            40);
        return;
    }
    if (posChoice < choices.size())
        engine.getMaterial().drawTexture(choices.at(posChoice).first,
            {pos.first + (967 * scale / 2)
                    - (static_cast<float>(
                           engine.getMaterial().getTexture(choices.at(posChoice).first).width)
                        / 2 * choices.at(posChoice).second),
                pos.second + ((1295 * scale / 2) * 4 / 5)
                    - (static_cast<float>(
                           engine.getMaterial().getTexture(choices.at(posChoice).first)
                               .height)
                        / 2 * choices.at(posChoice).second)},
            0,
            choices.at(posChoice).second,
            WHITE);
    Engine::drawText(name,
        BLACK,
        {pos.first + (250 * scale), pos.second + (1050 * scale)},
        40);
}

void PlayerBox::updateBox(Event& event)
{
    std::string clickSoundName = "click";
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons.at(i).getCollisionBox().isColide(
                event.getMouseInfo().pos)) {
            buttons.at(i).setZoom(1.1);
            if (event.getMouseInfo().left) {
                engine.getSFX().playSound(clickSoundName);
                if (type == PLAYER) {
                    if (i == 0)
                        setPosChoice(static_cast<int>(posChoice) - 1);
                    else if (i == 1)
                        setPosChoice(static_cast<int>(posChoice) + 1);
                } else {
                    if (i == 0)
                        setDifficulty(difficulty - 1);
                    else if (i == 1)
                        setDifficulty(difficulty + 1);
                }
            }
        } else {
            buttons.at(i).setZoom(1);
        }
    }
}