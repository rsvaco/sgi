#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

static GLuint estrella;
static GLuint figura;
static GLuint circulo;
static GLuint manilla1;
static GLuint manilla2;
static GLuint manilla3;
static float angulo1;
static float angulo2;
static float angulo3;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//glPushMatrix();
	glPushMatrix();
	glRotatef(-angulo1, 0.0, 0.0, 1);
	glCallList(manilla1);
	glPopMatrix();


	glColor3f(1, 0.0, 0.0);
	glCallList(manilla2);


	glColor3f(0.0, 1, 0.0);
	glCallList(manilla3);
	//glPopMatrix();

	//crea los 12 circulos que marcaran las horas
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glRotatef((360/12)*i, 0.0, 0.0, 1.0);
		glTranslatef(0.0, +0.9, 0.0);
		glScalef(0.1, 0.1, 0.1);
		glCallList(circulo);
		glPopMatrix();
	}

	glFlush();
}
void reshape(GLint w, GLint h)
{
}

void init() {

	float PI = 3.141592;
	glEnable(GL_DEPTH_TEST);

	//circulo
	circulo = glGenLists(1);
	glNewList(circulo, GL_COMPILE);
	float x, y;
	float radius = 0.5f;
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	x = (float)radius * cos(359 * PI / 180.0f);
	y = (float)radius * sin(359 * PI / 180.0f);
	for (int j = 0; j < 360; j++)
	{
		glVertex2f(x, y);
		x = (float)radius * cos(j * PI / 180.0f);
		y = (float)radius * sin(j * PI / 180.0f);
		glVertex2f(x, y);
	}

	glEnd();

	glEndList();

	//manilla1
	manilla1 = glGenLists(1);
	glNewList(manilla1, GL_COMPILE);

	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutWireSphere(0.1f, 30, 30);
	glutWireCone(0.1, 0.7, 30, 30);
	
	glPopMatrix();

	
	glEndList();

	//manilla2
	manilla2 = glGenLists(1);
	glNewList(manilla2, GL_COMPILE);
	
	
	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	glCallList(manilla1);
	glPopMatrix();
	
	
	glEndList();

	//manilla3
	manilla3 = glGenLists(1);
	glNewList(manilla3, GL_COMPILE);


	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	glCallList(manilla2);
	glPopMatrix();


	glEndList();
	

}

void onIdle()
// Funcion de atencion al evento idle
{
	/*
	//Calculamos el tiempo transcurrido desde la última vez
	static int antes = 0;
	int ahora, tiempo_transcurrido;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Tiempo transcurrido desde el inicio
	tiempo_transcurrido = ahora - antes; //Tiempo transcurrido desde antes en msg.
	// angulo = angulo anterior + velocidad x tiempo
	angulo1 += 1.0 * tiempo_transcurrido / 60.0;
	antes = ahora;
	glutPostRedisplay();	*/
}

void onTimer(int valor)
// Funcion de atencion al evento idle
{
	angulo1 += 1;
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("ARTURO SAMPEDRO REIG PRACT1");
	std::cout << "ARTURO SAMPEDRO REIG PRACT1" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	//glutTimerFunc(10, onTimer, 1);
	glClearColor(1.0, 1.0, 1.0, 1);
	init();


	glutMainLoop();
}