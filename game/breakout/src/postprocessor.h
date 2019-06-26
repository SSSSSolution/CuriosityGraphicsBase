#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <graphicsglobal.h>
#include "texture2d.h"
#include "program.h"

namespace curiosity {
    namespace graphics {

    class PostProcessor {
    public:
        PostProcessor(Program program, unsigned int width, unsigned int height);
        void endRender();
        void beginRender();
        void render(float time);

    private:
        void initRenderData();

    public:
        Program postProcessingProgram;
        Texture2D texture;
        unsigned int width, height;
        bool shake;

    private:
        GLuint MSFBO, FBO;
        GLuint RBO;
        GLuint VAO;
    };

    }
}

#endif
