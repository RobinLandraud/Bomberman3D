/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Model3D
*/

#include "Model3D.hpp"

#include <iostream>

Model3D::Model3D(Texture2D& texture,
    std::string& modele,
    std::vector<std::string>& animsPath,
    float size)
    : texture(texture)
    , animIndex(0)
    , model(LoadModel(modele.c_str()))
    , size(size)
    , animFrameCounter(0)
{
    unsigned int count = 0;
    ModelAnimation* animation = nullptr;
    SetMaterialTexture(
        &this->model.materials[0], MATERIAL_MAP_DIFFUSE, texture);
    for (auto& animPath : animsPath) {
        animation = LoadModelAnimations(animPath.c_str(), &count);
        this->anims.emplace_back(animation, count

        );
    }
}

std::pair<ModelAnimation*, unsigned int>& Model3D::getAnim(unsigned int index)
{
    return anims.at(index);
}

unsigned int Model3D::getAnimsCount(int index) const
{
    return anims.at(index).second;
}

unsigned int Model3D::getAnimIndex() const
{
    return animIndex;
}

void Model3D::setAnimIndex(unsigned int index)
{
    animIndex = index;
}

unsigned int Model3D::getAnimFrameCounter() const
{
    return animFrameCounter;
}

void Model3D::setAnimFrameCounter(unsigned int nb)
{
    animFrameCounter = nb;
    if (animIndex >= anims.size())
        return;
    UpdateModelAnimation(model,
        anims.at(animIndex).first[0],
        static_cast<int>(animFrameCounter));
    if (animFrameCounter >= anims.at(animIndex).first[0].frameCount)
        animFrameCounter = 0;
}

float Model3D::getSize() const
{
    return size;
}

Model& Model3D::getModel()
{
    return this->model;
}
