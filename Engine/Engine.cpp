/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-valentin.eyraud
** File description:
** Engine
*/

#include "Engine.hpp"

#include <raylib.h>

Engine::Engine(int width, int height) noexcept
    : screenWidth(width)
    , screenHeight(height)
    , path("assets/")
    , font(LoadFont("assets/setback.png"))
    , imageTemp(LoadImage("assets/setback.png"))
    , camera({0})
    , posCenter({0, 0})
{
    // InitWindow(1920, 1080, "indie");
    SetTargetFPS(120);
    camera.position = {5.0f, 15.0f, 10.0f};
    camera.target = {5.0f, 15.0f, 10.0f};
    camera.up = {5.0f, 15.0f, 10.0f};
    camera.fovy = 180.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    for (auto& asset : assets) {
        std::ifstream f(path + asset + ".png");
        if (!f.good()) {
            std::cout << "file not found " + path + asset + ".png\n\n";
            continue;
        }
        addTextureToTab(path + asset + ".png", asset);
    }
}

void Engine::initWindow(int width, int height)
{
    InitWindow(width, height, "Indie");
}

void Engine::beginDraw()
{
    BeginDrawing();
}

void Engine::endDraw()
{
    EndDrawing();
}

void Engine::clearBackground()
{
    ClearBackground(RAYWHITE);
}

void Engine::stopWindowDisplay()
{
    CloseWindow();
}

bool Engine::windowShouldClose()
{
    return WindowShouldClose();
}

Engine::~Engine() noexcept
{
    unloadTextures();
}

int Engine::addTextureToTab(std::string path, std::string& name)
{
    int texture_pos = 0;
    Texture2D texture;
    if (path.empty() || checkFile(path) == -1)
        return (-1);
    imageTemp = LoadImage(path.c_str());
    texture = LoadTextureFromImage(imageTemp);
    UnloadImage(imageTemp);
    textures.insert(std::pair<std::string, Texture2D>(name, texture));
    return (0);
}

int Engine::checkFile(std::string& name)
{
    int pos = 0;
    if (!std::filesystem::exists(name)) {
        return -1;
    }
    pos = static_cast<int>(name.find_last_of('.'));
    if (name.substr(pos + 1).compare("png") == 0
        || name.substr(pos + 1).compare("jpg") == 0)
        return 0;
    return -1;
}

std::map<std::string, Texture2D>& Engine::getTextures()
{
    return (this->textures);
}

Model3D& Engine::getModel3D(int pos)
{
    return models.at(pos);
}

int Engine::getNbModels() const
{
    return static_cast<int>(models.size());
}

void Engine::drawTexture(std::string& name,
    Vector2 pos,
    float rotation,
    float scale,
    Color colorName)
{
    std::map<std::string, Texture2D>::iterator it;
    it = textures.find(name);
    DrawTextureEx(it->second, pos, rotation, scale, colorName);
}

void Engine::drawButtons(std::map<std::string, Button>& buttons)
{
    for (auto& button : buttons) {
        if (button.second.is_activated())
            DrawTextureEx(button.second.getTexture(),
                button.second.getPos(),
                0,
                button.second.getScale(),
                button.second.getColor());
        else
            DrawTextureEx(button.second.getTextureOff(),
                button.second.getPos(),
                0,
                button.second.getScaleOff(),
                button.second.getColor());
    }
}

void Engine::drawButtons(std::vector<Button>& buttons)
{
    for (auto& button : buttons) {
        if (button.is_activated())
            DrawTextureEx(button.getTexture(),
                button.getPos(),
                0,
                button.getScale(),
                button.getColor());
        else
            DrawTextureEx(button.getTextureOff(),
                button.getPos(),
                0,
                button.getScaleOff(),
                button.getColor());
    }
}

void Engine::drawText(
    std::string& msg, Color colorName, std::pair<int, int> pos, int fontSize)
{
    DrawText(msg.c_str(), pos.first, pos.second, fontSize, colorName);
}

void Engine::unloadTextures()
{
    std::map<std::string, Texture2D>::iterator it;
    for (it = textures.begin(); it != textures.end(); it++) {
        UnloadTexture(it->second);
    }
}

std::vector<std::string> Engine::getAssetsTab()
{
    return (this->assets);
}

int Engine::getScreenWidth() const
{
    return screenWidth;
}

int Engine::getScreenHeight() const
{
    return screenHeight;
}

Texture2D& Engine::getTexture(std::string& name)
{
    return textures.find(name)->second;
}

Event& Engine::getEvent()
{
    return event;
}

void Engine::drawBlock(Texture2D texture,
    Vector3 position,
    float width,
    float height,
    float length,
    Color color)
{
    DrawCubeTexture(texture, position, width, height, length, color);
}

void Engine::drawnSphere(Vector3 position, float radius, Color color)
{
    DrawSphere(position, radius, color);
}

Camera Engine::getCamera()
{
    return (this->camera);
}

SFX& Engine::getSFX()
{
    return (this->audioHandler);
}

void Engine::setCameraValue(
    Vector3 pos, Vector3 target, Vector3 up, float fovy, int projection)
{
    camera.position = pos;
    camera.target = target;
    camera.up = up;
    camera.fovy = fovy;
    camera.projection = projection;
}

void Engine::initCameraMode(CameraMode camMode)
{
    SetCameraMode(camera, camMode);
}

void Engine::updateCamera()
{
    UpdateCamera(&camera);
}

void Engine::initMode3D()
{
    BeginMode3D(camera);
}

void Engine::endMode3D()
{
    EndMode3D();
}

void Engine::addModel(std::string& textureName,
    std::string& model,
    std::vector<std::string>& anims,
    float size)
{
    this->models.emplace_back(getTexture(textureName), model, anims, size);
}

void Engine::drawModel(Model3D& model,
    std::pair<float, float> pos,
    std::tuple<float, float, float> axeRot,
    float angleRot)
{
    DrawModelEx(model.getModel(),
        {pos.first, 1.0f, pos.second},
        {std::get<0>(axeRot), std::get<1>(axeRot), std::get<2>(axeRot)},
        angleRot,
        {model.getSize(), model.getSize(), model.getSize()},
        WHITE);
}

std::string& Engine::getTitle(int pos)
{
    return (this->titles.at(pos));
}

void Engine::drawHUDStart()
{
    std::string textureName = "instructions";
    if (getFramesCounter(1) < 1000) {
        drawTexture(textureName, {1300, 50}, 0, 0.5, WHITE);
        DrawTextEx(font,
            "Epitech BORDEAUX, 2022",
            {10, 1000},
            static_cast<float>(font.baseSize) + 10,
            2,
            BLACK);
        DrawTextEx(font,
            TextSubtext(titles[0].c_str(), 0, framesCounterVec.at(0) / 10),
            {150, 100},
            static_cast<float>(font.baseSize) + 10,
            2,
            BLACK);
        if (framesCounterVec.at(0) > 700) {
            for (int i = 1; i <= 4; i++) {
                DrawTextEx(font,
                    TextSubtext(
                        titles[i].c_str(), 0, framesCounterVec.at(i) / 20),
                    {150, static_cast<float>((150 + (i * 40)))},
                    static_cast<float>(font.baseSize) + 10,
                    2,
                    BLACK);
            }
        }
    }
}

void Engine::setFramesCounter(int nb, int pos)
{
    framesCounterVec.at(pos) = nb;
}

int Engine::getFramesCounter(int pos)
{
    return (this->framesCounterVec.at(pos));
}