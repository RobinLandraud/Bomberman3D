/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Event
*/

#include "Event.hpp"

Event::mouse_t& Event::updateMouseInfo()
{
    mouse.pos = {GetMouseX(), GetMouseY()};
    mouse.right = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    mouse.left = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    mouse.middle = IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE);
    mouse.isVisible = !IsCursorHidden();
    return mouse;
}

std::vector<KeyList>& Event::updateKeysPressed()
{
    auto key = static_cast<KeyList>(GetKeyPressed());
    size_t i = 0;
    size_t size = keyPressed.size();
    bool exist = false;
    while (key != K_NULL) {
        exist = false;
        for (auto elem : keyPressed) {
            if (elem == key)
                exist = true;
        }
        if (!exist)
            keyPressed.emplace_back(key);
        key = static_cast<KeyList>(GetKeyPressed());
    }
    while (i < size) {
        if (IsKeyUp(static_cast<int>(keyPressed.at(i)))) {
            keyPressed.erase(keyPressed.begin() + static_cast<long>(i));
            size -= 1;
        } else {
            i++;
        }
    }
    return keyPressed;
}

std::pair<std::vector<KeyList>&, Event::mouse_t&> Event::updateEvents()
{
    return {updateKeysPressed(), updateMouseInfo()};
}

Event::mouse_t& Event::getMouseInfo()
{
    return mouse;
}

std::vector<KeyList>& Event::getKeysPressed()
{
    return keyPressed;
}

std::pair<std::vector<KeyList>&, Event::mouse_t&> Event::getEvents()
{
    return {getKeysPressed(), getMouseInfo()};
}