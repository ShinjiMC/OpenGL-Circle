#include "circle.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>

// Asume que tienes una función para dibujar texto
void renderBitmapString(float x, float y, void *font, const std::string &string)
{
    glRasterPos2f(x, y);
    for (char c : string)
        glutBitmapCharacter(font, c);
}

Circle::Circle(int x, int y, int radius, float r, float g, float b)
    : xCenter(x), yCenter(y), radius(radius), red(r), green(g), blue(b) {}

void Circle::drawCircle() const
{
    glColor3f(red, green, blue);
    glBegin(GL_POINTS);
    circleMidPoint();
    glEnd();
}

void Circle::setPixel(int x, int y) const
{
    glVertex2i(x, y);
}

void Circle::circlePoints(int x, int y) const
{
    setPixel(xCenter + x, yCenter + y);
    setPixel(xCenter - x, yCenter + y);
    setPixel(xCenter + x, yCenter - y);
    setPixel(xCenter - x, yCenter - y);
    setPixel(xCenter + y, yCenter + x);
    setPixel(xCenter - y, yCenter + x);
    setPixel(xCenter + y, yCenter - x);
    setPixel(xCenter - y, yCenter - x);
}

void Circle::circleMidPoint() const
{
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    circlePoints(x, y);
    while (x < y)
    {
        x++;
        if (p < 0)
        {
            p += 2 * x + 1;
        }
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        circlePoints(x, y);
    }
}

void Circle::drawPieChart(const std::vector<float> &percentages) const
{
    std::vector<float> adjusted = percentages;
    adjustPercentages(adjusted);

    float startAngle = 0.0f;
    for (float percentage : adjusted)
    {
        float endAngle = startAngle + (percentage * 360.0f / 100.0f);
        float startAngleRad = startAngle * M_PI / 180.0f;
        float endAngleRad = endAngle * M_PI / 180.0f;

        // Draw pie chart lines using DDA
        DDA lineStart(this->red, this->green, this->blue, xCenter, yCenter,
                      xCenter + radius * cos(startAngleRad),
                      yCenter + radius * sin(startAngleRad), "dashed");
        lineStart.drawLine();

        DDA lineEnd(this->red, this->green, this->blue, xCenter, yCenter,
                    xCenter + radius * cos(endAngleRad),
                    yCenter + radius * sin(endAngleRad), "dashed");
        lineEnd.drawLine();

        // Render percentage text
        float textX = xCenter + (radius + 10) * cos((startAngleRad + endAngleRad) / 2.0f);
        float textY = yCenter + (radius + 10) * sin((startAngleRad + endAngleRad) / 2.0f);
        std::string text = std::to_string(percentage) + "%";
        renderBitmapString(textX, textY, GLUT_BITMAP_HELVETICA_12, text);

        startAngle = endAngle;
    }
}

void Circle::adjustPercentages(std::vector<float> &percentages) const
{
    float sum = 0;
    for (float p : percentages)
        sum += p;
    if (sum != 100.0f)
    {
        if (sum > 100.0f)
        {
            float difference = sum - 100.0f;
            for (float &p : percentages)
            {
                float reduction = (p / sum) * difference;
                p -= reduction;
            }
        }
        else
        {
            float difference = 100.0f - sum;
            percentages.push_back(difference);
        }
    }
}
