#ifndef BREAKOUT_H
#define BREAKOUT_H
#include <tuple>
#include "graphicsglobal.h"
#include "spriterender.h"
#include "gamelevel.h"
#include "gameobject.h"
#include "ballobject.h"
#include "particlegenerator.h"
#include "postprocessor.h"

namespace curiosity {
    namespace breakout {

    class Game {
    public:
        Game(unsigned int width, unsigned height);
        ~Game();
        void Init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();

    private:
        enum Direction {
            NONE = -1,
            UP,
            RIGHT,
            DOWN,
            LEFT
        };
        typedef std::tuple<bool, Direction, curiosity::graphics::Vec2> Collision;
        bool checkCollision(curiosity::graphics::GameObject &one,
                            curiosity::graphics::GameObject &two);
        Collision checkCollision(curiosity::graphics::BallObject &ball,
                            curiosity::graphics::GameObject &box);
        void doCollisions();
        Direction vectorDirection(curiosity::graphics::Vec2 target);

    public:
        enum GameState {
            GAME_ACTIVE,
            GAME_MENU,
            GAME_WIN
        };
        GameState state;
        bool keys[1024];
        unsigned int width, height;

    private:
        std::vector<curiosity::graphics::GameLevel> levels;
        GLuint level;
        curiosity::graphics::SpriteRender *renderer;
        curiosity::graphics::GameObject *player;
        curiosity::graphics::BallObject *ball;
        curiosity::graphics::ParticleGenerator *particles;
        curiosity::graphics::PostProcessor *effects;
        float shakeTime;
    };

    }
}

#endif
