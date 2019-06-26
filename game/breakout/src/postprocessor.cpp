#include <iostream>
#include "postprocessor.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    PostProcessor::PostProcessor(Program program, unsigned int width, unsigned int height)
        : postProcessingProgram(program), texture(), width(width), height(height), shake(false) {
        glGenFramebuffers(1, &MSFBO);
        glGenFramebuffers(1, &FBO);
        glGenRenderbuffers(1, &RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_RGB, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, RBO);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            cout << "ERROR::POSTPROCESSOR: Failed to initialze MSFBO" << endl;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        texture.generate(width, height, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            cout << "ERROR::POSTPROCESSOR: Failed to initialze FBO" << endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        initRenderData();
        postProcessingProgram.setInt("scene", 0);
        float offset = 1.0f/300.0f;
        float offsets[9][2] = {
            { -offset,  offset },
            { 0.0f,     offset },
            { offset,   offset },
            { -offset,  0.0f   },
            { 0.0f,     0.0f   },
            { offset,   0.0f   },
            { -offset,  -offset},
            { 0.0f,     -offset},
            { offset,   -offset}
        };
        postProcessingProgram.set2fv("offsets", 9, (GLfloat*)offsets);
        GLint edge_kernel[9] = {
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
        };
        postProcessingProgram.set1iv("edge_kernel", 9, edge_kernel);
        GLfloat blur_kernel[9] = {
            1.0f/16, 2.0f/16, 1.0f/16,
            2.0f/16, 4.0f/16, 2.0f/16,
            1.0f/16, 2.0f/16, 1.0f/16
        };
        postProcessingProgram.set1fv("blur_kernel", 9, blur_kernel);
    }

    void PostProcessor::beginRender() {
        glBindFramebuffer(GL_FRAMEBUFFER, MSFBO);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void PostProcessor::endRender() {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, MSFBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
        glBlitFramebuffer(0, 0, width, height, 0, 0,
                          width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void PostProcessor::render(float time) {
        postProcessingProgram.use();
        postProcessingProgram.setFloat("time", time);
        postProcessingProgram.setBool("shake", shake);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void PostProcessor::initRenderData() {
        GLuint VBO;
        float vertices[] = {
            -1.0f, -1.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  0.0f,  1.0f,

            -1.0f, -1.0f,  0.0f,  0.0f,
             1.0f, -1.0f,  1.0f,  0.0f,
             1.0f,  1.0f,  1.0f,  1.0f
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), (GLvoid *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    }
}
