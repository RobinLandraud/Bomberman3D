/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** SFX
*/

#ifndef SFX_HPP_
#define SFX_HPP_

#include <raylib.h>

#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

class SFX
{
  public:
    SFX();
    ~SFX() noexcept;
    SFX(SFX&& b) noexcept = default;

    SFX& operator=(SFX const& rhs) noexcept = default;
    SFX& operator=(SFX&& rhs) noexcept = default;
    void addSound(std::string& path, std::string& name);
    void addMusic(std::string& path, std::string& name);
    void playSound(std::string& name);
    void pauseSound(std::string& name);
    static void changeMasterVolume(float volume);
    void changeVolume(float volume, std::string& name);
    void changePitch(float pitch, std::string& name);
    static bool isSoundPlaying(Sound sound);
    static bool isMusicPlaying(Music music);
    void pause(std::string& name);
    void play(std::string& name);
    void unloadAll();
    void unloadSound(std::string& name);
    void unloadMusic(std::string& name);
    Sound getSound(std::string& name);
    void playIndexSound(std::string& name, int size, float volume);

  protected:
  private:
    std::map<std::string, Music> musics;
    std::map<std::string, Sound> sounds;
    std::vector<std::pair<std::string, std::string>> soundsToAdd = {
        {"assets/test_song.ogg", "mainsong"},
        {"assets/main_menu_bb.ogg", "main_menu_bb"},
        {"assets/ben_ugh.ogg", "ben_ugh"},
        {"assets/ben_ugh.ogg", "ben_ugh2"},
        {"assets/ben_ugh.ogg", "ben_ugh3"},
        {"assets/ben_ugh.ogg", "ben_ugh4"},
        {"assets/ice_bb_song.ogg", "ice_bb_song"},
        {"assets/click.ogg", "click"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion"},
        {"assets/bonus_song.ogg", "bonus_song"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion2"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion3"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion4"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion5"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion6"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion7"},
        {"assets/explosion_bomb_bb.ogg", "bomb_explosion8"},
        {"assets/volcano.ogg", "volcano"},
        {"assets/highway.ogg", "highway"},
        {"assets/underground.ogg", "underground"},
        {"assets/forest.ogg", "forest"}};
};

#endif /* !SFX_HPP_ */
