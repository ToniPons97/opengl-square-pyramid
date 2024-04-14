#include "Window.h"

Window::Window(GLint width, GLint height)
{
    this->width = width;
    this->height = height;
    screenWidth = 0;
    screenHeight = 0;
}

void Window::CreateWindow()
{
    // Initialize GLFW
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "Couldn't initialize GLFW." << std::endl;
        glfwTerminate();
        return;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Required for Mac
    // Core profile = no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello OpenGL!", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();

        return;
    }

    // Get buffer size information
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, WindowSizeCallback);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();

        return;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Setup viewport size
    glViewport(0, 0, screenWidth, screenHeight);

    this->window = window;
}

void Window::WindowSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int Window::WindowShouldClose()
{
    return !glfwWindowShouldClose(window);
}

GLfloat Window::GetAspectRatio()
{
    return (GLfloat) width / (GLfloat) height;
}

void Window::CloseWindowOnKeyPress()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Window::TogglePolygonMode()
{
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

bool Window::IsArrowKeyPressed()
{
    return (
        glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS 
            || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS 
            || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS 
            || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS
    );
}

GLFWwindow* Window::GetWindowPtr()
{
    return window;
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}