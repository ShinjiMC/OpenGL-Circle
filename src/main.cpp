#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Components/DDA/dda.hpp"
#include "Components/Circle/circle.hpp"

// Función para mostrar los cuadrantes
void showQuadrants()
{
    DDA lineX(1.0, 1.0, 1.0, -1000.0, 0.0, 1000.0, 0.0, "solid");
    DDA lineY(1.0, 1.0, 1.0, 0.0, -1000.0, 0.0, 1000.0, "solid");

    lineX.drawLine();
    lineY.drawLine();
}

// Inicialización de OpenGL
void initGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Fondo negro
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400.0, 400.0, -400.0, 400.0); // Ajustar el rango a la ventana
}

// Función para manejar el redimensionamiento de la ventana
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

// Variables globales para el círculo
Circle *circle = nullptr;
std::vector<float> percentages;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    showQuadrants();

    if (circle)
    {
        circle->drawCircle();
        if (!percentages.empty())
        {
            circle->drawPieChart(percentages);
        }
    }

    glFlush();
}

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        std::cerr << "Usage:\n";
        std::cerr << "./exe drawCircle <r g b pointX pointY radius>\n";
        std::cerr << "./exe drawPie <r g b pointX pointY radius>\n";
        return 1;
    }

    std::string mode = argv[1];
    float r = std::stof(argv[2]);
    float g = std::stof(argv[3]);
    float b = std::stof(argv[4]);
    int x = std::stoi(argv[5]);
    int y = std::stoi(argv[6]);
    int radius = std::stoi(argv[7]);

    if (mode == "drawCircle")
    {
        circle = new Circle(x, y, radius, r, g, b);
    }
    else if (mode == "drawPie")
    {
        circle = new Circle(x, y, radius, r, g, b);

        int numSegments;
        std::cout << "Enter the number of segments: ";
        std::cin >> numSegments;

        percentages.resize(numSegments);
        for (int i = 0; i < numSegments; ++i)
        {
            std::cout << "Enter percentage for segment " << (i + 1) << ": ";
            std::cin >> percentages[i];
        }
    }
    else
    {
        std::cerr << "Invalid mode. Use 'drawCircle' or 'drawPie'.\n";
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Draw Circle with OpenGL");
    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    delete circle;
    return 0;
}
