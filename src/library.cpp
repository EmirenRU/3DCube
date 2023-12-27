#include "library.hpp"


Cube::Cube(const std::string& filePathVertics, const std::string& filePathConnectivity, const std::string& filePathColor){
    loadVertices(filePathVertics, filePathConnectivity, filePathColor);
    setupBuffers();
}   

void Cube::loadVertices(const std::string& filePath,  const std::string& filePathConnectivity, const std::string& filePathColor) {
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

    file.open(filePathConnectivity);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    GLushort temp;

    while(file >> temp){ cubeConnectivity.push_back(temp); }

    file.close();

    file.open(filePathColor);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    GLdouble r,g,b,a;
    file >> r >> g >> b >> a;

    for (int i = 0; i < numVertices; i++){
        vertices.at(i)->worldCoord->color.r = r;
        vertices.at(i)->worldCoord->color.g = g;
        vertices.at(i)->worldCoord->color.b = b;
        vertices.at(i)->worldCoord->color.a = a;
    }

    file.close();
    
}



void Cube::setupBuffers() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    for (const auto& vertexPtr : vertices) {
        if (vertexPtr && vertexPtr->worldCoord) {
            vertexData.push_back(vertexPtr->worldCoord->x);
            vertexData.push_back(vertexPtr->worldCoord->y);
            vertexData.push_back(vertexPtr->worldCoord->z);

            vertexData.push_back(vertexPtr->worldCoord->color.r);
            vertexData.push_back(vertexPtr->worldCoord->color.g);
            vertexData.push_back(vertexPtr->worldCoord->color.b);
            vertexData.push_back(vertexPtr->worldCoord->color.a);

        }
    }   

    glGenBuffers(3, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * vertexData.size(), &vertexData.front(), GL_STATIC_DRAW);

    glGenBuffers(3, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeConnectivity.size() * sizeof(GLuint), &cubeConnectivity.front(), GL_STATIC_DRAW);
 
    
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_TRUE, sizeof(GLdouble) * 7, NULL);
    glVertexAttribPointer(1, 4, GL_DOUBLE, GL_TRUE, sizeof(GLdouble) * 7, (void*)(sizeof(GLdouble) * 3));   
    glVertexAttribPointer(2, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLubyte), NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void Cube::draw() {
    glBindVertexArray(vbo);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
}

short Cube::getNumVertices(){
    return numVertices;
}

Cube::~Cube(){
    vertices.clear();
    vertexData.clear();
    vao = vbo = ebo = 0;
}