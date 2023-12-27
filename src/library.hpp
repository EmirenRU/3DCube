#include "main.hpp"
#include <fstream>

static std::fstream file;

struct v3d {
    GLdouble x, y, z;
    v3d(GLdouble dx, GLdouble dy, GLdouble dz) : x(dx), y(dy), z(dz) { }
};

class Vertex {
public:
    unsigned int id;
    v3d* worldCoord;

    Vertex(GLdouble x, GLdouble y, GLdouble z) : worldCoord( new v3d(x,y,z)) { id++;}

    void setId(int id) { this->id = id; }
    void setWorldCoord(v3d* wCoord) { this->worldCoord = wCoord; }

    void draw(Vertex* &end);
    vector<GLdouble> data();
};

class Polygon {
private:
    Vertex* vertices[3]; 

public:
    Polygon(Vertex* v0, Vertex* v1, Vertex* v2);
    void draw();
    void draw(Vertex a,Vertex b,Vertex c);
};

class Cube {
private:
    GLuint vao, vbo, ebo;
    vector<Vertex*> vertices; 
    vector<GLdouble> vertexData;
    std::vector<GLushort> cubeConnectivity;

    short numVertices = 24;
    void loadVertices(const std::string& filePath,  const std::string& filePathConnectivity);
    void setupBuffers();    

public:
    Cube(const std::string& filePathVertics, const std::string& filePathConnectivity);
    short getNumVertices();
    void draw();
    ~Cube();
};