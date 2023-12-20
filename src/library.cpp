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
        // initFileReader();
        surfaceFile.open(path);


        surfaceFile >> n >> m; 
        
        for (int i = 0; i < n; i++){
            std::vector<Vertex*> temp;
            for (int j = 0; j < m; j++){
                double x, y, z;
                
                surfaceFile >> x >> y >> z;

                temp.push_back(new Vertex(x,y,z));
            }

            vList.push_back(temp);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        
    }
    closeFileReader();
}

void Surface::saveData(){
    std::fstream surfaceFile;
    std::ofstream fWriter; // Use ofstream for writing to a file
    std::string path = "Surface.txt";
    std::string file = "Surface.dat";

    surfaceFile.open(path);
    fWriter.open(file, std::ios::out);

    if (!surfaceFile.is_open() || !fWriter.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    int n, m;
    int a, b, c;
    surfaceFile >> n >> m;
    fWriter << n << " " << m << std::endl;
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            surfaceFile >> a >> b >> c;
            fWriter << a << " " << b << " " << c << "\n";
        }
    }

    fWriter.close();
    surfaceFile.close();

}

Vertex::Vertex(double x, double y, double z){
    worldCoord = new v3d(x,y,z);
}

int Vertex::UID = 0;

// std::string    Edge::path = "Edge.txt";
// std::string Surface::path = "Surface.txt";
