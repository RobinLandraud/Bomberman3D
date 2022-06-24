/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Player
*/

#include "Player.hpp"

#include "Bonuses.hpp"
#include "Map.hpp"

Player::Player(Map& map,
    std::vector<KeyList> binding,
    Settings::Skin skin,
    std::string& skinAsset,
    std::string playerIqm,
    std::vector<std::string> animIqm,
    std::pair<float, float> pos,
    float speed,
    Engine& engine)
    : ACharacter(map, pos, speed)
    , skin(skin)
    , playerIqm(playerIqm)
    , animIqm(animIqm)
    , binding(std::move(binding))
    , engine(engine)
    , model(Model3D(engine.getTexture(skinAsset), playerIqm, animIqm, 0.01f))
{
}

std::pair<float, float> Player::getNextPos()
{
    std::string explosionSoundName = "bomb_explosion";
    std::pair<float, float> nextPos = pos;
    for (KeyList key : engine.getEvent().getKeysPressed()) {
        if (key == this->binding.at(UP)) {
            nextPos = {
                this->pos.first, this->pos.second - (0.01 * this->speed)};
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({0.0f, 1.0f, 1.0f, 180.0f});
            direction = UP;
        } else if (key == this->binding.at(DOWN)) {
            nextPos = {
                this->pos.first, this->pos.second + (0.01 * this->speed)};
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, 0.0f, 0.0f, -90.0f});
            direction = DOWN;
        } else if (key == this->binding.at(LEFT)) {
            nextPos = {
                this->pos.first - (0.01 * this->speed), this->pos.second};
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, 1.0f, 1.0f, 240.0f});
            direction = LEFT;
        } else if (key == this->binding.at(RIGHT)) {
            nextPos = {
                this->pos.first + (0.01 * this->speed), this->pos.second};
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, -1.0f, -1.0f, 240.0f});
            direction = RIGHT;
        } else if (key == this->binding.at(BOMB)) {
            if (dropBomb() == 0)
                engine.getSFX().playSound(explosionSoundName);
        }
    }
    if (direction == NONE) {
        getModel().setAnimIndex(1);
        this->model.setAnimFrameCounter(this->model.getAnimFrameCounter() + 1);
    }
    return nextPos;
}

std::tuple<float, float, float, float> Player::getAxe() const
{
    return axe;
}

void Player::setAxe(std::tuple<float, float, float, float> newAxe)
{
    axe = newAxe;
}

Model3D& Player::getModel()
{
    return this->model;
}

Settings::Skin Player::getSkin() const
{
    return this->skin;
}

void Player::display()
{
    Engine::drawModel(model,
        {this->pos.first - 0.15f, this->pos.second - 0.15f},
        {std::get<0>(getAxe()), std::get<1>(getAxe()), std::get<2>(getAxe())},
        std::get<3>(getAxe()));
}