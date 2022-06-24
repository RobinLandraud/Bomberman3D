/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(Texture2D& texture,
    std::pair<float, float> pos,
    float scale,
    Color colorName)
    : texture(texture)
    , off(texture)
    , scale(scale)
    , scale2(scale)
    , zoom(1)
    , color(colorName)
    , box(pos.first,
          pos.second,
          static_cast<float>(texture.width) * scale,
          static_cast<float>(texture.height) * scale)
    , activated(false)
    , pos({pos.first, pos.second})
{
}

Button::Button(std::pair<Texture2D&, float> on,
    std::pair<Texture2D&, float> off,
    std::pair<float, float> pos,
    Color colorName,
    bool activated)
    : texture(on.first)
    , off(off.first)
    , scale(on.second)
    , scale2(off.second)
    , zoom(1)
    , color(colorName)
    , box(pos.first,
          pos.second,
          static_cast<float>(texture.width) * on.second,
          static_cast<float>(texture.height) * on.second)
    , activated(activated)
    , pos({pos.first, pos.second})
{
}

Button::Button(Texture2D& texture, std::pair<float, float> pos, float scale)
    : Button(texture, pos, scale, WHITE)
{
}

Button::Button(Texture2D& texture, std::pair<float, float> pos, Color colorName)
    : Button(texture, pos, 1, colorName)
{
}

Button::Button(Texture2D& texture, std::pair<float, float> pos)
    : Button(texture, pos, 1, WHITE)
{
}

void Button::setZoom(float zoom)
{
    this->zoom = zoom;
}

void Button::setPos(Vector2& pos)
{
    this->pos.x = pos.x;
    this->pos.y = pos.y;
}

Texture2D& Button::getTexture() const
{
    return this->texture;
}

Texture2D& Button::getTextureOff() const
{
    return this->off;
}

void Button::setTexture(Texture& texture, float scale)
{
    this->texture = texture;
    this->scale = scale;
}

float Button::getScale() const
{
    return (this->scale * this->zoom);
}

float Button::getScaleOff() const
{
    return (this->scale2 * this->zoom);
}

void Button::click()
{
    activated = !activated;
}

bool Button::is_activated() const
{
    return activated;
}

Color Button::getColor() const
{
    return this->color;
}

Vector2& Button::getPos()
{
    return this->pos;
}

CollisionBox& Button::getCollisionBox()
{
    return this->box;
}

CollisionBox::CollisionBox(float x, float y, float w, float h)
    : x(x)
    , y(y)
    , w(w)
    , h(h)
{
}

CollisionBox::CollisionBox(
    std::pair<float, float> pos, std::pair<float, float> size)
    : x(pos.first)
    , y(pos.second)
    , w(size.first)
    , h(size.second)
{
}

bool CollisionBox::isColide(CollisionBox& other) const
{
    if (std::fabs(this->x - (other.x + other.w)) < 0.001f
        || std::fabs((this->x + this->w) - other.x) < 0.001f
        || std::fabs(this->y - (other.y + other.h)) < 0.001f
        || std::fabs((this->h + this->y) - other.y) < 0.001f)
        return false;
    return (this->x < other.x + other.w && this->x + this->w > other.x
            && this->y < other.y + other.h && this->h + this->y > other.y);
}

bool CollisionBox::isColide(std::pair<float, float>& pos) const
{
    return (pos.first > this->x && pos.first < this->x + this->w
            && pos.second > this->y && pos.second < this->y + this->h);
}

void CollisionBox::setPos(float x, float y)
{
    this->x = x;
    this->y = y;
}

void CollisionBox::setPos(Vector2 pos)
{
    this->x = pos.x;
    this->y = pos.y;
}

void CollisionBox::setPos(std::pair<float, float> pos)
{
    this->x = pos.first;
    this->y = pos.second;
}