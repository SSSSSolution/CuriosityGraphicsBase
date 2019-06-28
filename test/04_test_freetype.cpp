#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "graphicsglobal.h"
#include "fpscamera.h"
#include "model.h"
#include "lightsource.h"
#include "program.h"
#include "shader.h"
#include "scene.h"
#include "transmat4.h"
#include "resourcemanager.h"
#include <map>
#include "text_renderer/tttextrenderer.h"

//using namespace sb7;
using namespace curiosity::graphics;
using namespace std;

class my_application : public sb7::application {
public:
    virtual void init() {
        strcpy(info.title, "test Curiosity Graphics Base");
        info.windowWidth = 800;
        info.windowHeight = 600;

#ifdef __APPLE__
        info.majorVersion = 3;
        info.minorVersion = 2;
#else
        info.majorVersion = 4;
        info.minorVersion = 3;
#endif
        info.samples = 0;
        info.flags.all = 0;
        info.flags.cursor = 1;
#ifdef _DEBUG
        info.flags.debug = 1;
#endif
        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    struct Character {
      GLuint textureID;
      Vec2 size;
      Vec2 bearing;
      unsigned int advance;
    };
    std::map<GLchar, Character> characters;
    virtual void startup()
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        fov = 45.0f;
        camera.moveSpeed_ = 0.25f;
        camera.mouseSensitivity_ = 0.025f;

        textRenderer = NULL;
        textRenderer = new TTTextRenderer("NotoSansCJK-Bold.ttc", 800, 600);
        fpsKeepTime  = 0.1f;

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        std::cout << "startup finished" << std::endl;
    }

    virtual void render(double currentTime)
    {
        static double lastTime = currentTime;
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
//        std::cout << "frame time: " << deltaTime << "s" << std::endl;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        fpsKeepTime -= deltaTime;
        if (fpsKeepTime <= 0.0f) {
            int fps = 1/deltaTime;
            fpsStr = "fps: " + std::to_string(fps);
            fpsKeepTime = 0.1f;
        }
        textRenderer->renderText(fpsStr, 250.0f, 250.0f,
                                  1.0f, Vec3(0.5f, 0.8f, 0.2f));
    }

    virtual void onKey(int button, int action)
    {
        if (button == GLFW_KEY_W && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(FPSCamera::FORWARD);
        } else if (button == GLFW_KEY_S && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(FPSCamera::BACKWARD);
        } else if (button == GLFW_KEY_A && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(FPSCamera::LEFT);
        } else if (button == GLFW_KEY_D && (GLFW_REPEAT == action || GLFW_PRESS == action)) {
            camera.processKeyboard(FPSCamera::RIGHT);
        }
    }

    virtual void onMouseMove(int x, int y)
    {
        static int lastX, lastY;
        static bool firstMouse = true;
        if (firstMouse) {
            lastX = info.windowWidth/2.0f;
            lastY = info.windowHeight/2.0f;
            firstMouse = false;
        }

        float xoffset = x - lastX;
        float yoffset = y - lastY;
        lastX = x;
        lastY = y;

        camera.processMouseMove(xoffset, yoffset);
    }


private:
    FPSCamera camera;
    float fov;
    TransMat4 projectMat, modelMat, viewMat;
    GLuint VAO, VBO;
    Program textProgram;
    TTTextRenderer *textRenderer;
    float fpsKeepTime;
    std::string fpsStr;
};

DECLARE_MAIN(my_application);
