/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** PlayerBox
*/

#ifndef PLAYERBOX_HPP_
#define PLAYERBOX_HPP_

#include "Engine.hpp"

class PlayerBox
{
  public:
    enum TypeBox { PLAYER, BOT };
    PlayerBox(
        Engine& engine, std::pair<float, float> pos, float scale, TypeBox type);
    ~PlayerBox() = default;
    void addChoice(std::string& choice, float scale);
    void setPosChoice(int pos);
    void display();
    void updateBox(Event& event);
    void setDifficulty(int dif);
    [[nodiscard]] TypeBox getTypeBox() const;
    [[nodiscard]] unsigned int getChoice() const;
    std::string& getDifficultyTxt();
    [[nodiscard]] int getDifficulty() const;

  protected:
  private:
    std::vector<Button> buttons;
    std::vector<std::pair<std::string, float>> choices;
    std::pair<float, float> pos;
    int difficulty;
    float scale;
    unsigned int posChoice;
    TypeBox type;
    Engine& engine;
    std::vector<std::string> difs = {"EASY", "MEDIUM", "HARD"};
    std::string name = "PLAYER";
};

#endif /* !PLAYERBOX_HPP_ */
