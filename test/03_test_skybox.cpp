#include <iostream>
#include <vector>
#include <memory>
#include "graphicsglobal.h"
#include "fpscamera.h"
#include "model.h"
#include "lightsource.h"
#include "program.h"
#include "shader.h"
#include "scene.h"
#include "transmat4.h"
#include "stb_image.h"
#include "drawable_object/cubeblock.h"
#include "drawable_object/skybox.h"


//using namespace sb7;
using namespace curiosity::graphics;
using namespace std;

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
        char *root = getenv("PROJECT_ROOT");
        std::string rootDir(root);
        std::string vertexShaderPath = shaderDir() +"/cubeblock_vertex_shader";
        std::string fragmentShaderPath = shaderDir() +"/cubeblock_fragment_shader";
        Shader vertexShader = Shader(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
        Shader fragmentShader = Shader(fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
        vertexShader.compile();
        fragmentShader.compile();
        vector<Shader> shaders;
        shaders.push_back(vertexShader);
        shaders.push_back(fragmentShader);
        cubeProgram = new Program;
        cubeProgram->use();
        std::cout << "create Program finished" << std::endl;
        cubeProgram->linkShaders(shaders);

        vertexShaderPath = shaderDir() +"/vertex_shader";
        fragmentShaderPath =shaderDir() +"/fragment_shader";
        Shader modelVertexShader = Shader(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
        Shader modelfragmentShader = Shader(fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
        modelVertexShader.compile();
        modelfragmentShader.compile();
        vector<Shader> modelShaders;
        modelShaders.push_back(modelVertexShader);
        modelShaders.push_back(modelfragmentShader);
        modelProgram = new Program;
        modelProgram->use();
        std::cout << "create Program finished" << std::endl;
        modelProgram->linkShaders(modelShaders);

        spotLight1 = new SpotLight;

        model = new Model("/home/huangwei/study/computer_graphics/learning_computer_graphics/src/model/nanosuit/nanosuit.obj");

        scene.addLightSource(spotLight1);
        scene.addModel(model);

        fov = 45.0f;
        camera.moveSpeed_ = 0.25f;
        camera.mouseSensitivity_ = 0.025f;

        cubeBlock1.init();
        cubeBlock1.position_ = Vec3(0.0f, 0.0f, 0.0f);
        cubeBlock2.init();
        cubeBlock2.position_ = Vec3(-128.0f, 0.0f, 0.0f);
        cubeBlock3.init();
        cubeBlock3.position_ = Vec3(-128.0f, 0.0f, -128.0f);
        cubeBlock4.init();
        cubeBlock4.position_ = Vec3(0.0f, 0.0f, -128.0f);


        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_CULL_FACE);
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
        vertexShaderPath = shaderDir() +"/skybox_vertex_shader";
        fragmentShaderPath = shaderDir() +"/skybox_fragment_shader";
        Shader skyboxVertexShader = Shader(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
        Shader skyboxfragmentShader = Shader(fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
        skyboxVertexShader.compile();
        skyboxfragmentShader.compile();
        vector<Shader> skyboxShaders;
        skyboxShaders.push_back(skyboxVertexShader);
        skyboxShaders.push_back(skyboxfragmentShader);
        skyboxProgram = new Program;
        skyboxProgram->use();
        skyboxProgram->linkShaders(skyboxShaders);
        std::cout << "create Program finished" << std::endl;

    }

    virtual void render(double currentTime)
    {
        static double lastTime = currentTime;
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
//        std::cout << "frame time: " << deltaTime << "s" << std::endl;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.getViewTransMat();
        projectMat = TransMat4::projection(
                    (float)(info.windowWidth)/(float)(info.windowHeight),
                     fov, 0.1f, 1000.0f);

        // 绘制skybox
        skyboxProgram->use();

        skyboxViewMat = viewMat;
        skyboxViewMat.data_[12] = 0;
        skyboxViewMat.data_[13] = 0;
        skyboxViewMat.data_[14] = 0;

        skyboxProgram->setTransMat4("view", skyboxViewMat);
        skyboxProgram->setTransMat4("project", projectMat);
        skyboxProgram->setInt("skybox", 0);
        skybox->draw(*skyboxProgram);



        modelProgram->use();
        modelProgram->setTransMat4("view", viewMat);
        modelProgram->setTransMat4("project", projectMat);
        modelMat = TransMat4::translation(0.0f, 0.5f, 0.0f);
        TransMat4 scaleMat = TransMat4::scale(0.2f, 0.2f, 0.2f);
        modelMat =  modelMat * scaleMat;
        modelProgram->setTransMat4("model", modelMat);
        modelProgram->setVec3("viewPos", camera.position_);
        spotLight1->position_ = camera.position_;
        spotLight1->direction_ = camera.getFront();
        scene.draw(*modelProgram);

        cubeProgram->use();
        cubeProgram->setTransMat4("view", viewMat);
        cubeProgram->setTransMat4("project", projectMat);

        modelMat = TransMat4::translation(cubeBlock1.position_);
        cubeProgram->setTransMat4("model", modelMat);
        cubeBlock1.draw(*cubeProgram);

        modelMat = TransMat4::translation(cubeBlock2.position_);
        cubeProgram->setTransMat4("model", modelMat);
        cubeBlock2.draw(*cubeProgram);

        modelMat = TransMat4::translation(cubeBlock3.position_);
        cubeProgram->setTransMat4("model", modelMat);
        cubeBlock3.draw(*cubeProgram);

        modelMat = TransMat4::translation(cubeBlock4.position_);
        cubeProgram->setTransMat4("model", modelMat);
        cubeBlock4.draw(*cubeProgram);
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
    Model *model;

    Program *cubeProgram, *modelProgram, *skyboxProgram;
    TransMat4 projectMat, modelMat, viewMat, skyboxViewMat;
    SpotLight *spotLight1;
    Scene scene;
    CubeBlock cubeBlock1,cubeBlock2, cubeBlock3, cubeBlock4, cubeBlock5, cubeBlock6;
    GLuint cubemapTexture;
    GLuint skyboxVAO_, skyboxVBO_;
    std::shared_ptr<Skybox> skybox;
};

DECLARE_MAIN(my_application);
