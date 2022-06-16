/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** main
*/

#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

#include "Core.hpp"

int main()
{
    Engine::initWindow(1920, 1080);
    indie::Core core;
    core.mainLoop();
    return (0);
}