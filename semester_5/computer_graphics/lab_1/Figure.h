#pragma once
class Figure {

    bool dragging = false;
    int previousX = 0, previousY = 0;

protected:

    int size, offsetX, offsetY;

public:

    Figure(int _size, int _offsetX, int _offsetY);

    virtual ~Figure() = default;

    virtual void draw() = 0;
    virtual bool isInnerPoint(int x, int y) = 0;

    void moveTo(int x, int y);

    void move(int x, int y);

    void startDragging(int x, int y);

    void drag(int x, int y);

    bool isDragging() const;

    void stopDragging();

    int getSize() const;

    int getOffsetX() const;

    int getOffsetY() const;

    void setSize(int _size);

    void setOffsetX(int _xPos);

    void setOffsetY(int _yPos);

};
