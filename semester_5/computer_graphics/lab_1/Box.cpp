#include "Box.h"
#include <GL/gl.h>

Box::Box(const int size, const int offsetX, const int offsetY) : Figure(size, offsetX, offsetY) {}

void Box::draw() {
    glColor3f(0.0f, 0.5f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(getOffsetX(), getOffsetY());
    glVertex2f(getOffsetX() + getSize(), getOffsetY());
    glVertex2f(getOffsetX() + getSize(), getOffsetY() + getSize());
    glVertex2f(getOffsetX(), getOffsetY() + getSize());
    glEnd();
}

bool Box::isInnerPoint(int x, int y) {
    return x >= getOffsetX() && x <= getOffsetX() + getSize() &&
           y >= getOffsetY() && y <= getOffsetY() + getSize();
}


