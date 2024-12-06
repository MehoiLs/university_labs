#include "Figure.h"

Figure::Figure(const int _size, const int _offsetX, const int _offsetY) {
    size = _size;
    offsetX = _offsetX;
    offsetY = _offsetY;
}


void Figure::moveTo(const int x, const int y) {
    offsetX = x - size / 2;
    offsetY = y - size / 2;
}


void Figure::move(const int x, const int y) {
    offsetX += x;
    offsetY += y;
}


void Figure::startDragging(const int x, const int y) {
    dragging = true;
    previousX = x;
    previousY = y;
}


void Figure::drag(const int x, const int y) {
    if (isDragging()) {
        move(x - previousX, y - previousY);
        previousX = x;
        previousY = y;
    }
}


bool Figure::isDragging() const {
    return dragging;
}


void Figure::stopDragging() {
    dragging = false;
}

int Figure::getSize() const {
    return size;
}


int Figure::getOffsetX() const {
    return offsetX;
}


int Figure::getOffsetY() const {
    return offsetY;
}

void Figure::setSize(const int _size) {
    size = _size;
}


void Figure::setOffsetX(const int _xPos) {
    offsetX = _xPos;
}

void Figure::setOffsetY(const int _yPos) {
    offsetY = _yPos;
}