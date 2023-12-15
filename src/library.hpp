#include "main.hpp"

static std::fstream    edgeFile;
static std::fstream surfaceFile;

typedef struct v3d{
    double x,y,z;
};

typedef struct v2d{
    double x,y;
};

class Vertex{
public:
    int id;
    v3d* worldCoord;
    // v3d* viewCoord;
    v3d* next;
    
    Vertex(int id, v3d* &wCoord, v3d* &vCoord){
        this->id = id;
        this->worldCoord = wCoord;
        // this->viewCoord = vCoord;
    }

    void setId(int id)                  { this->id = id; }
    void setWorldCoord(v3d* &wCoord)    { this->worldCoord = wCoord; }
    // void setViewCoord(v3d* &vCoord)     { this->viewCoord = vCoord; }


    void draw(v3d* &coord) { glBegin(GL_POINTS); glVertex3i(coord->x, coord->y, coord->z); glEnd(); }
};

class Edge{
private:
    Vertex* startV;
    Vertex* endV;
    Edge* next;

    static std::string path = "edges.txt";
public:
    Edge() { }
    Edge(Vertex*& start, Vertex*& end)                { startV = start; endV = end; }
    Edge(Vertex*& start, Vertex*& end, Vertex*& next) { startV = start, endV = end; this->next = next; }

    static void initFileReader() { edgeFile.open(path, ios::binary | ios::in | ios::out | ios::app); }
    void loadVertex() { if (edgeFile.is_open) { return; } }
    void saveVertex() { if (edgeFile.is_open) { return; } }
    static void closeFileReader() { edgeFile.close(); }

    void draw(){ glBegin(GL_LINES); glVertex3d(startV->worldCoord->x, startV->worldCoord->y, startV->worldCoord->z); glVertex3d(endV->worldCoord->x,endV->worldCoord->y,endV->worldCoord->z); glEnd;}

};

class Surface {
public:
    Vertex* vList;
    Edge* eList;

    static std::string path = "vertex.txt";

    static void initFileReader()  { surfaceFile.open(path, ios::binary | ios::in | ios::out | ios::app); }
    static void closeFileReader() { surfaceFile.close(); }

    static v3d viewpoint;

    void setViewPoint() {double px, double py, double pz} { viewpoint{ px, py, pz}; }
     void draw() { }
}