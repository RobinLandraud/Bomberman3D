/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** ACharacter
*/

#include "ACharacter.hpp"

ACharacter::ACharacter(Map& map, std::pair<float, float> pos, float speed)
    : map(map)
    , speed(speed)
    , direction(Direction::NONE)
    , spawn(pos)
    , pos(pos)
    , collideBox(pos, {0.6, 0.6})
    , clockBomb(1)
    , inviTime(2)
    , otherChars(nullptr)
    , ghostTime(3)
{
}

void ACharacter::collideBonuses()
{
    std::string BonusSoundName = "bonus_song";
    for (Bonuses& bonuse : this->map.getBonuses()) {
        if (this->collideBox.isColide(bonuse.getCollideBox())) {
            switch (bonuse.getType()) {
                case SPEED: this->speed = this->speed + 0.25f; break;
                case BOMB_UP:
                    this->nbBomb++;
                    this->maxBomb++;
                    break;
                case BOMB_RANGE: this->bombStrength++; break;
                case WALL_PATH:
                    this->isGhost = true;
                    this->ghostTime.reset();
                    break;
            }
            map.getEngine().getSFX().playSound(BonusSoundName);
            this->map.removeBonuses(bonuse);
        }
    }
}

std::pair<bool, bool> ACharacter::checkCollide(
    std::pair<float, float> pos, std::vector<std::vector<Block>> blocks)
{
    int x = 0;
    int y = 0;
    bool collide = false;
    bool isDead = false;
    if (std::fabs(std::ceil(pos.first) - pos.first) < 0.001f)
        x = std::ceil(pos.first);
    else
        x = std::floor(pos.first);
    if (std::fabs(std::ceil(pos.second) - pos.second) < 0.001f)
        y = std::ceil(pos.second);
    else
        y = std::floor(pos.second);
    int startX = x - 1;
    int startY = y - 1;
    if (startX < 0)
        startX = 0;
    if (startY < 0)
        startY = 0;
    for (; startY < (y + 2) && startY < blocks.size(); startY++) {
        for (int tempX = startX;
             tempX < (x + 2) && tempX < blocks.at(startY).size();
             tempX++) {
            if (blocks.at(startY).at(tempX).getType() != AIR
                && blocks.at(startY).at(tempX).getType() != EXPLODE
                && this->collideBox.isColide(
                    blocks.at(startY).at(tempX).getCollideBox())) {
                if (isGhost
                    && blocks.at(startY).at(tempX).getType() != OBSTACLE)
                    continue;
                collide = true;
            }
            if (blocks.at(startY).at(tempX).getType() == EXPLODE
                && this->collideBox.isColide(
                    blocks.at(startY).at(tempX).getCollideBox())) {
                isDead = true;
            }
        }
    }
    return {collide, isDead};
}

void ACharacter::update(Event& event, Engine& engine)
{
    if (life <= 0) {
        this->updateBombs();
        return;
    }
    if (isInvisible && inviTime.loop())
        isInvisible = false;
    std::pair<float, float> nextPos = pos;
    bool collide = false;
    bool isDead = false;
    direction = Direction::NONE;
    getModel().setAnimIndex(0);
    if (isGhost && ghostTime.loop()) {
        isGhost = false;
    }
    nextPos = getNextPos();
    this->collideBox.setPos(nextPos);
    std::pair<bool, bool> res = checkCollide(this->pos, this->map.getBlocks());
    collide = res.first;
    isDead = res.second;
    for (int z = 0; z < getAllBomb().size() && !collide; z++) {
        if (this->collideBox.isColide(getAllBomb().at(z).getCollideBox())
            && !isGhost)
            collide = true;
    }
    for (Bomb& myBomb : this->bombs) {
        if (this->collideBox.isColide(myBomb.getCollideBox())
            && !myBomb.getOwnerInside() && !isGhost)
            collide = true;
        else if (!this->collideBox.isColide(myBomb.getCollideBox())
                 && myBomb.getOwnerInside())
            myBomb.setOwnerInside(false);
    }
    if (collide) {
        this->collideBox.setPos(pos);
    } else {
        pos = nextPos;
    }
    collideBonuses();
    respawn(isDead, engine);
    this->updateBombs();
}

void ACharacter::respawn(bool isDead, Engine& engine)
{
    std::string deathSoundName = "ben_ugh";
    if (isDead && !this->getIsInvisible()) {
        this->setIsInvisible(true);
        this->pos = this->spawn;
        this->collideBox.setPos(pos);
        engine.getSFX().playSound(deathSoundName);
        life--;
    }
}

void ACharacter::display()
{
}

int ACharacter::dropBomb()
{
    if (static_cast<int>(clockBomb.loop()) != 1)
        return 1;
    if (this->nbBomb <= 0)
        return 1;
    clockBomb.reset();
    this->bombs.emplace_back(this->pos, 2.3, this->bombStrength);
    this->nbBomb--;
    return 0;
}

void ACharacter::setNbBomb(int nbBomb)
{
    this->nbBomb = nbBomb;
}

int ACharacter::getNbBomb() const
{
    return this->nbBomb;
}

int ACharacter::getMaxBomb() const
{
    return this->maxBomb;
}

int ACharacter::getLife() const
{
    return this->life;
}

bool ACharacter::hasLaunchBomb() const
{
    return this->launchBomb;
}

std::pair<float, float> ACharacter::getPos() const
{
    return this->pos;
}

int ACharacter::getBombStrength() const
{
    return this->bombStrength;
}

std::vector<Bomb>& ACharacter::getBombs()
{
    return this->bombs;
}

void ACharacter::setDirection(Direction dir)
{
    direction = dir;
}

ACharacter::Direction ACharacter::getDirection() const
{
    return direction;
}

void ACharacter::setOtherChars(
    std::tuple<ACharacter&, ACharacter&, ACharacter&> newOthers)
{
    (void)otherChars.release();
    otherChars =
        std::make_unique<std::tuple<ACharacter&, ACharacter&, ACharacter&>>(
            newOthers);
}

std::tuple<ACharacter&, ACharacter&, ACharacter&> ACharacter::getOtherChars()
{
    return *otherChars;
}

void ACharacter::setPos(std::pair<float, float> newPos)
{
    this->pos = newPos;
}

std::pair<float, float> ACharacter::getSpawn() const
{
    return spawn;
}

void ACharacter::updateBombs()
{
    int size = static_cast<int>(bombs.size());
    for (int i = 0; i < size; i++) {
        bombs.at(i).update();
        if (bombs.at(i).hasExploded()) {
            this->map.giveMeWhatExplode(
                bombs.at(i).getStrength(), bombs.at(i).getPos());
            this->nbBomb++;
            bombs.erase(bombs.begin() + i);
            size--;
            i--;
        }
    }
}

std::vector<Bomb> ACharacter::getAllBomb()
{
    this->allBomb.clear();
    if (this->otherChars == nullptr)
        return this->allBomb;
    for (Bomb& bomb : std::get<0>(*otherChars).getBombs()) {
        this->allBomb.push_back(bomb);
    }
    for (Bomb& bomb : std::get<1>(*otherChars).getBombs()) {
        this->allBomb.push_back(bomb);
    }
    for (Bomb& bomb : std::get<2>(*otherChars).getBombs()) {
        this->allBomb.push_back(bomb);
    }
    return this->allBomb;
}

bool ACharacter::getIsInvisible() const
{
    return this->isInvisible;
}

void ACharacter::setIsInvisible(bool invisible)
{
    if (invisible)
        this->inviTime.reset();
    this->isInvisible = invisible;
}

std::pair<float, float> ACharacter::getNextPos()
{
    return this->pos;
}