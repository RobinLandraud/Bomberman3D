/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Map
*/

#include "Map.hpp"

#include <cmath>

#include "Bonuses.hpp"

Map::Map(Engine& engine)
    : engine(engine)
{
    srand(time(nullptr));
}

void Map::update()
{
    for (std::vector<Block>& listBlock : this->blocks) {
        for (Block& block : listBlock) {
            if (block.getType() != EXPLODE)
                continue;
            block.updateBlock();
        }
    }
}

void Map::parseMap(std::string& path)
{
    std::fstream newfile;
    int y = 0;
    std::string line;
    unsigned int pos = path.find_last_of('.');
    blocks = {};
    spawns = {};
    bonuses = {};
    if (!std::filesystem::exists(path))
        return;
    if (path.substr(pos + 1).compare("txt") != 0)
        return;
    newfile.open(path, std::ios::in);
    if (!newfile.is_open())
        return;
    line.clear();
    while (getline(newfile, line)) {
        this->blocks.emplace_back();
        for (int x = 0; x < line.size(); x++) {
            switch (line.at(x)) {
                case '#':
                    this->blocks.at(y).push_back(
                        Block({float(x) * sizeBlock, float(y) * sizeBlock},
                            BlockType::OBSTACLE));
                    break;
                case '$':
                    if (rand() % 5 != 4)
                        this->blocks.at(y).push_back(
                            Block({float(x) * sizeBlock, float(y) * sizeBlock},
                                BlockType::BOX));
                    else
                        this->blocks.at(y).push_back(
                            Block({float(x) * sizeBlock, float(y) * sizeBlock},
                                BlockType::AIR));
                    break;
                case ' ':
                    this->blocks.at(y).push_back(
                        Block({float(x) * sizeBlock, float(y) * sizeBlock},
                            BlockType::AIR));
                    break;
                case 'P':
                    this->blocks.at(y).push_back(
                        Block({float(x) * sizeBlock, float(y) * sizeBlock},
                            BlockType::AIR));
                    this->spawns.emplace_back(
                        float(x) * sizeBlock, float(y) * sizeBlock);
                    break;
            }
        }
        y += 1;
    }
    newfile.close();
}

void Map::fillMap()
{
}

Block& Map::getBlock(std::pair<float, float> /*unused*/)
{
    return this->blocks.at(0).at(0);
}

Engine& Map::getEngine()
{
    return engine;
}

void Map::giveMeWhatExplode(int strength, std::pair<float, float> pos)
{
    int x = 0;
    int y = 0;
    float centerX = pos.first + 0.3f;
    float centerY = pos.second + 0.3f;
    if (std::fabs(std::ceil(centerX) - centerX) < 0.001f)
        x = std::ceil(centerX);
    else
        x = std::floor(centerX);
    if (std::fabs(std::ceil(centerY) - centerY) < 0.001f)
        y = std::ceil(centerY);
    else
        y = std::floor(centerY);
    if (blocks.at(y).at(x).getType() != OBSTACLE)
        blocks.at(y).at(x).setType(EXPLODE);
    blocks.at(y).at(x).startClock();
    for (int i = 0; i < strength && x - (i + 1) >= 0; i++) {
        if (blocks.at(y).at(x - (i + 1)).getType() == AIR
            || blocks.at(y).at(x - (i + 1)).getType() == EXPLODE) {
            blocks.at(y).at(x - (i + 1)).setType(EXPLODE);
            blocks.at(y).at(x - (i + 1)).startClock();
            continue;
        }
        if (blocks.at(y).at(x - (i + 1)).getType() == BOX) {
            blocks.at(y).at(x - (i + 1)).setType(EXPLODE);
            blocks.at(y).at(x - (i + 1)).startClock();
            addBonuses({x - (i + 1) + 0.1, y + 0.1});
        }
        break;
    }
    for (int i = 0; i < strength && x + (i + 1) < blocks.at(y).size(); i++) {
        if (blocks.at(y).at(x + (i + 1)).getType() == AIR
            || blocks.at(y).at(x + (i + 1)).getType() == EXPLODE) {
            blocks.at(y).at(x + (i + 1)).setType(EXPLODE);
            blocks.at(y).at(x + (i + 1)).startClock();
            continue;
        }
        if (blocks.at(y).at(x + (i + 1)).getType() == BOX) {
            blocks.at(y).at(x + (i + 1)).setType(EXPLODE);
            blocks.at(y).at(x + (i + 1)).startClock();
            addBonuses({x + (i + 1) + 0.1, y + 0.1});
        }
        break;
    }
    for (int i = 0; i < strength && y + (i + 1) < blocks.size(); i++) {
        if (blocks.at(y + (i + 1)).at(x).getType() == AIR
            || blocks.at(y + (i + 1)).at(x).getType() == EXPLODE) {
            blocks.at(y + (i + 1)).at(x).setType(EXPLODE);
            blocks.at(y + (i + 1)).at(x).startClock();
            continue;
        }
        if (blocks.at(y + (i + 1)).at(x).getType() == BOX) {
            blocks.at(y + (i + 1)).at(x).setType(EXPLODE);
            blocks.at(y + (i + 1)).at(x).startClock();
            addBonuses({x + 0.1, y + (i + 1) + 0.1});
        }
        break;
    }
    for (int i = 0; i < strength && y - (i + 1) >= 0; i++) {
        if (blocks.at(y - (i + 1)).at(x).getType() == AIR) {
            blocks.at(y - (i + 1)).at(x).setType(EXPLODE);
            blocks.at(y - (i + 1)).at(x).startClock();
            continue;
        }
        if (blocks.at(y - (i + 1)).at(x).getType() == BOX) {
            blocks.at(y - (i + 1)).at(x).setType(EXPLODE);
            blocks.at(y - (i + 1)).at(x).startClock();
            addBonuses({x + 0.1, y - (i + 1) + 0.1});
        }
        break;
    }
}

void Map::drawBlocks()
{
    std::vector<std::string> textureNames = {
        "basic_floor", "zyzz_texture", "box_texture", "explosion"};
    for (auto& blocks_line : blocks) {
        for (auto& block : blocks_line) {
            Engine::drawBlock(getEngine().getTexture(textureNames.at(0)),
                {roundf(block.getPos().first),
                    0.0f,
                    roundf(block.getPos().second)},
                sizeBlock,
                sizeBlock,
                sizeBlock,
                WHITE);
            switch (block.getType()) {
                case OBSTACLE:
                    Engine::drawBlock(
                        getEngine().getTexture(textureNames.at(1)),
                        {block.getPos().first, 1.0f, block.getPos().second},
                        sizeBlock,
                        sizeBlock,
                        sizeBlock,
                        WHITE);
                    break;
                case BOX:
                    Engine::drawBlock(
                        getEngine().getTexture(textureNames.at(2)),
                        {block.getPos().first, 1.0f, block.getPos().second},
                        sizeBlock,
                        sizeBlock,
                        sizeBlock,
                        WHITE);
                    break;
                default: break;
            }
        }
    }
    for (auto& blocks_line : blocks) {
        for (auto& block : blocks_line) {
            if (block.getType() == EXPLODE) {
                Engine::drawBlock(getEngine().getTexture(textureNames.at(3)),
                    {block.getPos().first, 1.0f, block.getPos().second},
                    sizeBlock,
                    sizeBlock,
                    sizeBlock,
                    WHITE);
            }
        }
    }
    for (Bonuses& bonuse : bonuses) {
        bonuse.display(engine);
    }
}

Block::Block(std::pair<float, float> pos, BlockType type)
    : type(type)
    , pos(pos)
    , clocks({})
    , collideBox(pos, {1, 1})
{
}

CollisionBox& Block::getCollideBox()
{
    return this->collideBox;
}

BlockType Block::getType() const
{
    return type;
}

void Block::setType(BlockType type)
{
    this->type = type;
}

std::pair<float, float> Block::getPos() const
{
    return pos;
}

std::vector<std::pair<float, float>> Map::getSpawns()
{
    return this->spawns;
}

std::vector<std::vector<Block>> Map::getBlocks()
{
    return this->blocks;
}

void Block::startClock()
{
    if (clocks.empty())
        clocks.emplace_back(1.5);
    this->clocks.at(clocks.size() - 1).reset();
}

void Block::updateBlock()
{
    if (static_cast<int>(this->clocks.at(clocks.size() - 1).loop()) == 1) {
        this->type = AIR;
        this->clocks.pop_back();
    }
}

void Map::addBonuses(std::pair<float, float> pos)
{
    if (rand() % 4 == 0)
        this->bonuses.emplace_back(pos);
}

std::vector<Bonuses> Map::getBonuses()
{
    return this->bonuses;
}

void Map::removeBonuses(Bonuses& bonus)
{
    for (int i = 0; i < bonuses.size(); i++) {
        if (bonuses.at(i).getPos().first == bonus.getPos().first
            && bonuses.at(i).getPos().second == bonus.getPos().second
            && bonuses.at(i).getType() == bonus.getType()) {
            this->bonuses.erase(this->bonuses.begin() + i);
            return;
        }
    }
}