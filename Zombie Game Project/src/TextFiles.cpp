#include "TextFiles.h"
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
TextFiles::TextFiles()
{
    file = " ";
    simulation = 1;
}


void TextFiles:: delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

bool TextFiles:: startNew (Matrix M)
{
    switch (simulation) {
    case 0:
        file = "Alemanha1.txt";
        simulation++;
        break;

    case 1:
        file = "Alemanha2.txt";
        simulation++;
        break;

    case 2:
        file = "Austria1.txt";
        simulation++;
        break;

    case 3:
        file = "Austria2.txt";
        simulation++;
        break;

    case 4:
        file = "Austria3.txt";
        simulation++;
        break;

    case 5:
        file = "Brasil1.txt";
        simulation++;
        break;

    case 6:
        file = "Brasil2.txt";
        simulation++;
        break;

    case 7:
        file = "Brasil3.txt";
        simulation++;
        break;

    case 8:
        file = "Brasil4.txt";
        simulation++;
        break;

    case 9:
        file = "Brasil5.txt";
        simulation++;
        break;

    case 10:
        file = "Brasil6.txt";
        simulation++;
        break;

    case 11:
        file = "Brasil7.txt";
        simulation++;
        break;

    case 12:
        file = "Brasil8.txt";
        simulation++;
        break;

    case 13:
        file = "China1.txt";
        simulation++;
        break;

    case 14:
        file = "China2.txt";
        simulation++;
        break;

    case 15:
        file = "China3.txt";
        simulation++;
        break;

    case 16:
        file = "Desconhecido1.txt";
        simulation++;
        break;

    case 17:
        file = "Desconhecido2.txt";
        simulation++;
        break;

    case 18:
        file = "Desconhecido3.txt";
        simulation++;
        break;

    case 19:
        file = "Dubai1.txt";
        simulation++;
        break;

    case 20:
        file = "Dubai2.txt";
        simulation++;
        break;

    case 21:
        file = "Espanha1.txt";
        simulation++;
        break;

    case 22:
        file = "Franca1.txt";
        simulation++;
        break;

    case 23:
        file = "Franca2.txt";
        simulation++;
        break;

    case 24:
        file = "Inglaterra1.txt";
        simulation = 0;
        break;


    case 25:
        file = "Japao1.txt";
        simulation++;
        break;

    case 26:
        file = "Japao2.txt";
        simulation++;
        break;

    case 27:
        file = "Portugal1.txt";
        simulation++;
        break;

    case 28:
        file = "Turquia1.txt";
        simulation=1;
        return false;
        break;

    }
    delay (1.0);
    M.Initialize();
    M.readFile(file);
    return true;

}

vector<int> TextFiles:: openScore (){
    std::vector<int> arrlist;
    ifstream arq;
    arq.open( "Ranking.txt" , ios::in );
    string cabecalho;
	getline(arq,cabecalho);
	do
	{
	    string name;
		int pontos;
		arq >> name >> pontos;
		if(!arq.fail()) {
			arrlist.push_back(pontos);
		}
	} while(arq.good());
	return arrlist;
}

vector<string> TextFiles:: openScoreNames(){
    std::vector<string> arrlist;
    ifstream arq;
    arq.open( "Ranking.txt" , ios::in );
    string cabecalho;
	getline(arq,cabecalho);
	do
	{
	    string name;
		int pontos;
		arq >> name >> pontos;
		if(!arq.fail()) {
			arrlist.push_back(name);
		}
	} while(arq.good());
	return arrlist;
}

void TextFiles:: printRank () {
    std::vector<string> arrNames;
    std::vector<int> arrPoints;
    ifstream arq;
    arq.open( "Ranking.txt" , ios::in );
    string cabecalho;
	getline(arq,cabecalho);
	do
	{
	    string name;
		int pontos;
		arq >> name >> pontos;
		if(!arq.fail()) {
            arrPoints.push_back(pontos);
			arrNames.push_back(name);
		}
	} while(arq.good());
	for (int i = 0; i<arrNames.size(); i++) {
        cout << i+1 << "- " << arrNames[arrNames.size() - i -1] << " " << arrPoints[arrPoints.size() - i -1] << endl;
	}
}

void TextFiles:: saveScore (int pont, string name){
    vector<string> arrNames = openScoreNames();
    vector<int> arrlist = openScore();
    vector<int> oldArrlist = arrlist;
    arrlist.push_back(pont);
    std::sort(arrlist.begin(), arrlist.end());
    ofstream arqsaida;
    arqsaida.open( "Ranking.txt" , ios::out );
    arqsaida << "Ranking" << endl;
    int x = 0;
    int ranking = 0;
    for (int i = 0; i < arrlist.size(); i++){
        if (arrlist[i] == oldArrlist[x]) {
            arqsaida << arrNames [x] << " " << arrlist[i] << endl;
            x++;
        }else{
            arqsaida << name << " " << arrlist[i] << endl;
            ranking = i;
        }
    }
    arqsaida.close();
    cout << "Voce ficou no rank " << arrlist.size() - ranking << endl;
}
