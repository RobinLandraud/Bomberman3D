/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Model3D
*/

#ifndef MODEL3D_HPP_
#define MODEL3D_HPP_

#include <raylib.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

class Model3D
{
  public:
    Model3D(Texture2D& texture,
        std::string& model,
        std::vector<std::string>& anims,
        float size);
    ~Model3D() = default;

    std::pair<ModelAnimation*, unsigned int>& getAnim(unsigned int index);
    [[nodiscard]] unsigned int getAnimsCount(int index) const;
    [[nodiscard]] unsigned int getAnimFrameCounter() const;
    void setAnimFrameCounter(unsigned int nb);
    [[nodiscard]] unsigned int getAnimIndex() const;
    void setAnimIndex(unsigned int index);
    float getSize() const;
    Model& getModel();

  protected:
    unsigned int animIndex;
    unsigned int animFrameCounter;
    float size;
    Model model;
    Texture2D& texture;
    std::vector<std::pair<ModelAnimation*, unsigned int>> anims = {};

  private:
};

#endif /* !MODEL3D_HPP_ */
