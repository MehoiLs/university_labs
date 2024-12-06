#include "Box.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static constexpr int WINDOW_SIZE = 800;
static constexpr int BOX_SIZE = 100;

auto box = Box(BOX_SIZE, BOX_SIZE, BOX_SIZE);

/**
 * Sets the coordinates of the Box so that in remains within the window screen.
 */
void assertWithinScreen() {
    if (box.getOffsetX() + BOX_SIZE > WINDOW_SIZE) {
        box.setOffsetX(WINDOW_SIZE - BOX_SIZE);
    }

    if (box.getOffsetX() < 0) {
        box.setOffsetX(0);
    }

    if (box.getOffsetY() + BOX_SIZE > WINDOW_SIZE) {
        box.setOffsetY(WINDOW_SIZE - BOX_SIZE);
    }

    if (box.getOffsetY() < 0) {
        box.setOffsetY(0);
    }
}

void cursorPosCallback(GLFWwindow* window, const double xPos, const double yPos) {
    box.drag(xPos, yPos);
    assertWithinScreen();
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

        assertWithinScreen();
    }
}

void initGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_SIZE, WINDOW_SIZE, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void renderPrimitives() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    box.draw();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error while initializing GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Box", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error while creating GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    initGL();
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window)) {
        renderPrimitives();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
