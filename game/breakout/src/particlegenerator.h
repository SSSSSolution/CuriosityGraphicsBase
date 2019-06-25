#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>
#include "graphicsglobal.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "texture2d.h"
#include "program.h"
#include "gameobject.h"

namespace curiosity {
    namespace graphics {

    struct Particle {
        Vec2 position, velocity;
        Vec4 color;
        float life;

        Particle() : position(0.0f, 0.0f), velocity(0.0f, 0.0f),
            color(1.0f, 1.0f, 1.0f, 1.0f), life(0.0f) { }
    };

    class ParticleGenerator {
    public:
        ParticleGenerator(Program program, Texture2D texture, unsigned int amount);
        void update(float dt, GameObject &object, unsigned int newParticles, Vec2 offset=Vec2(0.0f, 0.0f));
        void draw();

    private:
        void init();
        GLuint firstUnusedParticle();
        void respawnParticle(Particle &particle, GameObject &object, Vec2 offset = Vec2(0.0f, 0.0f));

    private:
        std::vector<Particle> particles;
        unsigned int amount;
        Program program;
        Texture2D texture;
        GLuint VAO;
    };

    }
}

#endif
