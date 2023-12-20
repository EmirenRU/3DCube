#include "main.hpp"
#pragma once

static std::fstream    edgeFile;
static std::fstream surfaceFile;

struct v3d{
    double x,y,z;
    v3d(double dx,double dy, double dz) : x(dx), y(dy), z(dz) { }
} ;

class Vertex{
public:
    static int UID;
    int id;
    v3d* worldCoord;
    // v3d* viewCoord;
    // Vertex* next;
    
    Vertex(int id, v3d* &wCoord ){//v3d* &vCoord
        this->id = id;
        this->worldCoord = wCoord;
        // this->viewCoord = vCoord;
    }

    Vertex(double x, double y, double z);

    void setId(int id)                  { this->id = id; }
    void setWorldCoord(v3d* &wCoord)    { this->worldCoord = wCoord; }
    // void setViewCoord(v3d* &vCoord)     { this->viewCoord = vCoord; }


    void draw(v3d* &coord) { glColor3f(1,1,1);  (GL_POINTS); glVertex3i(coord->x, coord->y, coord->z); glEnd(); }
    void draw(){ glColor3f(1,1,1);  glBegin(GL_POINTS); glVertex3i(worldCoord->x, worldCoord->y, worldCoord->z); glEnd(); }
    void draw(Vertex* start, Vertex* end) { glColor3f(1,1,1);  glBegin(GL_LINES); glVertex3f(start->worldCoord->x, start->worldCoord->y, start->worldCoord->z); glVertex3f(end->worldCoord->x, end->worldCoord->y, end->worldCoord->z); glEnd(); }
};


class Edge{
public:
    Vertex* startV;
    Vertex* endV;
    Edge* next;

    static std::string path ;

    Edge() { }
    Edge(Vertex*& start, Vertex*& end)              { startV = start; endV = end; }
    Edge(Vertex*& start, Vertex*& end, Edge*& next) { startV = start, endV = end; this->next = next; }

    Edge(double x1, double y1, double z1, double x2, double y2, double z2);

    void addEdge(double x2, double y2, double z2);

    static void initFileReader() { edgeFile.open(path, ios::binary | ios::in | ios::out | ios::app); }
    void loadVertex() { if (edgeFile.is_open()) { return; } }
    void saveVertex() { if (edgeFile.is_open()) { return; } }
    static void closeFileReader() { edgeFile.close(); }

    void draw(){ glColor3f(1,1,1); glBegin(GL_LINES); glVertex3d(startV->worldCoord->x, startV->worldCoord->y, startV->worldCoord->z); glVertex3d(endV->worldCoord->x,endV->worldCoord->y,endV->worldCoord->z); glEnd;}

};

class Surface {
public:
    int n, m;
    std::vector<std::vector<Vertex*>> vList; 
    // Surface* next;

    std::string path  = "Surface.dat";

    void initFileReader()  { surfaceFile.open(path, ios::binary | ios::in | ios::out | ios::app); }
    void closeFileReader() { surfaceFile.close(); }
    void loadData();


    static v3d viewpoint;

    void setViewPoint(double px, double py, double pz) { viewpoint = { px, py, pz}; }
  
    void drawLine(Vertex* &start, Vertex* &end) {
        glColor3f(1,1,1);  
        glBegin(GL_LINES); 
        glVertex3f(start->worldCoord->x, start->worldCoord->y, start->worldCoord->z); 
        glVertex3f(end->worldCoord->x, end->worldCoord->y, end->worldCoord->z); 
        glEnd(); 
        }

    void draw() {

        glPointSize(5.0); 
        
        for (int i = 0; i < n; i++){
            // 1 -> 2; 1->3; 2->4, 4->3
            Vertex* a = vList[i][0];
            Vertex* b = vList[i][1];
            Vertex* c = vList[i][2];
            Vertex* d = vList[i][3];
            
            drawLine(a, b);
            drawLine(a, d);
            drawLine(c, d);
            drawLine(c, b);

            // Vertex::draw(vList[i][1], vList[i][3]);
            // Vertex::draw(vList[i][2], vList[i][4]);
            // Vertex::draw(vList[i][3], vList[i][4]);
        }        

    }
};

        // Vertex* currentVertex = vList;
    // Edge* eList;

        // Edge* currentEdge = eList;

        // glLineWidth(2.0); 
        // while (currentEdge != nullptr) {
        //     currentEdge->draw();
        //     currentEdge = currentEdge->next;
        // }

        // while (currentVertex != nullptr) {
        //     currentVertex->draw();
        //     currentVertex = currentVertex->next;
        // }