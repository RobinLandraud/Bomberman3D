/*
** EPITECH PROJECT, 2022
** Bomberman3D
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <raylib.h>

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class TextMaterial {
    public:
        TextMaterial();
        ~TextMaterial();

        int addTextureToTab(std::string path, std::string& name);
        std::map<std::string, Texture2D>& getTextures();
        void drawTexture(std::string& name,
            Vector2 pos,
            float rotation,
            float scale,
            Color colorName);
        void unloadTextures();
        Texture2D& getTexture(std::string& name);

    protected:
        std::map<std::string, Texture2D> textures;
    private:
        static int checkFile(std::string& name);
};

#endif /* !TEXTURE_HPP_ */
