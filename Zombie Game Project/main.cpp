#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Coordinate.h"
#include "Matrix.h"
#include "TextFiles.h"
#include <fstream>	// para usar file streams (ifstream,ofstream)
#include <string>	// para usar string
#include <iomanip>	// para usar manipuladores (setw, right, ...)
#include <cstdlib>	// para usar srand(), rand() e exit()
#include <time.h>
#include <windows.h>
#include <GL/gl.h>
#include "InfectionClass.h"
#include <math.h>
#include <thread>


# define PI           3.14159265358979323846  /* pi */

GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY=6, obsZ, posX, posY=6, posZ, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 44; //44
int x_ini,y_ini,bot;
using namespace std;
Matrix M (50, 1000);
int frame = 0;
int simulation = 0;
string file;
TextFiles files;
bool automatic;
InfectionClass Inf;
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0
bool nextF;



double DegreesToRadians( double degrees )
{
    return degrees * PI / 180;
}

void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
    nextF = true;
}

void delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

void calculaposX ()
{
    float CO = sin(DegreesToRadians(-rotY)) * (3);
    posX = obsX + CO * -1;
}

void calculaposZ ()
{
    float CA = cos(DegreesToRadians(-rotY)) * (3);
    posZ = obsZ + CA * -1;
}

void calculaObsX(GLfloat rotaY)
{
    float CO = sin(DegreesToRadians(-1* (rotY + rotaY))) * (3);
    obsX = obsX + CO * -1;
}

void calculaObsZ (GLfloat rotaY)
{
    float CA = cos(DegreesToRadians(-1* (rotY + rotaY))) * (3);
    obsZ = obsZ + CA * -1;
}

void PosicionaObservador(void)
{

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	//glTranslatef(-obsX,-obsY,-obsZ);
	//glRotatef(rotX,1,0,0);
	//glRotatef(rotY,0,1,0);
    calculaposX();
    calculaposZ();

	//gluLookAt(0.0,5.0, 1.0, 0.0,5.0,0.0, 0.0,1.0,0.0);
	gluLookAt(obsX, obsY, obsZ, posX, posY, posZ, 0.0,1.0,0.0);
}
void EspecificaParametrosVisualizacao(void)
{

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();


	gluPerspective(angle,fAspect,0.01,500);

    PosicionaObservador();

}
void desenhaChao()
    {
        glColor3f(0,0.5,0);
        glLineWidth(3);
        glBegin(GL_LINES);
        for(float z=-1000; z<=1000; z+=10)
        {
            glVertex3f(-1000,-0.1f,z);
            glVertex3f( 1000,-0.1f,z);
        }
        for(float x=-1000; x<=1000; x+=10)
        {
            glVertex3f(x,-0.1f,-1000);
            glVertex3f(x,-0.1f,1000);
        }
        glEnd();
        glLineWidth(1);
    }

void Desenha(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	EspecificaParametrosVisualizacao();

    glEnable (GL_DEPTH_TEST);
    glLineWidth(1.5);
    glColor3f (0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(posX, 5.95, posZ);
        glVertex3f(posX, 6.05, posZ);
        glVertex3f(posX-0.05, 6, posZ-0.05);
        glVertex3f (posX+0.05, 6, posZ+0.05);
    glEnd();
    //glEnable (GL_DEPTH_TEST);
    //glColor3f(0.0f, 0.0f, 1.0f);

    glRasterPos3d(posX, posY+1, posZ);
    	//char* pontos = std:: to_string (Inf.getPontuacao());
    	//string str_pontos = SSTR(Inf.getPontuacao());
    	//cout<<str_pontos;
        char *pontos;

        char buffer[30];
        snprintf(buffer, 10, "%d", Inf.getPontuacao());

    	//strcpy(pontos, str_pontos);
    	char str_Pontuacao[30];
    	//str_Pontuacao= strcat("Pontuacao: ", buffer);
    	//strcpy(str_Pontuacao,strcat("Pontuacao: ", buffer) );

    	//cout<<strcat("Pontuacao: ", buffer);

    	snprintf(str_Pontuacao,30,"%s %s","Pontuacao: ",buffer);


	for(int l=0; l<strlen(str_Pontuacao); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str_Pontuacao[l]);

    //desenhaProjetil();
	desenhaChao();

	///////////////////////////////////////////
    //cout<< nextF;
    bool finished = false;
    finished = Inf.drawInfectionSimulation(nextF);
    if (finished == true) {
            if (automatic == true){
                bool stop = files.startNew(M);
                if (!stop) {
                    string name;
                    cout << "Digite seu nome: ";
                    cin >> name;
                    files.saveScore(Inf.getPontuacao(), name);
                    files.printRank();
                    cout << "Digite qualquer tecla para sair: ";
                    string tecla;
                    cin >> tecla;
                    exit(0);
                }
                Inf.clearMap();
                Inf.attMatrix(M.getMatrix());
                Inf.setInfected(0, 0);
                Inf.setInfected(5, 0);
                frame = 0;
            }
    }
     // Executa os comandos OpenGL
     glutSwapBuffers();
     simulation++;

	//////////////////////////////////////////



	//glFlush();
}

void desenhaProjetil(int d) {
        int i = 5;
        glColor3f (0.0f, 0.0f, 0.0f);
        glPushMatrix();
        float CA = cos(DegreesToRadians(-rotY)) * (d*5);
        float CO = sin(DegreesToRadians(-rotY)) * (d*5);
        GLfloat posX = obsX + CO * -1;
        GLfloat posZ = obsZ + CA * -1;
        glTranslatef(posX, 4.3, posZ);
        //cout<< "Ini: " << obsX << " " << obsZ << " " << posX << " " << posZ << " ";
        glutSolidRhombicDodecahedron();
        glPopMatrix();
        glutSwapBuffers();
        std::this_thread::sleep_for (std::chrono::milliseconds(2));
        Desenha();
        if (d < 80) {
            Inf.shootEvent(posX, posZ);
            d++;
            desenhaProjetil(d);
        }
        else {
            cout << "\t Sua pontuacao: " << Inf.getPontuacao() << endl;
            return;
        }
    }







void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


void Teclado (unsigned char key, int x, int y)
{
    nextF = false;
	if (key == 27)
		exit(0);

    if (key == 119) {    //W 87
        //obsZ -= 3;
        obsX = posX;
        obsZ = posZ;
        //cout << "Frente";
    }

    if (key == 115) {  //S
        //obsZ += 3;
        calculaObsX(180);
        calculaObsZ(180);
        //cout << "Tras";
    }

    if (key == 97) {    //A
        //obsX -= 3;
        calculaObsX(270);
        calculaObsZ(270);
        //cout<< "Esquerda";
    }

    if (key == 100) {    //D
        //obsX += 3;
        calculaObsX(90);
        calculaObsZ(90);
        //cout<< "Direita";
    }
    PosicionaObservador();
	glutPostRedisplay();


}


void Inicializa (void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLineWidth(2.0);
}

void GerenciaMouse(int button, int state, int x, int y)
{
    nextF = false;
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
		if (button == GLUT_LEFT_BUTTON)desenhaProjetil(0);
	}
	else bot = -1;
}
void GerenciaMovim(int x, int y)
{

	if(bot==GLUT_RIGHT_BUTTON)
	{

		int deltax = x_ini - x;
		int deltay = y_ini - y;

		rotY = rotY_ini - deltax/SENS_ROT;
		//cout << rotY << " ";
		//rotX = rotX_ini - deltay/SENS_ROT;
	}

	else if(bot==GLUT_LEFT_BUTTON)
	{

		//int deltaz = y_ini - y;

		//obsZ = obsZ_ini + deltaz/SENS_OBS;
        //std::thread shoot (desenhaProjetil, 0);
        //desenhaProjetil(0);
        //shoot.join();
	}

	else if(bot==GLUT_MIDDLE_BUTTON)
	{

		int deltax = x_ini - x;
		int deltay = y_ini - y;

		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	nextF = false;
	PosicionaObservador();
	glutPostRedisplay();
}


int main(void)
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

    automatic = true;
    files.startNew(M);
    Inf.attMatrix(M.getMatrix());
    Inf.setInfected(0, 0);
    Inf.setInfected(5, 0);

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


	glutInitWindowPosition(5,5);


	glutInitWindowSize(450,450);


	glutCreateWindow("Camera, Projecao");


	glutDisplayFunc(Desenha);


	glutReshapeFunc(AlteraTamanhoJanela);

	glutKeyboardFunc (Teclado);

	glutMotionFunc(GerenciaMovim);

    glutMouseFunc(GerenciaMouse);



	glutTimerFunc(33, Timer, 1);



	Inicializa();

	glutMainLoop();

	return 0;
}
