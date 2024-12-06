#include "Box.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static constexpr int SCREEN_SIZE = 800;
static constexpr int BOX_SIZE = 100;

auto box = Box(BOX_SIZE, BOX_SIZE, BOX_SIZE);

void onScreen() {
    if (box.getOffsetX() + BOX_SIZE > SCREEN_SIZE) {
        box.setOffsetX(SCREEN_SIZE - BOX_SIZE);
    }

    if (box.getOffsetX() < 0) {
        box.setOffsetX(0);
    }

    if (box.getOffsetY() + BOX_SIZE > SCREEN_SIZE) {
        box.setOffsetY(SCREEN_SIZE - BOX_SIZE);
    }

    if (box.getOffsetY() < 0) {
        box.setOffsetY(0);
    }
}

void cursorPosCallback(GLFWwindow* window, const double xPos, const double yPos) {
    box.drag(xPos, yPos);
    onScreen();
}

void mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            double xPos, yPos;
            glfwGetCursorPos(window, &xPos, &yPos);

            if (box.isInnerPoint(xPos, yPos)) {
                box.startDragging(xPos, yPos);
            } else {
                box.moveTo(xPos, yPos);
            }
        } else if (action == GLFW_RELEASE) {
            box.stopDragging();
        }

        onScreen();
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error while initializing GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCREEN_SIZE, SCREEN_SIZE, "Box", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error while creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_SIZE, SCREEN_SIZE, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        box.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
