#pragma once

#include <GL/glew.h>

class Mesh {
    public:
        Mesh();
        ~Mesh();

        void CreateMesh(GLfloat *vertices, GLuint *indices, unsigned int verticesBufferSize, unsigned int indicesBufferSize);
        void RenderMesh();
        void ClearMesh();

    private:
        GLuint VAO, IBO, VBO;
        GLsizei indexCount;
};