#include <iostream>
#include <vector>
#include "graphicsglobal.h"
#include "fpscamera.h"
#include "model.h"
#include "lightsource.h"
#include "program.h"
#include "shader.h"
#include "scene.h"
#include "transmat4.h"
#include "game.h"


//using namespace sb7;
using namespace curiosity::graphics;
using namespace std;

curiosity::breakout::Game BreakOut(800, 600);
class my_application : public sb7::application {
public:
    virtual void init() {
        strcpy(info.title, "breakout");
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

    virtual void startup()
    {
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        BreakOut.Init();
    }

    virtual void render(double currentTime)
    {
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        std::cout << deltaTime << std::endl;
        BreakOut.ProcessInput(deltaTime);
        BreakOut.Update(deltaTime);

        glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        BreakOut.Render();
    }

    virtual void onKey(int button, int action)
    {
        if (button == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (button >= 0 && button < 1024) {
            if (action == GLFW_PRESS)
                BreakOut.keys[button] = GL_TRUE;
            else if (action == GLFW_RELEASE)
                BreakOut.keys[button] = GL_FALSE;
        }
    }

    virtual void onMouseMove(int x, int y)
    {

    }


private:
    GLfloat deltaTime;
    GLfloat lastFrame;
};

DECLARE_MAIN(my_application);
