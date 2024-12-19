#include "Model2D.h"

#include "AffineTransform.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

Model2D::Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices)
    : mVertices(vertices), mIndices(indices), mModelMatrix(Identity()) {}

void Model2D::translate(const float x, const float y) {
    mModelMatrix = Translation(x, y) * mModelMatrix;
}

void Model2D::rotate(const float angle) {
    mModelMatrix = Rotation(angle) * mModelMatrix;
}

void Model2D::draw() const {
    if (mVertices.empty() || mIndices.empty()) {
        return;
    }

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (size_t i = 0; i < mIndices.size() - 1; ++i) {
        glVertex2f(
            (mModelMatrix * glm::vec3(mVertices[mIndices[i]], 1.0f)).x,
            (mModelMatrix * glm::vec3(mVertices[mIndices[i]], 1.0f)).y
        );
        glVertex2f(
            (mModelMatrix * glm::vec3(mVertices[mIndices[i+1]], 1.0f)).x,
            (mModelMatrix * glm::vec3(mVertices[mIndices[i+1]], 1.0f)).y
        );
    }

    glEnd();
}
