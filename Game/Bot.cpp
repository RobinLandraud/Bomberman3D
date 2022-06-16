/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Bot
*/

#include "Bot.hpp"

#include <utility>

#include "Settings.hpp"

Bot::Bot(Map& map,
    Settings::Difficulty diff,
    std::string& skinAsset,
    std::string playerIqm,
    std::vector<std::string> animIqm,
    std::pair<float, float> pos,
    float speed,
    Engine& engine)
    : ACharacter(map, pos, speed)
    , playerIqm(playerIqm)
    , animIqm(animIqm)
    , engine(engine)
    , model(Model3D(engine.getTexture(skinAsset), playerIqm, animIqm, 0.01f))
    , difficulty(diff)
{
    int x = 0;
    int y = 0;
    if (std::fabs(std::ceil(pos.first) - pos.first) < 0.001f)
        x = std::ceil(pos.first);
    else
        x = std::floor(pos.first);
    if (std::fabs(std::ceil(pos.second) - pos.second) < 0.001f)
        y = std::ceil(pos.second);
    else
        y = std::floor(pos.second);
    oldPos = {x, y};
}

void Bot::setAxe(std::tuple<float, float, float, float> newAxe)
{
    axe = newAxe;
}

std::tuple<float, float, float, float> Bot::getAxe() const
{
    return axe;
}

Model3D& Bot::getModel()
{
    return model;
}

void Bot::display()
{
    Engine::drawModel(model,
        {this->pos.first - 0.15f, this->pos.second - 0.15f},
        {std::get<0>(getAxe()), std::get<1>(getAxe()), std::get<2>(getAxe())},
        std::get<3>(getAxe()));
}

void Bot::respawn(bool isDead, Engine& engine)
{
    std::string deathSoundName = "ben_ugh";
    if (isDead && !this->getIsInvisible()) {
        this->nextDirs = {};
        this->setIsInvisible(true);
        this->pos = this->spawn;
        this->collideBox.setPos(pos);
        engine.getAudioEngine().playSound(deathSoundName);
        life--;
    }
}

std::pair<float, float> Bot::getNextPos()
{
    std::pair<float, float> nextPos = pos;
    setNextDirs();
    if (nextDirs.empty()) {
        getModel().setAnimIndex(1);
        this->model.setAnimFrameCounter(this->model.getAnimFrameCounter() + 1);
        return this->pos;
    }
    switch (nextDirs.at(0)) {
        case UP:
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({0.0f, 1.0f, 1.0f, 180.0f});
            direction = UP;
            nextPos = {
                this->pos.first, this->pos.second - (0.01 * this->speed)};
            break;
        case DOWN:
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, 0.0f, 0.0f, -90.0f});
            direction = DOWN;
            nextPos = {
                this->pos.first, this->pos.second + (0.01 * this->speed)};
            break;
        case LEFT:
            nextPos = {
                this->pos.first - (0.01 * this->speed), this->pos.second};
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, 1.0f, 1.0f, 240.0f});
            direction = LEFT;
            break;
        case RIGHT:
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            setAxe({1.0f, -1.0f, -1.0f, 240.0f});
            direction = RIGHT;
            nextPos = {
                this->pos.first + (0.01 * this->speed), this->pos.second};
            break;
        default:
            getModel().setAnimIndex(1);
            this->model.setAnimFrameCounter(
                this->model.getAnimFrameCounter() + 1);
            nextPos = this->pos;
            break;
    }
    return nextPos;
}

int Bot::preciseFloor(float flo)
{
    int return_int = 0;
    if (std::fabs(std::ceil(flo) - flo) < 0.001f)
        return_int = std::ceil(flo);
    else
        return_int = std::floor(flo);
    return return_int;
}

std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
Bot::getBlockAroundMe(int length)
{
    int x = preciseFloor(pos.first);
    int y = preciseFloor(pos.second);
    int startX = x - length;
    int startY = y - length;
    if (startX < 0)
        startX = 0;
    if (startY < 0)
        startY = 0;
    std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>>
        axeY = {};
    for (; startY < (y + length + 1) && startY < map.getBlocks().size();
         startY++) {
        std::vector<std::pair<std::pair<float, float>, BlockType>> axeX = {};
        for (int tempX = startX; tempX < (x + length + 1)
                                 && tempX < map.getBlocks().at(startY).size();
             tempX++) {
            axeX.emplace_back(map.getBlocks().at(startY).at(tempX).getPos(),
                map.getBlocks().at(startY).at(tempX).getType());
        }
        axeY.push_back(axeX);
    }
    return axeY;
}

std::vector<ACharacter::Direction> Bot::getPath(std::pair<int, int> pos,
    int tempX,
    int tempY,
    std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>> tab,
    std::vector<Direction> possibleNextDirs,
    Direction prevMove)
{
    if (pos.first != tempX && pos.second != tempY)
        return possibleNextDirs;
    if (abs(pos.first - tempX) > bombStrength
        || abs(pos.second - tempY) > bombStrength)
        return possibleNextDirs;
    std::vector<Direction> dirCopy = possibleNextDirs;
    if (prevMove != LEFT && tempX + 1 < tab.at(tempY).size()
        && tab.at(tempY).at(tempX + 1).second == AIR) {
        possibleNextDirs.push_back(RIGHT);
        possibleNextDirs =
            getPath(pos, tempX + 1, tempY, tab, possibleNextDirs, RIGHT);
        if (!possibleNextDirs.empty())
            return possibleNextDirs;
        possibleNextDirs = dirCopy;
    }
    if (prevMove != RIGHT && tempX - 1 >= 0
        && tab.at(tempY).at(tempX - 1).second == AIR) {
        possibleNextDirs.push_back(LEFT);
        possibleNextDirs =
            getPath(pos, tempX - 1, tempY, tab, possibleNextDirs, LEFT);
        if (!possibleNextDirs.empty())
            return possibleNextDirs;
        possibleNextDirs = dirCopy;
    }
    if (prevMove != UP && tempY + 1 < tab.size()
        && tab.at(tempY + 1).at(tempX).second == AIR) {
        possibleNextDirs.push_back(DOWN);
        possibleNextDirs =
            getPath(pos, tempX, tempY + 1, tab, possibleNextDirs, DOWN);
        if (!possibleNextDirs.empty())
            return possibleNextDirs;
        possibleNextDirs = dirCopy;
    }
    if (prevMove != DOWN && tempY - 1 >= 0
        && tab.at(tempY - 1).at(tempX).second == AIR) {
        possibleNextDirs.push_back(UP);
        possibleNextDirs =
            getPath(pos, tempX, tempY - 1, tab, possibleNextDirs, UP);
        if (!possibleNextDirs.empty())
            return possibleNextDirs;
        possibleNextDirs = dirCopy;
    }
    return {};
}

bool Bot::poseBomb(
    std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>> tab,
    std::pair<int, int> playerPos)
{
    std::string explosionSoundName = "bomb_explosion";
    std::vector<Direction> possibleNextDirs = {};
    if (!nextDirs.empty() || rand() % 3 != 0)
        return false;
    possibleNextDirs = getPath(playerPos,
        playerPos.first,
        playerPos.second,
        std::move(tab),
        possibleNextDirs,
        NONE);
    if (!possibleNextDirs.empty()) {
        if (dropBomb() != 0)
            return false;
        engine.getAudioEngine().playSound(explosionSoundName);
        this->nextDirs = possibleNextDirs;
        return true;
    }
    return false;
}

void Bot::setNextDirs()
{
    int x = 0;
    int y = 0;
    int xw = 0;
    int yh = 0;
    std::vector<Direction> possibleNextDirs = {};
    int nextDirIndex = 0;
    int sizeTab = 3;

    if (difficulty == Settings::Difficulty::HARD)
        sizeTab = 5;
    x = preciseFloor(pos.first);
    y = preciseFloor(pos.second);
    xw = preciseFloor(pos.first + this->collideBox.w);
    yh = preciseFloor(pos.second + this->collideBox.h);

    if (!nextDirs.empty()) {
        if ((oldPos.first != x || oldPos.second != y)
            && (oldPos.first != xw || oldPos.second != yh)) {
            oldPos = {x, y};
            nextDirs.erase(nextDirs.begin());
        }
        if (!nextDirs.empty())
            return;
    }
    if (nbBomb < maxBomb)
        return;
    auto tab = getBlockAroundMe(sizeTab);
    std::pair<int, int> playerPos = Bot::getCurrentPosInTab(tab, {x, y});
    if (difficulty == Settings::Difficulty::EASY || !poseBomb(tab, playerPos)) {
        if (tab.at(playerPos.second - 1).at(playerPos.first).second == AIR)
            possibleNextDirs.push_back(UP);
        if (tab.at(playerPos.second + 1).at(playerPos.first).second == AIR)
            possibleNextDirs.push_back(DOWN);
        if (tab.at(playerPos.second).at(playerPos.first + 1).second == AIR)
            possibleNextDirs.push_back(RIGHT);
        if (tab.at(playerPos.second).at(playerPos.first - 1).second == AIR)
            possibleNextDirs.push_back(LEFT);
        if (!possibleNextDirs.empty()) {
            nextDirIndex = static_cast<int>(rand() % possibleNextDirs.size());
            nextDirs.push_back(possibleNextDirs.at(nextDirIndex));
        }
    }
}

std::pair<int, int> Bot::getCurrentPosInTab(
    std::vector<std::vector<std::pair<std::pair<float, float>, BlockType>>> tab,
    std::pair<int, int> currentPos)
{
    int intY = 0;
    int intX = 0;
    for (int y = 0; y < tab.size(); y++) {
        intY = preciseFloor(tab.at(y).at(0).first.second);
        if (intY == currentPos.second)
            for (int x = 0; x < tab.at(y).size(); x++) {
                intX = preciseFloor(tab.at(y).at(x).first.first);
                if (intX == currentPos.first)
                    return {x, y};
            }
    }
    return {1, 1};
}