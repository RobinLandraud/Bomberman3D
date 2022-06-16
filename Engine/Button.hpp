/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Button
*/

#pragma once

#include <raylib.h>

#include <cmath>
#include <iostream>

class CollisionBox
{
  public:
    CollisionBox(float, float, float, float);
    CollisionBox(std::pair<float, float>, std::pair<float, float>);
    bool isColide(CollisionBox&) const;
    bool isColide(std::pair<float, float>& pos) const;
    void setPos(float, float);
    void setPos(Vector2);
    void setPos(std::pair<float, float>);
    float x;
    float y;
    float w;
    float h;

  protected:
  private:
};

class Button
{
  public:
    Button(Texture2D& texture,
        std::pair<float, float> pos,
        float scale,
        Color colorName);
    Button(std::pair<Texture2D&, float> on,
        std::pair<Texture2D&, float> off,
        std::pair<float, float> pos,
        Color colorName,
        bool activated);
    Button(Texture2D& texture, std::pair<float, float> pos, float scale);
    Button(Texture2D& texture, std::pair<float, float> pos, Color colorName);
    Button(Texture2D& texture, std::pair<float, float> pos);
    [[nodiscard]] Texture& getTexture() const;
    [[nodiscard]] Texture& getTextureOff() const;
    void setTexture(Texture& texture, float scale);
    [[nodiscard]] float getScale() const;
    [[nodiscard]] float getScaleOff() const;
    [[nodiscard]] Color getColor() const;
    void setPos(Vector2& pos);
    Vector2& getPos();
    void setZoom(float zoom);
    CollisionBox& getCollisionBox();
    void click();
    [[nodiscard]] bool is_activated() const;

    ~Button() = default;

  protected:
  private:
    Texture2D& texture;
    Texture2D& off;
    Vector2 pos;
    float scale;
    float scale2;
    float zoom;
    Color color;
    CollisionBox box;
    bool activated;
};
