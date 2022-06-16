/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** AScene2D
*/

#pragma once
#include "AScene.hpp"

namespace indie
{
class AScene2D : public Ascene
{
  public:
    explicit AScene2D(Engine&, Settings&);
    ~AScene2D() noexcept = default;

    void displayHeader();
    std::map<std::string, Button>& getButtonsTab();
    std::map<std::string, Button>& getHeaderButtonsTab();

  protected:
  private:
    std::map<std::string, Button> buttons;
    std::map<std::string, Button> headerButtons;
};

class ChooseCharScene : public AScene2D
{
  public:
    enum TypeMode { SOLO, MULTI };
    explicit ChooseCharScene(Engine&, Settings&, TypeMode);
    ~ChooseCharScene() = default;
    void displayBoxes();
    SceneEvent updateScene() override;
    void displayScene() override;
    void saveSettings() override;

  protected:
  private:
    std::vector<PlayerBox> boxes;
};

class MainMenu : public AScene2D
{
  public:
    explicit MainMenu(Engine&, Settings&);
    ~MainMenu() = default;
    SceneEvent updateScene() override;
    void displayScene() override;

  protected:
  private:
    std::vector<std::string> buttonName = {"SOLO", "MULTI", "CONTINUE", "QUIT"};
};

class EndScene : public AScene2D
{
  public:
    explicit EndScene(Engine&, Settings&);
    ~EndScene() = default;
    SceneEvent updateScene() override;
    void displayScene() override;
    void setMessage(std::string message, Settings::Skin color);

  protected:
  private:
    std::string message = "!! YOU WIN !!";
    Settings::Skin color = Settings::Skin::S_BLUE;
};
}