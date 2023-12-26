#include "library.hpp"

// Vertex::Vertex(GLDouble x, GLDouble y, GLDouble z) {
//     worldCoord = {x, y, z};
// }

void Vertex::draw(Vertex* &end) { 
    glColor3f(1,1,1);  
    glBegin(GL_LINES); 
    glVertex3d(this->worldCoord->x, this->worldCoord->y, this->worldCoord->z); 
    glVertex3d(end->worldCoord->x, end->worldCoord->y, end->worldCoord->z); 
    glEnd(); 
}

void Polygon::draw(){
    for (int i = 0; i < 4; i++)
        vertices[i]->draw(vertices[(i + 1) % 3]);
}

void Polygon::draw(Vertex a,Vertex b,Vertex c){
    a.draw((Vertex*&)b);
    a.draw((Vertex*&)c);
    b.draw((Vertex*&)c);
}

void Cube::draw(){       
    for (int i = 0; i < 24; i+=1){
        std::cout << glm::pi<float>() <<std::endl;
        vertices[cubeConnectivity[i]]->draw(vertices[cubeConnectivity[i+1]]);
        vertices[cubeConnectivity[i+1]]->draw(vertices[cubeConnectivity[i+2]]);
        vertices[cubeConnectivity[i]]->draw(vertices[cubeConnectivity[i+2]]);
    }
}

void Cube::loadVertices(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    int n, m;
    file >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++){
            GLdouble x, y, z;
            file >> x >> y >> z;
            std::cout << x  << " " << y << " " << z << std::endl;
            std::cout << i * m + j << std::endl;
            vertices[i * m + j] = new Vertex(x, y, z);
        }
    }

    file.close();
}

const GLushort  Cube::cubeConnectivity[] = {
        0, 1, 2,  2, 1, 3,    /* front */
        4, 5, 6,  6, 5, 7,    /* back */
        8, 9,10, 10, 9,11,    /* left */
        12,13,14, 14,13,15,   /* right */
        16,17,18, 18,17,19,   /* top */
        20,21,22, 22,21,23    /* bottom */
    };