#include "main.hpp"
#include <fstream>

static std::fstream file;

struct v3d {
    GLdouble x, y, z;
    v3d(GLdouble dx, GLdouble dy, GLdouble dz) : x(dx), y(dy), z(dz) { }
};

class Vertex {
public:
    short id;
    v3d* worldCoord;

    Vertex(GLdouble x, GLdouble y, GLdouble z) : worldCoord( new v3d(x,y,z)) {}

    void setId(int id) { this->id = id; }
    void setWorldCoord(v3d* wCoord) { this->worldCoord = wCoord; }

    void draw(Vertex* &end);
};

class Polygon {
private:
    Vertex* vertices[3]; 

public:
    Polygon(Vertex* v0, Vertex* v1, Vertex* v2) {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }

    void draw();
    void draw(Vertex a,Vertex b,Vertex c);
};

class Cube {
private:
    Vertex* vertices[24]; 
    static const GLushort  cubeConnectivity[];
    

public:
   Cube(const std::string& filePath){
        loadVertices(filePath);
   }

    void loadVertices(const std::string& filePath);

    void draw();
};