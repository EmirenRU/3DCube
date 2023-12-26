#include "library.hpp"

Polygon::Polygon(Vertex* v0, Vertex* v1, Vertex* v2) {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}

void Cube::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vbo);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
    glBindVertexArray(0);
}

vector<GLdouble> Vertex::data(){
    return {worldCoord->x, worldCoord->y, worldCoord->z};
}

Cube::Cube(const std::string& filePath){
    cubeConnectivity =  {
        0, 1, 2,  2, 1, 3,    /* front */
        4, 5, 6,  6, 5, 7,    /* back */
        8, 9,10, 10, 9,11,    /* left */
        12,13,14, 14,13,15,   /* right */
        16,17,18, 18,17,19,   /* top */
        20,21,22, 22,21,23    /* bottom */
    };

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
    glBindVertexArray(vao);


    for (const auto& vertexPtr : vertices) {
        if (vertexPtr && vertexPtr->worldCoord) {
            vertexData.push_back(vertexPtr->worldCoord->x);
            vertexData.push_back(vertexPtr->worldCoord->y);
            vertexData.push_back(vertexPtr->worldCoord->z);
        }
    }   

    glGenBuffers(3, &vbo);  // Generate a buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, vbo);  // Bind the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * vertexData.size(), &vertexData.front(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeConnectivity.size() * sizeof(GLuint), &cubeConnectivity.front(), GL_STATIC_DRAW);
 
    
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(GLdouble) * 3, BUFFER_OFFSET(0));
    glVertexAttribPointer(2,4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLdouble), BUFFER_OFFSET(0));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

short Cube::getNumVertices(){
    return numVertices;
}

Cube::~Cube(){
    vertices.clear();
    vertexData.clear();
    vao = vbo = ebo = 0;
}