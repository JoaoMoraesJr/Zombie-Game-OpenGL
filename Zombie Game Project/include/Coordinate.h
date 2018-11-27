#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

using namespace std;

class Coordinate
{
    int x, y;
    bool infected;
    int startInfection;
    bool dead = false;
    int cDead = 0;

    public:
        Coordinate(int, int);
        int getX ();
        int getY ();
        void setX (int);
        void setY (int);
        string toString();

        void setInfected ();
        bool isInfected ();
        int getStartInfection();
        void countStartInfection();

        bool isDead();
        void setDead(bool);
        int countDead();
        void incDead();

        bool distance (Coordinate, int);
        int getDistance (Coordinate);

};

#endif // COORDINATE_H
