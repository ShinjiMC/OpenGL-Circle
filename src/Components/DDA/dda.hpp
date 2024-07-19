#ifndef DDA_HPP
#define DDA_HPP

#include <GL/glut.h>
#include <string>
#include <iostream>

class DDA
{
private:
    float red, green, blue;
    float x_start, y_start, x_end, y_end;
    std::string line_style;

public:
    DDA(float r, float g, float b, float x1, float y1, float x2, float y2, std::string style);
    void drawPoint(int x, int y, bool visible);
    void drawLine();    // Método para dibujar la línea
    void printPoints(); // Método para imprimir los puntos de la línea
};

#endif // DDA_HPP
