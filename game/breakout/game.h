#ifndef BREAKOUT_H
#define BREAKOUT_H
#include "graphicsglobal.h"
#include "spriterender.h"

namespace curiosity {
    namespace breakout {

    class Game {
        public:
        enum GameState {
            GAME_ACTIVE,
            GAME_MENU,
            GAME_WIN
        };

        GameState state;
        GLboolean Keys[1024];
        GLuint width, height;

        Game(GLuint width, GLuint height);
        ~Game();

        void Init();

        void ProcessInput(GLfloat dt);
        void Update(GLfloat dt);
        void Render();
    private:
        curiosity::graphics::SpriteRender *renderer;
    };

    }
}

#endif
