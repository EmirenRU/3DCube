#include "library.hpp"

Vertex::Vertex(int id, v3d* &wCoord ){
    this->id = id; 
    this->worldCoord = wCoord; 
}

void Vertex::draw(Vertex* &end) { 
    glColor3f(1,1,1);  
    glBegin(GL_LINES); 
    glVertex3f(this->worldCoord->x, this->worldCoord->y, this->worldCoord->z); 
    glVertex3f(end->worldCoord->x, end->worldCoord->y, end->worldCoord->z); 
    glEnd(); 
}

void Surface::draw(){
        glPointSize(5.0); 
        
        for (int i = 0; i < n; i++){
            vList[i][0]->draw( (Vertex*&) vList[i][1]);
            vList[i][0]->draw( (Vertex*&) vList[i][3]);
            vList[i][2]->draw( (Vertex*&) vList[i][3]);
            vList[i][2]->draw(  (Vertex*&) vList[i][1]);
        }        
    }

void Surface::loadData(){
    file.open(path);
    if (!file.is_open()){ return; }
        
    file >> n >> m; 
    for (int i = 0; i < n; i++){
        std::vector<Vertex*> temp;
        for (int j = 0; j < m; j++){
            double x, y, z;
            file >> x >> y >> z;

            temp.push_back(new Vertex(x,y,z));
        }
        vList.push_back(temp);
    }
    file.close();
}

Vertex::Vertex(double x, double y, double z){ worldCoord = new v3d(x,y,z); }

