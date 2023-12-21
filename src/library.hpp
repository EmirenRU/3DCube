#include "main.hpp"
#pragma once

static std::fstream file;

struct v3d{
    double x,y,z;
    v3d(double dx,double dy, double dz) : x(dx), y(dy), z(dz) { }
} ;

class Vertex{
public:
    int id;
    v3d* worldCoord;
    
    Vertex(int id, v3d* &wCoord );
    Vertex(double x, double y, double z);

    void setId(int id)                  { this->id = id; }
    void setWorldCoord(v3d* &wCoord)    { this->worldCoord = wCoord; }

    void draw(Vertex* &end);
};

class Surface {
public:
    const std::string path  = "Surface.dat";

    int n, m;
    std::vector<std::vector<Vertex*>> vList; 

    void loadData();  
    void draw();
};