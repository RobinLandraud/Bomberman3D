/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** AScene
*/

#include "AScene.hpp"

indie::Ascene::Ascene(Engine& engine, Settings& settings) noexcept
    : engine(engine)
    , settings(settings)
{
}

Engine& indie::Ascene::getEngine()
{
    return engine;
}

Settings& indie::Ascene::getSettings()
{
    return settings;
}

void indie::Ascene::displayScene()
{
}

void indie::Ascene::saveSettings()
{
}

indie::Ascene::SceneEvent indie::Ascene::updateScene()
{
    return Ascene::SceneEvent::NONE;
}
