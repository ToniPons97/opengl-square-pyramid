#pragma once

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window {
    public:
        Window();
        Window(GLint width, GLint height);
        void CreateWindow();
        int WindowShouldClose(); 
        GLfloat GetAspectRatio();
        void CloseWindowOnKeyPress();
        void TogglePolygonMode();
        bool IsArrowKeyPressed();
        GLFWwindow* GetWindowPtr();
        void SwapBuffers();

    private : GLFWwindow *window;
        GLfloat aspectRatio;
        GLint width, height;
        int screenHeight, screenWidth;
        static void WindowSizeCallback(GLFWwindow *window, int width, int height);
};