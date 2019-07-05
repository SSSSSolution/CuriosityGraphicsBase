#include <stdlib.h>
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
#include "data_struct/octree.h"
#include "drawable_object/skybox.h"

//using namespace sb7;
using namespace curiosity::graphics;
using namespace std;

class TestOcTree : public OcTree {
public:
    TestOcTree(int maxContentSize) : OcTree(maxContentSize)  {}
    ~TestOcTree() {}
protected:
    virtual void process(TreeNode *node) {
        cout << "<"
             << node->range[0] << ", " << node->range[1] << ","
             << node->range[2] << ", " << node->range[3] << ","
             << node->range[4] << ", " << node->range[5] << ">"
             << endl;
    }
};

class my_application : public sb7::application {
public:
    virtual void init() {
        strcpy(info.title, "test Curiosity Graphics Base");
        info.windowWidth = 1920;
        info.windowHeight = 1080;

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

        fov = 45.0f;
        camera.moveSpeed_ = 0.25f;
        camera.mouseSensitivity_ = 0.025f;


        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        std::vector<string> paths{
            skyboxDir() + "/skybox1/right.jpg",
            skyboxDir() + "/skybox1/left.jpg",
            skyboxDir() + "/skybox1/top.jpg",
            skyboxDir() + "/skybox1/bottom.jpg",
            skyboxDir() + "/skybox1/front.jpg",
            skyboxDir() + "/skybox1/back.jpg"
        };
        skybox = Skybox::create(paths);
        skyboxProgram =  ResourceManager::loadProgram("/skybox_vertex_shader", "/skybox_fragment_shader", nullptr, "skybox");

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

        viewMat = camera.getViewTransMat();
        projectMat = TransMat4::projection((float)(info.windowWidth)/(float)(info.windowHeight), fov, 0.1f, 1000.0f);

        // 绘制skybox
        skyboxProgram.use();

        skyboxViewMat = viewMat;
        skyboxViewMat.data_[12] = 0;
        skyboxViewMat.data_[13] = 0;
        skyboxViewMat.data_[14] = 0;

        skyboxProgram.setTransMat4("view", skyboxViewMat);
        skyboxProgram.setTransMat4("project", projectMat);
        skyboxProgram.setInt("skybox", 0);
        skybox->draw(skyboxProgram);
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
    TransMat4 projectMat, modelMat, viewMat, skyboxViewMat;
    Program textProgram, skyboxProgram;
    TTTextRenderer *textRenderer;

    float fpsKeepTime;
    std::string fpsStr;

    std::shared_ptr<Skybox> skybox;
};

DECLARE_MAIN(my_application);





















