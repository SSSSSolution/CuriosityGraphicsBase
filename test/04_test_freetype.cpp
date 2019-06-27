#include <iostream>
#include <vector>
#include <string>
#include "graphicsglobal.h"
#include "fpscamera.h"
#include "model.h"
#include "lightsource.h"
#include "program.h"
#include "shader.h"
#include "scene.h"
#include "transmat4.h"
#include "ft2build.h"
#include "resourcemanager.h"
#include <map>
#include FT_FREETYPE_H

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
        ResourceManager::loadProgram("/text.vs","/text.fs", NULL, "text");
        textProgram =  ResourceManager::getProgram("text");;
        TransMat4 projection = TransMat4::ortho(0.0f, (float)(info.windowWidth),
                                                0.0f, (float)(info.windowHeight),
                                                -1.0f, 1.0f);
        textProgram.use();
        textProgram.setTransMat4("projection", projection);

        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cout << "Error::FreetypeE: could not init freetype library" << std::endl;
        FT_Face face;
        if (FT_New_Face(ft, (fontDir()+"NotoSansCJK-Bold.ttc").c_str(), 0, &face))
            std::cout << "Error::FreeTypeE: failed to load font" << std::endl;
        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (GLubyte c = 0; c < 128; c++) {
            if (FT_Load_Char(face ,c, FT_LOAD_RENDER)) {
                std::cout << "Error::FreetypeE: failed to load GLyph" << std::endl;
                continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                         face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                Vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                (GLuint)(face->glyph->advance.x)
            };
            characters.insert(std::pair<GLchar, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 *4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        fov = 45.0f;
        camera.moveSpeed_ = 0.25f;
        camera.mouseSensitivity_ = 0.025f;

//        glEnable(GL_MULTISAMPLE);
//        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void renderText(Program program, std::string text, GLfloat x, GLfloat y,
                    GLfloat scale, Vec3 color) {
        program.use();
        program.set3f("textColor", color.x_, color.y_, color.z_);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); ++c) {
            Character ch = characters[*c];

            GLfloat xpos = x + ch.bearing.x_ * scale;
            GLfloat ypos = y - (ch.size.y_ - ch.bearing.y_) * scale;

            GLfloat w = ch.size.x_ * scale;
            GLfloat h = ch.size.y_ * scale;

            GLfloat vertices[6][4] = {
                { xpos, ypos+h, 0.0f, 0.0f},
                { xpos, ypos,   0.0f, 1.0f},
                { xpos + w, ypos, 1.0f, 1.0f},

                { xpos, ypos + h, 0.0f, 0.0f},
                { xpos + w, ypos, 1.0f, 1.0f},
                { xpos + w, ypos + h, 1.0f, 0.0f}
            };
            glBindTexture(GL_TEXTURE_2D, ch.textureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    virtual void render(double currentTime)
    {
        static double lastTime = currentTime;
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;
//        std::cout << "frame time: " << deltaTime << "s" << std::endl;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        int fps = 1/deltaTime;
        std::string str = "fps: " + std::to_string(fps);
        renderText(textProgram, "This is a sample text.", 25.0f, 25.0f,
                   1.0f, Vec3(0.5f, 0.8f, 0.2f));
        renderText(textProgram, str.c_str(), 540.0f, 570.0f,
                   0.5f, Vec3(0.3f, 0.7f, 0.9f));

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
};

DECLARE_MAIN(my_application);
