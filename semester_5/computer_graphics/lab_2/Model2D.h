#pragma once

#include <glm/glm.hpp>
#include <vector>

class Model2D {
public:
    Model2D() = default;
    Model2D(const std::vector<glm::vec2>& vertices, const std::vector<int>& indices);

    void translate(float x, float y);
    void rotate(float angle);

    void draw();

private:
    std::vector<glm::vec2> mVertices;
    std::vector<int> mIndices;
    glm::mat3 mModelMatrix{};
};