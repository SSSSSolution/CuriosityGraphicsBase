#include <string>
#include "game.h"
#include "resourcemanager.h"

using namespace curiosity::graphics;
using namespace std;

namespace curiosity {
    namespace breakout {

    Game::Game(GLuint width, GLuint height)
        : state(GAME_ACTIVE), Keys(), width(width), height(height) {

    }

    Game::~Game() {
        delete renderer;
    }

    void Game::Init() {
        ResourceManager::loadProgram((shaderDir()+"/breakout/sprite.vs").c_str(),
                                     (shaderDir()+"/breakout/sprite.fs").c_str(),
                                     NULL, "sprite");
        TransMat4 projection = TransMat4::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        Program spriteProgram = ResourceManager::getProgram("sprite");
        spriteProgram.use();
        spriteProgram.setInt("image", 0);
        spriteProgram.setTransMat4("projection", projection);

        ResourceManager::loadTexture("/breakout/awesomeface.png",
                                     GL_TRUE, "face");

        Program tmp = ResourceManager::getProgram("sprite");
        renderer = new SpriteRender(tmp);
    }

    void Game::Update(GLfloat dt) {

    }


    void Game::ProcessInput(GLfloat dt) {

    }

    void Game::Render() {
        renderer->drawSprite(ResourceManager::getTexture2D("face"),
                             Vec2(200.0f, 200.0f), Vec2(300.0f, 400.0f),
                             45.0f, Vec3(1.0f, 0.0f, 0.0f));
    }
    }
}

























