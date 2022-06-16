/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** AScene
*/

#pragma once
#include "Engine.hpp"
#include "PlayerBox.hpp"
#include "Settings.hpp"

namespace indie
{
class Ascene
{
  public:
    enum SceneEvent { NONE, CLOSE, NEXT, PREV, OPT1, OPT2, OPT3, OPT4 };
    explicit Ascene(Engine&, Settings&) noexcept;
    Ascene(Ascene const& b) noexcept = default;
    Ascene(Ascene&& b) noexcept = default;
    ~Ascene() noexcept = default;

    Ascene& operator=(Ascene const& rhs) noexcept = default;
    Ascene& operator=(Ascene&& rhs) noexcept = default;

    virtual void displayScene();
    virtual void saveSettings();
    virtual SceneEvent updateScene();
    Engine& getEngine();
    Settings& getSettings();

  protected:
    Settings& settings;
    Engine& engine;

  private:
};
}