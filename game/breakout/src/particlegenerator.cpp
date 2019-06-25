#include "particlegenerator.h"

namespace curiosity {
    namespace graphics {

    ParticleGenerator::ParticleGenerator(Program program, Texture2D texture, unsigned int amount)
        : program(program), texture(texture), amount(amount) {
        init();
    }

    void ParticleGenerator::update(float dt, GameObject &object, unsigned int newParticles, Vec2 offset) {
        for (unsigned int i = 0; i < newParticles; ++i) {
            int unusedParticle = firstUnusedParticle();
            respawnParticle(particles[unusedParticle], object, offset);
        }

        for (unsigned int i = 0; i < amount; ++i) {
            Particle &p = particles[i];
            p.life -= dt;
            if (p.life > 0.0f) {
                p.position -= p.velocity * dt;
                p.color.w -= dt*2.5f;
            }
        }
    }

    void ParticleGenerator::draw() {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        program.use();
        for (Particle particle : particles) {
            if (particle.life > 0.0f) {
                program.setVector2f("offset", particle.position);
                program.setVector4f("color", particle.color);
                texture.bind();
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void ParticleGenerator::init() {
        GLuint VBO;
        GLfloat particle_quad[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)0);
        glBindVertexArray(0);

        for (unsigned int i = 0; i < amount; ++i) {
            particles.push_back(Particle());
        }
    }

    unsigned int lastUsedParticle = 0;
    unsigned int ParticleGenerator::firstUnusedParticle() {
        for (unsigned int i = lastUsedParticle; i < amount; ++i) {
            if (particles[i].life <= 0.0f) {
                lastUsedParticle = i;
                return i;
            }
        }

        for (unsigned int i = 0; i < lastUsedParticle; ++i) {
            if (this->particles[i].life <= 0.0f ) {
                lastUsedParticle = i;
                return i;
            }
        }
        lastUsedParticle = 0;
        return 0;
    }

    void ParticleGenerator::respawnParticle(Particle &particle, GameObject &object, Vec2 offset) {
        float random = ((rand()%100)-50) / 10.0f;
        float rColor = 0.5 + ((rand()%100)/100.0f);
        particle.position = object.position + random + offset;
        particle.color = Vec4(rColor, rColor, rColor, 1.0f);
        particle.life = 1.0f;
        particle.velocity = object.velocity * 0.1f;
    }

    }
}






























