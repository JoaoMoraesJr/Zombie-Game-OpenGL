#include <iostream>
#include "Matrix.h"
#include <stdlib.h>
#include <fstream>	// para usar file streams (ifstream,ofstream)
#include <string>	// para usar string
#include <iomanip>	// para usar manipuladores (setw, right, ...)
#include <cstdlib>	// para usar srand(), rand() e exit()
#include <GL/glut.h>
#include <cmath>

using namespace std;

Matrix::Matrix(int persons, int frames) {

    Coordinate initiate (-1, -1);

  int i,j;

  matrix = (Coordinate**)malloc(persons * sizeof(Coordinate*));

  for (i = 0; i < persons; i++){
       matrix[i] = (Coordinate*) malloc(frames * sizeof(Coordinate));
       for (j = 0; j < frames; j++){
            matrix[i][j] = initiate;
       }
  }

}

Coordinate** Matrix:: getMatrix () {
    return matrix;
}

void Matrix:: Initialize () {
      Coordinate initiate (-1, -1);
      int i, j;
      for (i = 0; i < 50; i++){
       for (j = 0; j < 1000; j++){
            matrix[i][j] = initiate;
        }
    }
}

void Matrix:: mInsertCoord (Coordinate c, int person, int frame) {
    matrix [person] [frame] = c;
}

Coordinate Matrix:: getCoord (int person, int frame) {
    return matrix[person][frame];
}

void Matrix:: toString () {
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


void  Matrix :: readFile (string file) {
 Coordinate initiate (-1, -1);

    int posPerson = 0;
    int posFrame = 0;
    //LEITURA DE ARQUIVO

	// Cria input file stream (ifstream)
	ifstream arq;

	cout << "Abrindo arquivo texto..." << endl;

	// Abre arquivo
	const char * read = file.c_str();
	arq.open( read , ios::in );
	// Se houver erro, sai do programa
	if (!arq.is_open())
		cout << "Arquivo inv�lido" << endl;

    	// L� cabe�alho
	string cabecalho;
	getline(arq,cabecalho);

	// Exibe cabe�alho na tela
	cout << file << endl;
		// Agora, l� n registros num�ricos
	do
	{
	    posFrame = 0;
		string person, coords;
		arq >> person >> coords;
		if(!arq.fail()) {
			while (coords != "\n") {
                size_t init = coords.find("(");
                if (init != 0) {break;}
                size_t fim = coords.find (")");
                string coord1 = coords.substr(init, fim-init+1);

                //Adquire os dados das coordenadas
                size_t posX = coord1.find (",");
                string x = coord1.substr (init+1, posX - init-1);
                string coord2 = coord1.substr (posX+1);
                size_t posY = coord2.find (","); //coord1
                string y = coord2.substr (0, posY);
                string initFrame = coord2.substr (posY+1);
                size_t posFrame = initFrame.find (")");
                string frame = initFrame.substr (0, posFrame);
                int cordX = atoi(x.c_str());
                int cordY = atoi(y.c_str());
                int cFrame = atoi(frame.c_str());

                size_t cabecFim = cabecalho.find ("]");
                string cabecSubs = cabecalho.substr(1, cabecFim);
                int cabec = atoi(cabecSubs.c_str());
                Coordinate Coor((int)(cordX*100)/200, (int)(cordY*100)/200);


                mInsertCoord(Coor, posPerson, cFrame-1);

                coords = coords.substr(fim+1);
                posFrame++;
			}
		}

		posPerson++;
	} while(arq.good());
		if(arq.bad() || !arq.eof()) {
            cout << "Erro fatal!" << endl;
            exit(1);		// Aborta programa
	}
		cout << "Fechando o arquivo..." << endl;
	arq.close();

return;
}
