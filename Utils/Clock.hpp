/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Clock
*/

#pragma once

#include <chrono>

class Clock
{
  public:
    enum Status { PAUSE = 0, RUNNING = 1 };
    Clock(float secondes);
    ~Clock() = default;
    void refresh();
    void pause();
    Status is_running();
    void reset();
    bool loop();
    void setLapseLag(std::chrono::milliseconds mDeltaTime);

  protected:
  private:
    unsigned int fps = 60;
    Status status = PAUSE;
    std::chrono::milliseconds mLoopTime;
    std::chrono::duration<float> dDeltaTime;
    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> now;
    int lapseLag;
};