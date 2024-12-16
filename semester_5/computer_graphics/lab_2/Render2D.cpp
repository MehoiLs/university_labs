#include "Render2D.h"

#include <glad/glad.h>

void Render2D::draw()
{
    for (const auto model : mObjects) {
        model->draw();
    }
}

Render2D::~Render2D() = default;

void Render2D::addObject(Model2D* model)
{
    mObjects.push_back(model);
}

void Render2D::clearObjects()
{
    mObjects.clear();
}