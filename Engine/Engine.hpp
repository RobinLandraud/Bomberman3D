/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Engine
*/

#pragma once

#include <sys/stat.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "AudioEngine.hpp"
#include "Button.hpp"
#include "Event.hpp"
#include "Model3D.hpp"

class Engine
{
  public:
    Engine(int width, int height) noexcept;
    Engine(Engine const& b) noexcept = default;
    Engine(Engine&& b) noexcept = default;
    ~Engine() noexcept;

    int addTextureToTab(std::string path, std::string& name);
    std::map<std::string, Texture2D>& getTextures();
    void drawTexture(std::string& name,
        Vector2 pos,
        float rotation,
        float scale,
        Color colorName);
    static void drawButtons(std::map<std::string, Button>& buttons);
    static void drawButtons(std::vector<Button>& buttons);
    static void drawText(std::string& msg,
        Color colorName,
        std::pair<int, int> pos,
        int fontSize);
    void unloadTextures();
    std::vector<std::string> getAssetsTab();
    Texture2D& getTexture(std::string& name);
    Event& getEvent();
    [[nodiscard]] int getScreenWidth() const;
    [[nodiscard]] int getScreenHeight() const;
    Model3D& getModel3D(int pos);
    [[nodiscard]] int getNbModels() const;
    static void beginDraw();
    static void endDraw();
    static void clearBackground();
    static void stopWindowDisplay();
    static bool windowShouldClose();
    static void initWindow(int width, int height);
    void updateCamera();
    void initCameraMode(CameraMode camMode);
    Camera getCamera();
    AudioEngine& getAudioEngine();
    void initMode3D();
    static void endMode3D();
    void addModel(std::string& textureName,
        std::string& model,
        std::vector<std::string>& anims,
        float size);
    static void drawBlock(Texture2D texture,
        Vector3 position,
        float width,
        float height,
        float length,
        Color color);
    static void drawModel(Model3D& model,
        std::pair<float, float> pos,
        std::tuple<float, float, float> axeRot,
        float angleRot);
    static void drawnSphere(Vector3 position, float radius, Color color);
    void setCameraValue(
        Vector3 pos, Vector3 target, Vector3 up, float fovy, int projection);
    std::string& getTitle(int pos);
    void drawHUDStart();
    void setFramesCounter(int nb, int pos);
    int getFramesCounter(int pos);
    void drawTextEx(Font font,
        const char* txt,
        Vector2 position,
        float fontsize,
        float spacing,
        Color color);

  protected:
    Camera camera;
    std::map<std::string, Texture2D> textures;
    Image imageTemp;
    int screenWidth;
    int screenHeight;
    Vector2 posCenter;
    AudioEngine audioHandler;
    Event event;
    std::vector<std::string> assets = {
        "bgchar2",
        "bm-icon",
        "button1",
        "bombIcon",
        "clock",
        "close",
        "dot1",
        "dot2",
        "header",
        "heart",
        "ok",
        "pause",
        "play",
        "table",
        "next",
        "prev",
        "sky-bg",
        "zyzz_texture",
        "iconPlayerBlue",
        "iconPlayerRed",
        "iconPlayerGreen",
        "iconPlayerYellow",
        "iconPlayerPurple",
        "iconPlayerGrey",
        "deadpool",
        "deadpoolYellow",
        "deadpoolBlue",
        "deadpoolPurple",
        "deadpoolGreen",
        "deadpoolGrey",
        "basic_floor",
        "box_texture",
        "explosion",
        "bomb_up",
        "fire",
        "skate",
        "soft_block_pass",
        "instructions",
    };
    std::string path;
    std::vector<Model3D> models;
    std::vector<std::string> titles = {
        "A Bomberman video game using Raylib realised by : ",
        "-Nicolas  LAVIGNE",
        "-Robin    LANDRAUD",
        "-Valentin EYRAUD",
        "-Theo     PAUTARD",
    };
    std::vector<int> framesCounterVec = {0, 0, 0, 0, 0};
    Font font;

  private:
    static int checkFile(std::string& name);
};