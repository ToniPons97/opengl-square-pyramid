#pragma once

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <GL/glew.h>

class Shader {
    public:
        Shader();
        ~Shader();

        void CreateFromString(const char* vertexCode, const char* fragmentCode);
        void CreateFromFiles(const char* vertexFilePath, const char* fragmentFilePath);
        GLuint GetProjectionLocation();
        std::string ReadFile(const char* filepath);
        GLuint GetModelLocation();
        void UseShader();
        void ClearShader();
        GLuint GetShaderProgram();

    
    private:
        GLuint shaderID, uniformModel, uniformProjection;

        void CompileShader(const char *vertexCode, const char *fragmentCode);
        void AddShader(GLuint program, const char *shaderCode, GLenum shaderType);
};