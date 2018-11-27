#include <iostream>
#include "Matrix.h"
#include "InfectionClass.h"
#include "Coordinate.h"
#include <stdlib.h>
#include <fstream>	// para usar file streams (ifstream,ofstream)
#include <string>	// para usar string
#include <iomanip>	// para usar manipuladores (setw, right, ...)
#include <cstdlib>	// para usar srand(), rand() e exit()
#include <GL/glut.h>
#include <cmath>

using namespace std;

std::unordered_map<std::string, std::string> infectedCoordinateMap;

InfectionClass::InfectionClass() {
}

void InfectionClass:: Initialize () {
      Coordinate initiate (-1, -1);
      int i, j;
      for (i = 0; i < 50; i++){
       for (j = 0; j < 1000; j++){
            matrix[i][j] = initiate;
        }
    }
}

void InfectionClass:: attMatrix (Coordinate **mat) {
    matrix = mat;
}

void InfectionClass:: mInsertCoord (Coordinate c, int person, int frame) {
    matrix [person] [frame] = c;
}

Coordinate InfectionClass:: getCoord (int person, int frame) {
    return matrix[person][frame];
}

int InfectionClass:: getPontuacao () {
    return pontuacao;
}

void InfectionClass:: toString () {
    int i;
    int j;
    for (i = 0; i < 20; i++) {
    cout << "\n\n\n Pessoa " << i << ":" << endl;
        for (j = 0; j < 1000; j++) {
        Coordinate coord = matrix [i] [j];
        cout << "(" << coord.getX();
        cout<< ", " << coord.getY() << ") ";
    }
  }
}

void InfectionClass:: setInfected (int person, int frame) {
    pontuacao+= infPerson;
    cout << " Uma pessoa foi infectada! " << infPerson << " pontos" << endl;
    int k;
    for (k = frame; k < 1000; k++)
        matrix[person][k].setInfected();
}

void InfectionClass:: setStartInfections(int frame) {
    int i, k;
    for (i = 0; i < 50; i++) {
       if (matrix [i][frame].isInfected()) {
        for (k = frame; k < 1000; k++) {
            if (matrix [i][k].isInfected())
                matrix[i][k].countStartInfection();
    }
    }
}
}

void InfectionClass:: incrementDead(int person, int frame) {
        for (int k = frame; k < 1000; k++) {
                matrix[person][k].incDead();
        }
}


void InfectionClass:: setDead(int person, int frame) {
    int k;
    if (matrix[person][frame].isInfected() == true) {
        pontuacao += elimInf;
        cout << " Voce eliminou um infectado! +" << elimInf << " pontos" << endl;
    }
    else {
        pontuacao += elimPerson;
        cout << " Voce eliminou uma pessoa! "<< elimPerson << "  pontos" << endl;
    }
    for (k = frame; k < 1000; k++)
        matrix[person][k].setDead(true);
}

void InfectionClass:: shootEvent(int xS, int yS) {
    bool hit = false;
    for (int i = 0; i < 50; i++) {
            Coordinate c = matrix [i] [frame];
            if (matrix[i][frame].getX() != -1 && c.isDead() == false) {
                int xI = matrix[i][frame].getX();
                int yI = matrix[i][frame].getY();
                int x = xS - xI;
                x = x*x;
                int y = yS - yI;
                y = y*y;
                double soma = x + y;
                double distance = sqrt (soma);
                if (distance <= 4){
                hit = true;
                setDead(i, frame);
                }
            }
    }
}

void InfectionClass:: attInfected(int frame){
    for (int i=0; i<50; i++) {
        for (int j = 0; j < 50; j++) {
            Coordinate c = matrix [i] [frame];
            if (matrix[i][frame].isInfected() == true && matrix[i][frame].isDead() == false && matrix[i][frame].getStartInfection()>8 && matrix[i][frame].getX() != -1 && matrix[j][frame].isInfected() == false) {

                int xJ = matrix[j][frame].getX();
                int yJ = matrix[j][frame].getY();
                int xI = matrix[i][frame].getX();
                int yI = matrix[i][frame].getY();
                int x = xJ - xI;
                x = x*x;
                int y = yJ - yI;
                y = y*y;
                double soma = x + y;
                double distance = sqrt (soma);
                if (distance <= 80)
                setInfected(j, frame);

            }
        }
    }
}


void InfectionClass:: infectThroughTrace(int frame) {

    for (int i = 0; i < 50; i++) {
        if (findCoordinateFromMap(matrix[i][frame])) setInfected(i, frame);
    }

}

void InfectionClass:: insertCoordinateIntoHashMap(Coordinate c) {
    if (c.isInfected()) infectedCoordinateMap.emplace(c.toString(), c.toString());
}

bool InfectionClass:: findCoordinateFromMap(Coordinate c) {
    if (infectedCoordinateMap.count(c.toString()) == 0) return false;
    return true;
}

void InfectionClass:: clearMap () {
    infectedCoordinateMap.clear();
}

void InfectionClass:: desenhaTrajeto(int person, int frame) {
    glLineWidth(3.0);
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i<frame; i++) {
        Coordinate Coord = matrix[person] [i];
        if (Coord.isInfected() && Coord.getX() != -1)
        glVertex3f(Coord.getX(), Coord.getY(), 0.0);
    }
    glEnd();
}

void InfectionClass:: setInfectedColor (Coordinate c) {
    if (c.isInfected() && c.getStartInfection()>8) {
        glColor3f (0.0, 0.9f, 0.0f);
        return;
    }
    switch (c.getStartInfection()) {
    case 0:
        glColor3f (0.0, 0.0f, 0.0f);
        break;
    case 1:
        glColor3f (0.0, 0.1f, 0.0f);
        break;
    case 2:
        glColor3f (0.0, 0.2f, 0.0f);
        break;
    case 3:
        glColor3f (0.0, 0.3f, 0.0f);
        break;
    case 4:
        glColor3f (0.0, 0.4f, 0.0f);
        break;
    case 5:
        glColor3f (0.0, 0.5f, 0.0f);
        break;
    case 6:
        glColor3f (0.0, 0.6f, 0.0f);
        break;
    case 7:
        glColor3f (0.0, 0.7f, 0.0f);
        break;
    case 8:
        glColor3f (0.0, 0.8f, 0.0f);
        break;
    }
}

bool InfectionClass:: drawInfectionSimulation(bool nextF)
{
    bool finished = true;
	// Limpa a janela de visualiza��o com a cor branca
	//glClearColor(1,1,1,0);
	//glClear(GL_COLOR_BUFFER_BIT);

     //glMatrixMode(GL_MODELVIEW);
     //glLoadIdentity();

     // Limpa a janela de visualiza��o com a cor de fundo especificada
     //glClear(GL_COLOR_BUFFER_BIT);

     // Especifica que a cor corrente � vermelha
     //         R     G     B
     //glColor3f(1.0f, 0.0f, 0.0f);

     // Desenha um quadrado preenchido com a cor corrente
    setStartInfections(frame);
    for (int i = 0; i < 50; i++) {
        //glLoadIdentity();
        Coordinate c = getCoord(i, frame);
        //if (c.isInfected() && c.getX() != -1) insertCoordinateIntoHashMap(c);
        int xInc = c.getX();
        int yInc = c.getY();
        //cout << frame << endl;
        if (xInc != -1 && yInc != -1 && frame != 1000) {
            finished = false;
            if (c.isInfected()) setInfectedColor(c);
                //glColor3f (0.0, 0.5f, 0.0f);
            if (!c.isInfected()) glColor3f(0.0f, 0.0f, 0.7f);
            if (c.isDead()) {
                    incrementDead (i, frame);
                    glColor3f (1.0f, 0.0f, 0.0f);
            }
            if (c.countDead () < 100) {
                glPushMatrix();
                glTranslatef(xInc, 6, yInc);
                glRotatef(90, 1, 0, 0);
                glutSolidCylinder(2, 6, 10, 1);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(xInc, 7, yInc);
                glutSolidSphere(3, 10, 10);
                glPopMatrix();
            }
        }
        //if (c.isInfected()) desenhaTrajeto(i, frame);
        attInfected(frame);
        //infectThroughTrace(frame);
    }
    if (nextF) frame++;
    if (finished == true) frame = 0;
    simulation++;
    //glLoadIdentity();
    return finished;
}
