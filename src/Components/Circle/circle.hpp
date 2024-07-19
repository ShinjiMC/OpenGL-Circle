#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Components/DDA/dda.hpp"
#include <GL/glut.h>
#include <vector>

class Circle
{
private:
    int xCenter, yCenter, radius;
    float red, green, blue;

    void setPixel(int x, int y) const;
    void circlePoints(int x, int y) const;
    void circleMidPoint() const;
    void adjustPercentages(std::vector<float> &percentages) const;

public:
    Circle(int x, int y, int radius, float r, float g, float b);

    void drawCircle() const;
    void drawPieChart(const std::vector<float> &percentages) const;
};

#endif // CIRCLE_HPP
