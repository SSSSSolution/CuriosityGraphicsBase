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
#include "transmat4.h"
#include "resourcemanager.h"
#include <map>
#include "text_renderer/tttextrenderer.h"
#include "data_struct/octree.h"
#include "drawable_object/skybox.h"
#include "drawable_object/ballobject.h"
#include "scene_managing/scene_v1/scenev1.h"
#include "scene_managing/scene_v1/scenev1factory.h"
#include "drawable_object/cubeobject.h"
#include "drawable_object/gravity.h"

//using namespace sb7;
using namespace curiosity::graphics;
using namespace std;

class my_application : public sb7::application {
public:
    virtual void init() {
        strcpy(info.title, "test Curiosity Graphics Base");
        info.windowWidth = 2560;
        info.windowHeight = 1400;

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
        skyboxProgram =  ResourceManager::loadProgram("/skybox_vertex_shader", "/skybox_fragment_shader", nullptr, "skybox");
        ballProgram = ResourceManager::loadProgram("/drawobject/ballobject.vs", "/drawobject/ballobject.fs", nullptr, "ballobject");
        cubeProgram = ResourceManager::loadProgram("/drawobject/cubeobject.vs", "/drawobject/cubeobject.fs", nullptr, "cubeobject");
        ResourceManager::loadTexture("container2.png", GL_TRUE, "container2");

//        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        fov = 45.0f;
        camera.moveSpeed_ = 0.25f;
        camera.mouseSensitivity_ = 0.025f;

        std::vector<string> paths{
            skyboxDir() + "/skybox1/right.jpg",
            skyboxDir() + "/skybox1/left.jpg",
            skyboxDir() + "/skybox1/top.jpg",
            skyboxDir() + "/skybox1/bottom.jpg",
            skyboxDir() + "/skybox1/front.jpg",
            skyboxDir() + "/skybox1/back.jpg"
        };
        skybox = Skybox::create(paths);

        cube = new CubeObject(Vec3(0.0f, 0.0f, 0.0f), Vec3(100.0f, 1.0f, 100.0f), &cubeProgram);
        cube->setVelocity(Vec3(0.0f, 0.0f, 0.0f));
        cube->setTexture("container2");

        scenev1 = new SceneV1(new SceneV1Factory());

        fpsKeepTime = 0.05f;
        textRenderer = new TTTextRenderer("NotoSansCJK-Bold.ttc", info.windowWidth, info.windowHeight);

        gravity.setG(50.0f);
    }

    virtual void render(double currentTime)
    {
        static double lastTime = currentTime;
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
//        std::cout << "frame time: " << deltaTime << "s" << std::endl;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        cubeProgram.use();
        cubeProgram.setTransMat4("view", viewMat);
        cubeProgram.setTransMat4("project", projectMat);
//        cube->draw();

        gravity.setDeltaTime(deltaTime);
        gravity.notify();

        ballProgram.use();
        ballProgram.setTransMat4("view", viewMat);
        ballProgram.setTransMat4("project", projectMat);

        list<BallObject *>::const_iterator iter;
        for (iter = ballObjects.begin(); iter != ballObjects.end(); iter++) {
            (*iter)->setVeocity((*iter)->getVelocity()*0.99f);
            (*iter)->go(deltaTime);
            (*iter)->draw();
            if (IS_FLOAT_ZERO((*iter)->getVelocity().dot((*iter)->getVelocity()))) {
                scenev1->addObject(*iter);
                iter = ballObjects.erase(iter);
            }
        }
        // 场景开始工作
        scenev1->setMat(projectMat, viewMat);
        scenev1->exec();







        fpsKeepTime -= deltaTime;
        if (fpsKeepTime <= 0.0f) {
            int fps = 1/deltaTime;
            fpsStr = "fps: " + std::to_string(fps);
            fpsKeepTime = 0.1f;
        }
        textRenderer->renderText(fpsStr, 20.0f, 40.0f,
                                  0.5f, Vec3(0.5f, 0.8f, 0.2f));
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

    virtual void onMouseButton(int button, int action) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            BallObject *obj = new BallObject(camera.position_, Vec3(1.0f, 1.0f, 1.0f), &ballProgram);
            obj->setVeocity(camera.getFront()*100.0f);
//            scenev1->addObject(obj);
            ballObjects.push_back(obj);
//            gravity.attach(obj);
        }
    }

private:
    FPSCamera camera;
    float fov;
    TransMat4 projectMat, modelMat, viewMat, skyboxViewMat;
    Program textProgram, skyboxProgram, ballProgram, cubeProgram;
    TTTextRenderer *textRenderer;

    float fpsKeepTime;
    std::string fpsStr;

    std::shared_ptr<Skybox> skybox;
    CubeObject *cube;
    std::list<BallObject *> ballObjects;

    SceneV1 *scenev1;
    Gravity gravity;
};

DECLARE_MAIN(my_application);





















