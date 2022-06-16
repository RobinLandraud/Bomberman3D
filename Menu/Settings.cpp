/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Settings
*/

#include "Settings.hpp"

int Settings::addPlayer(Skin color)
{
    if ((bots.size() + players.size()) >= 4 || players.size() >= 2 || color < 0
        || color >= 5)
        return (-1);
    players.push_back(color);
    return (0);
}

int Settings::removePlayer(unsigned int index)
{
    if (index >= players.size())
        return (-1);
    players.erase(players.begin() + index);
    return (0);
}

int Settings::addBot(Difficulty difficulty)
{
    if ((bots.size() + players.size()) >= 4 || difficulty < 0
        || difficulty >= 3)
        return (-1);
    bots.push_back(difficulty);
    return (0);
}

int Settings::removeBot(unsigned int index)
{
    if (index >= bots.size())
        return (-1);
    bots.erase(bots.begin() + index);
    return (0);
}

int Settings::setMusicVolume(unsigned int percent)
{
    if (percent > 100)
        return (-1);
    musicVolume = percent;
    return (0);
}

int Settings::setSoundsVolume(unsigned int percent)
{
    if (percent > 100)
        return (-1);
    soundsVolume = percent;
    return (0);
}

int Settings::setSpeed(unsigned int speed)
{
    if (speed > 10)
        return (-1);
    this->speed = speed;
    return (0);
}

int Settings::setLifes(unsigned int lifes)
{
    if (lifes > 10)
        return (-1);
    this->lifes = lifes;
    return (0);
}

int Settings::setTimer(unsigned int minutes)
{
    if (minutes > 30)
        return (-1);
    minTime = minutes;
    return (0);
}

int Settings::setGameMode(GameMode mode)
{
    this->mode = mode;
    return (0);
}

int Settings::setMap(unsigned int indexMap)
{
    if (indexMap > 3)
        return (-1);
    this->indexMap = indexMap;
    return (0);
}

void Settings::clearAll()
{
    this->players.clear();
    this->bots.clear();
    players = {};
    bots = {};
    indexMap = 0;
    mode = LIFE;
    lifes = 3;
    minTime = 5;
    speed = 5;
    soundsVolume = 70;
    musicVolume = 70;
}

std::vector<Settings::Skin>& Settings::getPlayers()
{
    return players;
}

std::vector<Settings::Difficulty>& Settings::getBots()
{
    return this->bots;
}

unsigned int Settings::getIndexMap() const
{
    return indexMap;
}

Settings::GameMode Settings::getMode()
{
    return mode;
}

unsigned int Settings::getLifes() const
{
    return lifes;
}

unsigned int Settings::getMinTime() const
{
    return minTime;
}

unsigned int Settings::getSpeed() const
{
    return speed;
}