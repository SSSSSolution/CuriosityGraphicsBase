#include <string>
#include <fstream>
#include "gamelevel.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    void GameLevel::load(const GLchar *file, GLuint levelWidth, GLuint levelHeight) {
        bricks.clear();

        GLuint tileCode;
        GameLevel level;
        string line;
        ifstream fstream(file);
        vector<vector<GLuint> > tileData;
        if (fstream) {
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

    }


    }
}























