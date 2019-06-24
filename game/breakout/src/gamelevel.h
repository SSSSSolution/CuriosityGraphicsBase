#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H
#include <vector>
#include "gameobject.h"

namespace curiosity {
    namespace graphics {

    class GameLevel {
    public:
        GameLevel() {}

        void load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);

        void draw(SpriteRender &render);

        GLboolean isCompleted();

    private:
        void init(std::vector<std::vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight);

    public:
        std::vector<GameObject> bricks;
    };

    }
}


#endif
