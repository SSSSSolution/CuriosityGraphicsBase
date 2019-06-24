#include <string>
#include <fstream>
#include <sstream>
#include "gamelevel.h"
#include "resourcemanager.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    void GameLevel::load(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
        bricks.clear();

        GLuint tileCode;
        GameLevel level;
        string line;
        string filePath = rootDir()+"/levels/" + file;
        ifstream fstream(filePath.c_str());
        vector<vector<GLuint> > tileData;
        if (fstream) {
            // 读取文件的每一行
            while (getline(fstream, line)) {
                istringstream sstream(line);
                vector<GLuint> row;
                while (sstream >> tileCode)
                    row.push_back(tileCode);
                tileData.push_back(row);
            }
            if (tileData.size() > 0)
                init(tileData, levelWidth, levelHeight);
        } else {
            cout << "load gamelevel failed: " << file << endl;
        }
    }

    void GameLevel::draw(SpriteRender &render) {
        for (GameObject &tile : this->bricks)
            if (!tile.destroyed)
                tile.draw(render);
    }

    GLboolean GameLevel::isCompleted() {
        for (GameObject &tile : bricks)
            if (!tile.isSolid && !tile.destroyed)
                return GL_FALSE;
        return GL_TRUE;
    }

    void GameLevel::init(std::vector<std::vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight) {
        GLuint height = tileData.size();
        GLuint width = tileData[0].size();
        float unitWidth = levelWidth/(1.0f*width);
        float unitHeight = levelHeight/(1.0f*height);
        
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                if (tileData[y][x] == 1) {
                    Vec2 pos(unitWidth*x, unitHeight*y);
                    Vec2 size(unitWidth, unitHeight);
                    GameObject obj(pos, size, ResourceManager::getTexture2D("block_solid"),
                                   Vec3(0.8f, 0.8f, 0.7f));
                    obj.isSolid = true;
                    bricks.push_back(obj);
                } else if (tileData[y][x] > 1) {
                    Vec3 color = Vec3(1.0f, 1.0f, 1.0f);
                    if (tileData[y][x] == 2) {
                        color = Vec3(0.2f, 0.6f, 1.0f);
                    } else if (tileData[y][x] == 3) {
                        color = Vec3(0.0f, 0.7f, 0.0f);
                    } else if (tileData[y][x] == 4) {
                        color = Vec3(0.8f, 0.8f, 0.4f);
                    } else if (tileData[y][x] == 5) {
                        color = Vec3(1.0f, 0.5f, 0.0f);
                    }
                    
                    Vec2 pos(unitWidth*x, unitHeight *y);
                    Vec2 size(unitWidth, unitHeight);
                    bricks.push_back(GameObject(pos, size, ResourceManager::getTexture2D("block"), color));
                }
            }
        }
    }


    }
}

