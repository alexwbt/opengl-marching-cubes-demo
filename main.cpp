#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "window.h"
#include "shader.h"
#include "chunk.h"
#include "light.h"
#include "camera.h"

int main()
{
    if (Window::initWindow("OpenGL Marching Cubes Demo", 1080, 800) != 0)
    {
        std::cout << "Failed to initialize GLFW Window" << std::endl;
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Light::lights.push_back(&Light(glm::vec3(0.2f, -1.0f, 1.2f), { glm::vec3(0.25f), glm::vec3(1.0f), glm::vec3(1.0f) }));

    Chunk chunk;
    Camera camera;

    Shader shader({ "defaultVertexShader.vs", "defaultFragmentShader.fs" }, { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
    shader.use();
    shader.setFloat("specular", 0.2f);
    shader.setFloat("shininess", 16.0f);

    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    while (!glfwWindowShouldClose(Window::window))
    {
        float now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glClearColor(0.0f, 0.3f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Light::update(&shader);
        camera.update(deltaTime);
        shader.setVec3("cameraPos", camera.position);

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)Window::width / (float)Window::height, 0.1f, 100.0f);
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, -25.0f));
        shader.setMat4("model", model);
        shader.setMat4("pvm", projection * camera.viewMatrix * model);

        chunk.render();

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glfwTerminate();
}