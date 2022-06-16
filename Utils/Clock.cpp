/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Clock
*/

#include "Clock.hpp"

#include <chrono>
#include <iostream>

Clock::Clock(float secondes)
    : fps(static_cast<int>((1.0f / secondes)))
    , status(RUNNING)
    , lapseLag(0)
    , mLoopTime(
          std::chrono::milliseconds(static_cast<int>(secondes * float(1000.0))))
    , dDeltaTime(
          std::chrono::steady_clock::now() - std::chrono::steady_clock::now())
{
    std::chrono::milliseconds tmpMil(
        static_cast<int>(secondes * float(1000.0)));
    this->mLoopTime = tmpMil;
    begin = std::chrono::steady_clock::now();
    now = std::chrono::steady_clock::now();
    dDeltaTime = now - begin;
}

void Clock::refresh()
{
    if (status == PAUSE) {
        begin += (std::chrono::steady_clock::now() - now);
        now = std::chrono::steady_clock::now();
    }
    now = std::chrono::steady_clock::now();
    dDeltaTime = now - begin;
}

void Clock::pause()
{
    if (status == RUNNING)
        status = PAUSE;
    else
        status = RUNNING;
}

Clock::Status Clock::is_running()
{
    return (this->status);
}

void Clock::reset()
{
    this->status = RUNNING;
    begin = std::chrono::steady_clock::now();
    now = std::chrono::steady_clock::now();
    dDeltaTime = now - begin;
    lapseLag = 0;
}

void Clock::setLapseLag(std::chrono::milliseconds mDeltaTime)
{
    if (this->status == PAUSE)
        return;
    if (mDeltaTime >= (mLoopTime * 2))
        mDeltaTime -= mLoopTime;
    else
        return;
    while (mDeltaTime > mLoopTime) {
        if (lapseLag >= 10)
            lapseLag = 0;
        mDeltaTime -= mLoopTime;
        lapseLag = lapseLag + 1;
    }
}

bool Clock::loop()
{
    std::chrono::milliseconds mDeltaTime;
    refresh();
    mDeltaTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(dDeltaTime);
    if (status == RUNNING)
        setLapseLag(mDeltaTime);
    if (status == PAUSE)
        return false;
    if (mDeltaTime > mLoopTime) {
        begin += mLoopTime;
        return (true);
    }
    if (lapseLag > 0) {
        lapseLag = lapseLag - 1;
        begin += mLoopTime;
        return true;
    }
    return (false);
}