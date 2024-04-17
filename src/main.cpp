#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <cmath>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include <stdio.h>

void CreateObjects();
void CreateShaders();
void SetRotations(GLFWwindow *window, glm::vec2 *rotations, float* rotationAmount);
void UpdateColor(Shader* shader);

GLint WIDTH = 800, HEIGHT = 600;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

GLuint uniformModel = 0, uniformProjection = 0;

Window* mainWindow = new Window(WIDTH, HEIGHT);

// Vertex shader
static const char *vShader = "src/Shaders/shader.vert";

// Fragment shader
static const char *fShader = "src/Shaders/shader.frag";

int main(void)
{
    mainWindow->CreateWindow();

    CreateObjects();
    CreateShaders();
    shaderList[0].UseShader();

    GLfloat aspectRatio = 0;
    
    glm::mat4 projection = glm::mat4(1.0f);

    // Rotations variables
    bool isKeyPressed;
    glm::vec2 rotations = glm::vec2(0.1f);
    float rotationAmount;

    GLFWwindow* window = mainWindow->GetWindowPtr();
    // Render loop
    while (mainWindow->WindowShouldClose())
    {
        // User input
        mainWindow->CloseWindowOnKeyPress();
        mainWindow->TogglePolygonMode();

        // Control rotations through keyboard inputs
        isKeyPressed = mainWindow->IsArrowKeyPressed();
        rotationAmount = isKeyPressed ? 2.0f : 0.0f;
        SetRotations(window, &rotations, &rotationAmount);

        // Get and handle user input events
        glfwPollEvents();

        // Clear the screen with the provided (RGBA) color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        aspectRatio = mainWindow->GetAspectRatio();
        projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(5.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        
        // X rotation
        model = glm::rotate(model, glm::radians(std::fmod(rotations.x, 360.0f)), glm::vec3(0.0f, 1.0f, 0));
        
        // Y rotation
        model = glm::rotate(model, glm::radians(std::fmod(rotations.y, 360.0f)), glm::vec3(1.0f, 0.0f, 0));
        
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        meshList[0]->RenderMesh();

        // Siwtch buffers
        mainWindow->SwapBuffers();

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {
            UpdateColor(&shaderList[0]);
        }
    }

    glUseProgram(0);
    glfwTerminate();
    return 0;
}

void CreateObjects()
{
    // Square pyramid
    GLfloat vertices[] = {
        // Base vertices
        -1.0f, -1.0f, -1.0f, // 0 bottom left back
        1.0f, -1.0f, -1.0f,  // 1 bottom right back
        -1.0f, -1.0f, 1.0f,  // 2 bottom left front
        1.0f, -1.0f, 1.0f,   // 3 bottom right front

        // Apex vertex
        0.0f, 1.0f, 0.0f // 4 top center
    };

    GLuint indices[] = {
        // Base
        0, 1, 2, // Triangle 1
        2, 1, 3, // Triangle 2

        // Sides
        0, 2, 4, // Triangle 3
        1, 0, 4, // Triangle 4
        3, 1, 4, // Triangle 5
        2, 3, 4  // Triangle 6
    };

    Mesh* obj1 = new Mesh();

    obj1->CreateMesh(vertices, indices, sizeof(vertices), sizeof(indices));
    meshList.push_back(obj1);
}



void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    uniformModel = shaderList[0].GetModelLocation();
    uniformProjection = shaderList[0].GetProjectionLocation();
}

void SetRotations(GLFWwindow* window, glm::vec2* rotations, float* rotationAmount)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotations->x = std::fmod(rotations->x - *rotationAmount, 360.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotations->x = std::fmod(rotations->x + *rotationAmount, 360.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotations->y = std::fmod(rotations->y + *rotationAmount, 360.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotations->y = std::fmod(rotations->y - * rotationAmount, 360.0f);
    }
}

void UpdateColor(Shader *shader)
{
    GLuint shaderProgram = shader->GetShaderProgram();


    GLfloat greenValue = sin(glfwGetTime()) * 0.5f + 0.5f;
    GLfloat redValue = cos(2* glfwGetTime()) * 0.5f + 0.5f;
    GLfloat blueValue = sin(3 * glfwGetTime()) * 0.5f + 0.5f;

    GLint uniformColorLoc = glGetUniformLocation(shaderProgram, "varColor");
    glUniform4f(uniformColorLoc, redValue, greenValue, blueValue, 1.0f);
}