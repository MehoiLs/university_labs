#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Model2D.h"
#include "Render2D.h"
#include <iostream>

Render2D render;
Model2D model;
size_t currentModelIndex = 0;

static constexpr float DEFAULT_ROTATION_ANGLE = 30.0f;
static constexpr float DEFAULT_TRANSLATION_SIZE = 0.1f;

void keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP: {
                model.translate(0.0f, DEFAULT_TRANSLATION_SIZE);
                break;
            }
            case GLFW_KEY_DOWN: {
                model.translate(0.0f, -DEFAULT_TRANSLATION_SIZE);
                break;
            }
            case GLFW_KEY_LEFT: {
                model.translate(-DEFAULT_TRANSLATION_SIZE, 0.0f);
                break;
            }
            case GLFW_KEY_RIGHT: {
                model.translate(DEFAULT_TRANSLATION_SIZE, 0.0f);
                break;
            }
            case GLFW_KEY_R: {
                model.rotate(DEFAULT_ROTATION_ANGLE);
                break;
            }
            default: break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Cannot initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version to 2.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Cannot create a GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // Define vertices and indices for the model
    const std::vector vertices = {
        glm::vec2(-0.4, -0.4),
        glm::vec2(-0.4, 0.4),
        glm::vec2(0.4, 0.4),
        glm::vec2(0.4, -0.4),
        glm::vec2(0.0, -0.8)
    };
    const std::vector indices = {0, 1, 2, 3, 4, 0};

    model = Model2D(vertices, indices);
    render.addObject(&model);

    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer with white color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}