#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline glm::mat3 Translation(const double x, const double y)
{
    auto translationMatrix = glm::mat3(1.0f);
    translationMatrix[2][0] = x;
    translationMatrix[2][1] = y;
    return translationMatrix;
}

inline glm::mat3 Rotation(const double angle)
{
    const double rad = glm::radians(angle);
    const auto rotationMatrix = glm::mat3(
        std::cos(rad), -std::sin(rad), 0.0f,
        std::sin(rad), std::cos(rad), 0.0f,
        0.0f, 0.0f, 1.0f
    );
    return rotationMatrix;
}

inline glm::mat3 Identity()
{
    return {1.0f};
}

#endif