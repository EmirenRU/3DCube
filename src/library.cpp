#include "library.hpp"

// Vertex::Vertex(GLDouble x, GLDouble y, GLDouble z) {
//     worldCoord = {x, y, z};
// }

// void Vertex::draw(Vertex* &end) { 
//     glColor3f(1,1,1);  
//     glBegin(GL_LINES); 
//     glVertex3d(this->worldCoord->x, this->worldCoord->y, this->worldCoord->z); 
//     glVertex3d(end->worldCoord->x, end->worldCoord->y, end->worldCoord->z); 
//     glEnd(); 
// }

Polygon::Polygon(Vertex* v0, Vertex* v1, Vertex* v2) {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}

// void Polygon::draw(){
//     for (int i = 0; i < 4; i++)
//         vertices[i]->draw(vertices[(i + 1) % 3]);
// }

// void Polygon::draw(Vertex a,Vertex b,Vertex c){
//     a.draw((Vertex*&)b);
//     a.draw((Vertex*&)c);
//     b.draw((Vertex*&)c);
// }

void Cube::draw() {
    if (vertices.empty()) {
        // Handle the case where vertices vector is empty
        return;
    }

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2 * vertices.size());
    glBindVertexArray(0);
}

vector<GLdouble> Vertex::data(){
    return {worldCoord->x, worldCoord->y, worldCoord->z};
}

// void Cube::draw(){
//     glBindVertexArray(vao);
//     glDrawArrays(GL_LINES, 0, 2 * vertices.size());
//     glBindVertexArray(0);
//     // for (int i = 0; i < 21; i+=3){
//     //     vertices.at(cubeConnectivity[i]).draw((Vertex*&)vertices[cubeConnectivity[i+1]]);
//     //     vertices.at(cubeConnectivity[i+1]).draw((Vertex*&)vertices[cubeConnectivity[i+2]]);
//     //     vertices.at(cubeConnectivity[i]).draw((Vertex*&)vertices[cubeConnectivity[i+2]]);
//     // }
// }

Cube::Cube(const std::string& filePath){
    loadVertices(filePath);
    setupBuffers();
}   

void Cube::loadVertices(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    int n, m;
    file >> n >> m;
    numVertices = n * m;

    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            GLdouble x,y,z;
            file >> x >> y >> z;
            vertices.push_back(new Vertex(x,y,z));
        }
    }

    file.close();
}

void Cube::setupBuffers() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Assuming vertices is a vector<Vertex*>
     std::vector<GLdouble> vertexData;
    for (const auto& vertexPtr : vertices) {
        vertexData.push_back(vertexPtr->worldCoord->x);
        vertexData.push_back(vertexPtr->worldCoord->y);
        vertexData.push_back(vertexPtr->worldCoord->z);
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(GLdouble) * 3, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

const GLushort  Cube::cubeConnectivity[] = {
        0, 1, 2,  2, 1, 3,    /* front */
        4, 5, 6,  6, 5, 7,    /* back */
        8, 9,10, 10, 9,11,    /* left */
        12,13,14, 14,13,15,   /* right */
        16,17,18, 18,17,19,   /* top */
        20,21,22, 22,21,23    /* bottom */
    };


short Cube::getNumVertices(){
    return numVertices;
}