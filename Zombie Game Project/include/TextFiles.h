

#ifndef TEXTFILES_H
#define TEXTFILES_H
#include <string>
#include "Matrix.h"
#include <vector>
class TextFiles
{
    std::string file;
    int simulation;

    public:
        TextFiles();
        void delay (float);
        bool startNew(Matrix M);
        vector<int> openScore();
        vector<string> openScoreNames();
        void saveScore(int, string);
        void printRank();
};

#endif // TEXTFILES_H



