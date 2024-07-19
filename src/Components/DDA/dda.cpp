#include "dda.hpp"

DDA::DDA(float r, float g, float b, float x1, float y1, float x2, float y2, std::string style)
    : red(r), green(g), blue(b), x_start(x1), y_start(y1), x_end(x2), y_end(y2), line_style(style) {}

void DDA::drawPoint(int x, int y, bool visible)
{
    if (visible)
    {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

void DDA::drawLine()
{
    glColor3f(red, green, blue);

    int x1 = static_cast<int>(x_start);
    int y1 = static_cast<int>(y_start);
    int x2 = static_cast<int>(x_end);
    int y2 = static_cast<int>(y_end);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float x_inc = dx / static_cast<float>(steps);
    float y_inc = dy / static_cast<float>(steps);

    float x = x1;
    float y = y1;

    int patternIndex = 0;
    int patternLength = 1;
    bool pattern[] = {true}; // Solid line as default

    if (line_style == "dashed")
    {
        bool tempPattern[] = {true, true, true, true, false, false, false, false};
        patternLength = sizeof(tempPattern) / sizeof(tempPattern[0]);
        std::copy(tempPattern, tempPattern + patternLength, pattern);
    }
    else if (line_style == "dotted")
    {
        bool tempPattern[] = {true, false};
        patternLength = sizeof(tempPattern) / sizeof(tempPattern[0]);
        std::copy(tempPattern, tempPattern + patternLength, pattern);
    }

    for (int i = 0; i <= steps; ++i)
    {
        drawPoint(static_cast<int>(x), static_cast<int>(y), pattern[patternIndex]);
        x += x_inc;
        y += y_inc;
        patternIndex = (patternIndex + 1) % patternLength;
    }
}

void DDA::printPoints()
{
    int x1 = static_cast<int>(x_start);
    int y1 = static_cast<int>(y_start);
    int x2 = static_cast<int>(x_end);
    int y2 = static_cast<int>(y_end);

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float x_inc = dx / static_cast<float>(steps);
    float y_inc = dy / static_cast<float>(steps);

    float x = x1;
    float y = y1;
    std::cout << "DDA: (" << x_start << ", " << y_start << ") -> (" << x_end << ", " << y_end << ")" << std::endl;
    for (int i = 0; i <= steps; ++i)
    {
        std::cout << x << " " << y << std::endl;
        x += x_inc;
        y += y_inc;
    }
}
