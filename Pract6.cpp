#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <time.h>
#include <utilidades.h>

static float ojox = 3.0;
static float ojoy = 6.0;
static float ojoz = 0.0;
static float velocidad = 0.0;
static float angulo = 0.0;

static GLuint estrella;
static GLuint figura;
static GLuint circulo;
static GLuint manilla1;
static GLuint manilla2;
static GLuint manilla3;

//static float PI = 3.141592;

static float angulo1;
static float angulo2;
static float angulo3;
static float anguloCont1;
static float anguloCont2;
static int lineCount = 20;
static float lineWidth = 1.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ojox, ojoy, ojoz, 0, 0, 0, 1, 0, 0);

	GLfloat v0[3] = { -0.1, 0.0, -0.5 };
	GLfloat v1[3] = { 0.1, 0.0, -0.5 };
	GLfloat v2[3] = { 0.1, 0.0, 0.5 };
	GLfloat v3[3] = { -0.1, 0.0, 0.5 };

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 0.0, 0.0);
	quad(v3, v2, v1, v0);



	glFlush();
}

void onSpecialKey(int tecla, int x, int y)
// Funcion de atencion al teclado
{
	switch (tecla) {
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
	glutPostRedisplay();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Usamos toda el area de dibujo
	glViewport(0, 0, w, h);

	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float)w / h;

	/* CAMARA ORTOGRAFICA
	 Ajustamos la vista a la dimenson más pequenya del viewport para
	 poder ver la totalidad de la ventana del mundo real (2x2)
	if(w<h)
		glOrtho(-1,1,-1/razon,1/razon, 0,10);
	else
		glOrtho(-1*razon,1*razon,-1,1, 0,10);  RADIO DE LA ESFERA DIVIDIDO ENTRE LA DISTANCIA  SENO


	/* CAMARA PERSPECTIVA
	 La razon de aspecto se pasa directamente a la camara perspectiva
	 Como damos fijo el angulovertical, el tamanyo del dibujo solo se
	 modifica cuando variamos la altura del viewport 
	double cateto1 = sqrt(ojox * ojox + ojoy * ojoy + ojoz * ojoz);
	printf("%f", asin(1 / (cateto1)) * (180 / PI));
	gluPerspective(2 * asin(1 / (cateto1)) * (180 / PI), razon, 1, 100);*/
	gluPerspective(10.0, 1.0, 0.1, 100.0);
	
}

void init() {

	glEnable(GL_DEPTH_TEST);


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
	anguloCont1 += (360.0 / 1.0) * tiempo_transcurrido / 1000.0;
	anguloCont2 += (360.0 / 60.0) * tiempo_transcurrido / 1000.0; //60s
	//angulo2 += (360.0 / (60.0*60.0)) * tiempo_transcurrido / 1000.0; //60min*60s
	//angulo1 += (360.0 / (60.0 * 60.0 * 12.0)) * tiempo_transcurrido / 1000.0; //12h*60min*60s

	antes = ahora;
	*/

	glutPostRedisplay();
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Carretera");
	std::cout << "ARTURO SAMPEDRO REIG PRACT6" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	glutSpecialFunc(onSpecialKey);
	glClearColor(1.0, 1.0, 1.0, 1);
	init();


	glutMainLoop();
}
