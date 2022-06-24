/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** SFX
*/

#include "SFX.hpp"

#include <utility>

SFX::SFX()
{
    std::string name = "main_menu_bb";
    InitAudioDevice();
    for (auto& songToAdd : this->soundsToAdd)
        addSound(songToAdd.first, songToAdd.second);
    changeVolume(0.5, name);
    playSound(name);
}

SFX::~SFX() noexcept
{
    unloadAll();
    CloseAudioDevice();
}

void SFX::addSound(std::string& path, std::string& name)
{
    Sound sound = LoadSound(std::string(std::move(path)).c_str());
    this->sounds.emplace(name, sound);
}

void SFX::addMusic(std::string& path, std::string& name)
{
    Music music = LoadMusicStream(path.c_str());
    this->musics.emplace(name, music);
}

void SFX::playIndexSound(std::string& name, int size, float volume)
{
    std::vector<std::string> othersIndex = {};
    for (int i = 1; i < size; i++) {
        othersIndex.push_back(name + std::to_string(i + 1));
    }
    if (isSoundPlaying(this->sounds.at(name))) {
        for (auto& otherIndex : othersIndex) {
            if (!isSoundPlaying(this->sounds.at(otherIndex))) {
                changeVolume(volume, otherIndex);
                PlaySound(this->sounds.at(otherIndex));
                return;
            }
        }
    } else {
        PlaySound(this->sounds.at(name));
        changeVolume(volume, name);
    }
}

void SFX::playSound(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        PlayMusicStream(itm->second);
        return;
    }
    std::string soundExplosionName = "bomb_explosion";
    std::string soundBenName = "ben_ugh";
    auto its = this->sounds.find(name);
    if (name.compare(std::string("bomb_explosion")) == 0) {
        playIndexSound(soundExplosionName, 8, 0.2);
    } else if (name.compare(std::string("ben_ugh")) == 0) {
        playIndexSound(soundBenName, 4, 2);
    } else {
        if (its != this->sounds.end()) {
            PlaySound(its->second);
        }
    }
}

void SFX::pauseSound(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        PauseMusicStream(itm->second);
        return;
    }
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        PauseSound(its->second);
        return;
    }
}

void SFX::changeMasterVolume(float volume)
{
    SetMasterVolume(volume);
}

void SFX::changeVolume(float volume, std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        SetMusicVolume(itm->second, volume);
        return;
    }
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        SetSoundVolume(its->second, volume);
        return;
    }
}

void SFX::changePitch(float pitch, std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        SetMusicPitch(itm->second, pitch);
        return;
    }
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        SetSoundPitch(its->second, pitch);
        return;
    }
}

bool SFX::isSoundPlaying(Sound sound)
{
    return (IsSoundPlaying(sound));
}

bool SFX::isMusicPlaying(Music music)
{
    return (IsMusicStreamPlaying(music));
}

void SFX::pause(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        PauseMusicStream(itm->second);
        return;
    }
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        PauseSound(its->second);
        return;
    }
}

void SFX::play(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        PlayMusicStream(itm->second);
        return;
    }
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        PlaySound(its->second);
        return;
    }
}

void SFX::unloadAll()
{
    for (auto& music : musics) {
        UnloadMusicStream(music.second);
        return;
    }
    for (auto& sound : sounds) {
        UnloadSound(sound.second);
        return;
    }
}

void SFX::unloadSound(std::string& name)
{
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        UnloadSound(its->second);
        return;
    }
}

void SFX::unloadMusic(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        UnloadMusicStream(itm->second);
        return;
    }
}

Sound SFX::getSound(std::string& name)
{
    auto its = this->sounds.find(name);
    return (its->second);
}