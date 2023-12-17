#include "library.hpp"

Edge::Edge(double x1, double y1, double z1, double x2, double y2, double z2){
    v3d *a = new v3d( x1, y1, z1);
    v3d *b = new v3d(x2, y2, z2);

    Vertex* va = new Vertex(1, a);
    Vertex* vb = new Vertex(1, b);

    this->startV = va;
    this->endV = vb;
}

void Edge::addEdge(double x2, double y2, double z2){

}

void Surface::loadData(){
    try {
        initFileReader();

        surfaceFile >> n >> m; 
        
        vList = new Vertex[n];
        
        for (int i = 0; i < n; i++){ vList[i] = new Vertex[m]; } 
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                double x, y, z;
                
                surfaceFile >> x >> y >> z;

                vList[i][j] = new Vertex(x, y, z);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        
    }
    closeFileReader();
}

Vertex::Vertex(double x, double y, double z){
    worldCoord = new v3d(x,y,z);
}

int Vertex::UID = 0;

std::string    Edge::path = "Edge.txt";
std::string Surface::path = "Surface.txt";
