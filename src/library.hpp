#include "main.hpp"
#include <fstream>

static std::fstream file;

struct v3d {
    GLdouble x, y, z;
    glm::vec4 color;
    v3d(GLdouble dx, GLdouble dy, GLdouble dz) : x(dx), y(dy), z(dz) { }
};

class Vertex {
public:
    unsigned int id;
    v3d* worldCoord;

    Vertex(GLdouble x, GLdouble y, GLdouble z) : worldCoord( new v3d(x,y,z)) { id++;}

    void setId(int id) { this->id = id; }
    void setWorldCoord(v3d* wCoord) { this->worldCoord = wCoord; }

    vector<GLdouble> data() { return {worldCoord->x, worldCoord->y, worldCoord->z}; }
};

class Cube {
private:
    GLuint vao, vbo, ebo;
    vector<Vertex*> vertices;  
    vector<GLdouble> vertexData;
    std::vector<GLushort> cubeConnectivity;
    GLubyte numVertices;
    
    void loadVertices(const std::string& filePath,  const std::string& filePathConnectivity, const std::string& filePathColor);
    void setupBuffers();    

public:
    Cube(const std::string& filePathVertics, const std::string& filePathConnectivity, const std::string& filePathColor);
    short getNumVertices();
    void draw();
    ~Cube();
};