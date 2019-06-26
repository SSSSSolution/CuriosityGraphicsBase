#include <string>
#include "game.h"
#include "resourcemanager.h"

using namespace curiosity::graphics;
using namespace std;

const Vec2 PLAYER_SIZE(100,20);
const float PLAYER_VELOCITY(500.0f);
const Vec2 INITIAL_BALL_VELOSITY(200.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

namespace curiosity {
    namespace breakout {

    Game::Game(unsigned int width, unsigned int height)
        : state(GAME_ACTIVE), keys(), width(width), height(height), renderer(NULL), shakeTime(0.0f) {
    }

    Game::~Game() {
        if (renderer)
            delete renderer;
    }

    void Game::Init() {
        std::cout << ">>>>Game init ..." << std::endl << std::endl;

        ResourceManager::loadProgram("/sprite.vs","/sprite.fs", NULL, "sprite");
        TransMat4 projection = TransMat4::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        Program spriteProgram = ResourceManager::getProgram("sprite");
        spriteProgram.use();
        spriteProgram.setInt("sprite", 0);
        spriteProgram.setTransMat4("projection", projection);

        ResourceManager::loadTexture("/background.jpg", GL_FALSE, "background");
        ResourceManager::loadTexture("/block.png", GL_FALSE, "block");
        ResourceManager::loadTexture("/block_solid.png", GL_FALSE, "block_solid");
        ResourceManager::loadTexture("/awesomeface.png", GL_FALSE, "face");

        renderer = new SpriteRender(ResourceManager::getProgram("sprite"));

        // 加载关卡
        GameLevel one;
        one.load("one.lvl", width, height*0.5);
        levels.push_back(one);
        level = 1;

        // 加载挡板
        ResourceManager::loadTexture("/paddle.png", GL_FALSE, "paddle");
        Vec2 playerPos = Vec2(1.0f*width/2.0f - PLAYER_SIZE.x_/2,
                              height - PLAYER_SIZE.y_);
        player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture2D("paddle"));

        // 加载球
        Vec2 ballPos = playerPos + Vec2(PLAYER_SIZE.x_/2 - BALL_RADIUS, - BALL_RADIUS * 2);
        ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOSITY, ResourceManager::getTexture2D("face"));

        // 加载粒子效果
        ResourceManager::loadProgram("particles.vs", "particles.fs", NULL, "particle");
        Program particlesProgram = ResourceManager::getProgram("particle");
        particlesProgram.use();
        particlesProgram.setInt("sprite", 0);
        particlesProgram.setTransMat4("projection", projection);
        ResourceManager::loadTexture("particle.png", GL_TRUE, "particle");
        particles = new ParticleGenerator(
                    ResourceManager::getProgram("particle"),
                    ResourceManager::getTexture2D("particle"), 500);

        // 后期处理
        ResourceManager::loadProgram("post_processing.vs", "post_processing.fs", NULL, "postprocessing");
        effects = new PostProcessor(ResourceManager::getProgram("postprocessing"),width, height);
        std::cout << ">>>>Game init finished" << std::endl << std::endl;
    }

    void Game::Update(float dt) {
        ball->move(dt, this->width);
        doCollisions();
        particles->update(dt, *ball, 2, Vec2(ball->radius/2, ball->radius/2));
        if (shakeTime > 0.0f) {
            shakeTime -= dt;
            if (shakeTime <= 0.0f) {
                effects->shake = false;
            }
        }
    }


    void Game::ProcessInput(float dt) {
        if (state == GAME_ACTIVE) {
            float velocity = PLAYER_VELOCITY * dt;

            if (keys[GLFW_KEY_A]) {
                if (player->position.x_ >= 0) {
                    player->position.x_ -= velocity;
                    if (ball->stuck)
                        ball->position.x_ -= velocity;
                }
            } else if (keys[GLFW_KEY_D]) {
                if (player->position.x_ <= width - player->size.x_) {
                    player->position.x_ += velocity;
                    if (ball->stuck)
                        ball->position.x_ += velocity;
                }
            }
            if (keys[GLFW_KEY_SPACE]) {
                ball->stuck = false;
            }
        }
    }

    void Game::Render() {
        if (state == GAME_ACTIVE) {
            effects->beginRender();
                renderer->drawSprite(ResourceManager::getTexture2D("background"),
                                     Vec2(0, 0), Vec2(width, height), 0.0f);
                levels[level-1].draw(*renderer);
                player->draw(*renderer);
                particles->draw();
                ball->draw(*renderer);
            effects->endRender();
            effects->render(glfwGetTime());
        }
    }

    bool Game::checkCollision(GameObject &one, GameObject &two) {
        bool collisionX = (one.position.x_ + one.size.x_ > two.position.x_) &&
                          (two.position.x_ + two.size.x_ > one.position.x_);
        bool collisionY = (one.position.y_ + one.size.y_ > two.position.y_) &&
                          (two.position.y_ + two.size.y_ > one.position.y_);
        return collisionX && collisionY;
    }

    Game::Collision Game::checkCollision(BallObject &ball, GameObject &box) {
        Vec2 center(ball.position + Vec2(ball.radius, ball.radius));
        Vec2 boxHalf(box.size.x_/2, box.size.y_/2);
        Vec2 boxCenter(box.position.x_ + boxHalf.x_,
                       box.position.y_ + boxHalf.y_);
        Vec2 difference = center - boxCenter;
        Vec2 clamped = clamp(difference, boxHalf*(-1.0f), boxHalf);
        Vec2 closest = boxCenter + clamped;
        difference = closest - center;
        if (length(difference) < ball.radius)
            return std::make_tuple(true, vectorDirection(difference), difference);
        else
            return std::make_tuple(false, UP, Vec2(0.0f, 0.0f));
    }

    void Game::doCollisions() {
        for (GameObject &box : this->levels[level - 1].bricks) {
            if (!box.destroyed) {
                Collision collision = checkCollision(*ball, box);
                if (std::get<0>(collision)) {
                    if (!box.isSolid) {
                        box.destroyed = true;
                    } else {
                        effects->shake = true;
                        shakeTime = 0.05f;
                    }

                    Direction dir = std::get<1>(collision);
                    Vec2 diffVector = std::get<2>(collision);
                    if (dir == LEFT || dir == RIGHT) {
                        ball->velocity.x_ = -1.0f * ball->velocity.x_;
                        float penetration = ball->radius - std::abs(diffVector.x_);
                        if (dir == LEFT)
                            ball->position.x_ += penetration;
                        else
                            ball->position.x_ -= penetration;
                    } else {
                        ball->velocity.y_ = -1.0f * ball->velocity.y_;
                        float penetration = ball->radius  - std::abs(diffVector.y_);
                        if (dir == UP)
                            ball->position.y_ -= penetration;
                        else
                            ball->position.y_ += penetration;
                    }
                }
            }
        }

        Collision result = checkCollision(*ball, *player);
        if (!ball->stuck && std::get<0>(result)) {
            float centerBoard = player->position.x_ + player->size.x_ / 2;
            float distance = (ball->position.x_ + ball->radius) - centerBoard;
            float percentage = distance / (player->size.x_ / 2);

            float strength = 2.0f;
            Vec2 oldVelocity = ball->velocity;
            ball->velocity.x_ = INITIAL_BALL_VELOSITY.x_ * percentage * strength;
//            ball->velocity.y_ = -ball->velocity.y_;
            ball->velocity.y_ = -1.0f * abs(ball->velocity.y_);
            ball->velocity = ball->velocity.normalize() * length(oldVelocity);
        }
    }

    Game::Direction Game::vectorDirection(Vec2 target) {
        Vec2 compass[] {
          Vec2(0.0f, 1.0f),
          Vec2(1.0f, 0.0f),
          Vec2(0.0f, -1.0f),
          Vec2(-1.0f, 0.0f)
        };
        float max = -1.0f;
        int bestMatch = NONE;
        for (int i = 0; i < 4; ++i) {
            float dotProduct = target.normalize().dot(compass[i]);
            if (dotProduct > max) {
                max = dotProduct;
                bestMatch = i;
            }
        }
        return (Direction)bestMatch;
    }


    }
}
