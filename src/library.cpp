#include "library.hpp"

Polygon::Polygon(Vertex* v0, Vertex* v1, Vertex* v2) {
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}

void Cube::draw() {
    glBindVertexArray(vbo);
    glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_SHORT, NULL);
    glBindVertexArray(0);
}

vector<GLdouble> Vertex::data(){
    return {worldCoord->x, worldCoord->y, worldCoord->z};
}

Cube::Cube(const std::string& filePathVertics, const std::string& filePathConnectivity){
    loadVertices(filePathVertics, filePathConnectivity);
    setupBuffers();
}   

void Cube::loadVertices(const std::string& filePath,  const std::string& filePathConnectivity) {
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

    glGenBuffers(3, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeConnectivity.size() * sizeof(GLuint), &cubeConnectivity.front(), GL_STATIC_DRAW);
 
    
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_TRUE, sizeof(GLdouble) * 3, NULL);
    glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLubyte), NULL);
    
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