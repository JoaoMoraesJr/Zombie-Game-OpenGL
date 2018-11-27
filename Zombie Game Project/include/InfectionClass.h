#ifndef INFECTIONCLASS_H
#define INFECTIONCLASS_H

#include <string>
#include "Coordinate.h"
#include <unordered_map>
#include <GL/gl.h>
#include <GL/glut.h>

class InfectionClass
{
    Coordinate **matrix;
    Coordinate **infected;
    GLfloat x1 = 1.0f;
    GLfloat y1 = 1.0f;
    GLsizei rsize = 30;
    int frame = 0;
    int simulation = 0;
    int pontuacao = 0;
    int elimInf = 10;
    int elimPerson = -20;
    int infPerson = -5;
    public:

        InfectionClass();
        int getPontuacao ();
        void attMatrix(Coordinate**);
        void mInsertCoord(Coordinate, int, int);
        void Initialize();
        void toString();
        void readFile(std:: string);
        void setInfected(int, int);
        void attInfected(int);
        Coordinate getCoord(int, int);
        void desenhaTrajeto (int, int);
        void infectThroughTrace(int);
        void insertCoordinateIntoHashMap(Coordinate);
        bool findCoordinateFromMap(Coordinate);
        void clearMap();
        void setStartInfections(int);
        void setInfectedColor (Coordinate);
        bool drawInfectionSimulation(bool);
        void shootEvent(int, int);
        void setDead (int, int);
        void incrementDead(int, int);
};

#endif // MATRIX_H
