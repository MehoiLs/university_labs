#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 800;

static float SIDE_LENGTH = 0.5f;
static float COLOR[3] = { 1.0f, 0.0f, 0.0f };

void drawSquare(const float sideLength) {
    glBegin(GL_QUADS);
    glColor3f(COLOR[0], COLOR[1], COLOR[2]);

    glVertex2f(-SIDE_LENGTH, -SIDE_LENGTH);
    glVertex2f(SIDE_LENGTH, -SIDE_LENGTH);
    glVertex2f(SIDE_LENGTH, SIDE_LENGTH);
    glVertex2f(-SIDE_LENGTH, SIDE_LENGTH);
    glEnd();
}

void keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_Q) {
            COLOR[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            COLOR[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            COLOR[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }
    }
}

void mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && SIDE_LENGTH < 1.0f) {
            SIDE_LENGTH += 0.1f;
        } else if (button == GLFW_MOUSE_BUTTON_LEFT && SIDE_LENGTH > 0.2f) {
            SIDE_LENGTH -= 0.1f;
        }
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    const auto window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "[GLFW/GLEW] Square",
        nullptr,
        nullptr
    );
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSquare(SIDE_LENGTH);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}