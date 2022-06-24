/*
** EPITECH PROJECT, 2022
** Bomberman3D
** File description:
** Texture
*/

#include "Material.hpp"

TextMaterial::TextMaterial()
{
}

TextMaterial::~TextMaterial()
{
}

int TextMaterial::addTextureToTab(std::string path, std::string& name)
{
    int texture_pos = 0;
    Texture2D texture;
    if (path.empty() || checkFile(path) == -1)
        return (-1);
    Image imageTemp = LoadImage(path.c_str());
    texture = LoadTextureFromImage(imageTemp);
    UnloadImage(imageTemp);
    textures.insert(std::pair<std::string, Texture2D>(name, texture));
    return (0);
}

int TextMaterial::checkFile(std::string& name)
{
    int pos = 0;
    if (!std::filesystem::exists(name)) {
        return -1;
    }
    pos = static_cast<int>(name.find_last_of('.'));
    if (name.substr(pos + 1).compare("png") == 0
        || name.substr(pos + 1).compare("jpg") == 0)
        return 0;
    return -1;
}

std::map<std::string, Texture2D>& TextMaterial::getTextures()
{
    return (this->textures);
}

Texture2D& TextMaterial::getTexture(std::string& name)
{
    return (this->textures.at(name));
}

void TextMaterial::drawTexture(std::string& name,
    Vector2 pos,
    float rotation,
    float scale,
    Color colorName)
{
    std::map<std::string, Texture2D>::iterator it;
    it = textures.find(name);
    DrawTextureEx(it->second, pos, rotation, scale, colorName);
}

void TextMaterial::unloadTextures()
{
    std::map<std::string, Texture2D>::iterator it;
    for (it = textures.begin(); it != textures.end(); it++) {
        UnloadTexture(it->second);
    }
}