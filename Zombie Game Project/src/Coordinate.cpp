#include <iostream>
#include "Coordinate.h"
#include <string>
#include <sstream>
#include <cmath>
using namespace std;


Coordinate:: Coordinate(int x1, int y1) {
    x = x1;
    y = y1;
    infected = false;
}

int Coordinate:: getX (){
    return x;
}

int Coordinate:: getY (){
    return y;
}

void Coordinate:: setX (int x1) {
    x = x1;
}

void Coordinate:: setY (int y1) {
    y = y1;
}

void Coordinate:: setInfected () {
    infected = true;
}

bool Coordinate:: isInfected () {
    return infected;
}

int Coordinate:: getStartInfection () {
    return startInfection;
}

void Coordinate:: countStartInfection () {
    startInfection++;
}



bool Coordinate:: isDead () {
    return dead;
}

void Coordinate:: setDead (bool die) {
    dead = die;
}

bool Coordinate:: distance (Coordinate c2, int dist) {
                int xJ = c2.getX();
                int yJ = c2.getY();
                int xI = x;
                int yI = y;
                int x = xJ - xI;
                x = x*x;
                int y = yJ - yI;
                y = y*y;
                double soma = x + y;
                double result = sqrt (soma);
                if (result <= dist)
                    return true;
                return false;

}

int Coordinate:: getDistance (Coordinate c2) {
                int xJ = c2.getX();
                int yJ = c2.getY();
                int xI = x;
                int yI = y;
                int x = xJ - xI;
                x = x*x;
                int y = yJ - yI;
                y = y*y;
                double soma = x + y;
                double result = sqrt (soma);
                return result;

}

int Coordinate:: countDead () {
    return cDead;
}

void Coordinate:: incDead() {
    cDead++;
}

string Coordinate:: toString() {
    string result;
    ostringstream converter;
    converter << getX() << ", " << getY();
    return result = converter.str();
}

