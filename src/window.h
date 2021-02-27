#pragma once

struct GLFWwindow;

class Window
{
public:
    static GLFWwindow* window;
    static int initWindow(const char* title, int width, int height);

    static int width, height;
private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
