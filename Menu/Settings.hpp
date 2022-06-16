/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Settings
*/

#pragma once

#include <iostream>
#include <vector>

class Settings
{
  public:
    enum Skin { S_RED, S_BLUE, S_GREEN, S_YELLOW, S_PURPLE, S_GREY };
    enum Difficulty { EASY, MEDIUM, HARD };
    enum GameMode { TIMER, LIFE };
    Settings() = default;
    ~Settings() = default;
    int addPlayer(Skin);
    int removePlayer(unsigned int index);
    int addBot(Difficulty);
    int removeBot(unsigned int index);
    int setMusicVolume(unsigned int percent);
    int setSoundsVolume(unsigned int percent);
    int setSpeed(unsigned int speed);
    int setLifes(unsigned int lifes);
    int setTimer(unsigned int minutes);
    int setGameMode(GameMode);
    int setMap(unsigned int indexMap);
    void clearAll();
    std::vector<Skin>& getPlayers();
    std::vector<Difficulty>& getBots();
    [[nodiscard]] unsigned int getIndexMap() const;
    GameMode getMode();
    [[nodiscard]] unsigned int getLifes() const;
    [[nodiscard]] unsigned int getMinTime() const;
    [[nodiscard]] unsigned int getSpeed() const;

  protected:
  private:
    std::vector<Skin> players = {};
    std::vector<Difficulty> bots = {};
    unsigned int indexMap = 0;
    GameMode mode = LIFE;
    unsigned int lifes = 3;
    unsigned int minTime = 5;
    unsigned int speed = 1;
    unsigned int soundsVolume = 70;
    unsigned int musicVolume = 70;
};