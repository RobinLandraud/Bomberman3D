/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** AudioEngine
*/

#include "AudioEngine.hpp"

#include <utility>

AudioEngine::AudioEngine()
{
    std::string name = "main_menu_bb";
    InitAudioDevice();
    for (auto& songToAdd : this->soundsToAdd)
        addSound(songToAdd.first, songToAdd.second);
    changeVolume(0.5, name);
    playSound(name);
}

AudioEngine::~AudioEngine() noexcept
{
    unloadAll();
    CloseAudioDevice();
}

void AudioEngine::addSound(std::string& path, std::string& name)
{
    Sound sound = LoadSound(std::string(std::move(path)).c_str());
    this->sounds.emplace(name, sound);
}

void AudioEngine::addMusic(std::string& path, std::string& name)
{
    Music music = LoadMusicStream(path.c_str());
    this->musics.emplace(name, music);
}

void AudioEngine::playIndexSound(std::string& name, int size, float volume)
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

void AudioEngine::playSound(std::string& name)
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

void AudioEngine::pauseSound(std::string& name)
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

void AudioEngine::changeMasterVolume(float volume)
{
    SetMasterVolume(volume);
}

void AudioEngine::changeVolume(float volume, std::string& name)
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

void AudioEngine::changePitch(float pitch, std::string& name)
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

bool AudioEngine::isSoundPlaying(Sound sound)
{
    return (IsSoundPlaying(sound));
}

bool AudioEngine::isMusicPlaying(Music music)
{
    return (IsMusicStreamPlaying(music));
}

void AudioEngine::pause(std::string& name)
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

void AudioEngine::play(std::string& name)
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

void AudioEngine::unloadAll()
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

void AudioEngine::unloadSound(std::string& name)
{
    auto its = this->sounds.find(name);
    if (its != this->sounds.end()) {
        UnloadSound(its->second);
        return;
    }
}

void AudioEngine::unloadMusic(std::string& name)
{
    auto itm = this->musics.find(name);
    if (itm != this->musics.end()) {
        UnloadMusicStream(itm->second);
        return;
    }
}

Sound AudioEngine::getSound(std::string& name)
{
    auto its = this->sounds.find(name);
    return (its->second);
}