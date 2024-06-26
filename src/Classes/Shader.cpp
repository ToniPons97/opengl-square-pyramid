#include "Shader.h"

Shader::Shader() 
{
    shaderID = 0, uniformModel = 0, uniformProjection = 0;
}

void Shader::CreateFromString(const char *vertexCode, const char *fragmentCode) 
{
    CompileShader(vertexCode, fragmentCode);
} 

void Shader::CreateFromFiles(const char *vertexFilePath, const char *fragmentFilePath) {
    std::string vertexString = ReadFile(vertexFilePath);
    std::string fragmentString = ReadFile(fragmentFilePath);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char *filepath) {
    std::string content;
    std::ifstream fileStream(filepath, std::ios::in);

    if (!fileStream.is_open()) 
    {
        std::cout << "Failed to read file: " << filepath << std::endl;
        return "";
    }

    std::string line = "";

    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
    shaderID = glCreateProgram();

    if (!shaderID)
    {
        std::cout << "Error creating shader program." << std::endl;
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);

        std::cout << "Error linking shader program: " << eLog << std::endl;
        return;
    }

    glValidateProgram(shaderID);
    glGetShaderiv(shaderID, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);

        std::cout << "Error validating shader program: " << eLog << std::endl;
        return;
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
}

void Shader::AddShader(GLuint program, const char *shaderCode, GLenum shaderType) 
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);

        std::cout << "Error compiling the " << shaderType << " shader program: " << eLog << std::endl;
        return;
    }

    glAttachShader(program, theShader);
}

GLuint Shader::GetModelLocation() 
{
    return uniformModel;
}

GLuint Shader::GetProjectionLocation() 
{
    return uniformProjection;
}

void Shader::UseShader() 
{
    glUseProgram(shaderID);
}

void Shader::ClearShader() 
{
    if (shaderID != 0) 
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0, uniformProjection = 0;
}

GLuint Shader::GetShaderProgram()
{
    return shaderID;
}

Shader::~Shader()
{
    ClearShader();
}