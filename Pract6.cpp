#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <time.h>
#include <utilidades.h>

static float ojox = 0.0;
static float ojoy = 100.0;
static float ojoz = 0.0;
static float velocidad = 0.0;
static float angulo = 0.0;
static float ancho = 1.0;
static float tramos = 30;
static float seno = 0;
static float inc = 0.7; //incremento para la funcion que calcula los senos
static float valores[10] = { 1, 0.5, 0, -0.5, 0, 0.5, 1, 0.5, 0, 0.5 };

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

	gluLookAt(ojox, ojoy, ojoz, 0, 0, 0, 0, 0, 1);

	GLfloat v0 [3] = { 0,0,0 - ancho };
	GLfloat v1 [3] = { 0,0,0 + ancho };
	GLfloat v2 [3] = { 0,0,0 + ancho };
	GLfloat v3 [3] = { 0,0,0 - ancho };

	for (int i = 0; i < tramos; i++) {
		for (int j = 0; j < 3; j++) {
			v0[j] = v3[j];
			v1[j] = v2[j];
		}

		v2[0] = valores[i%10] + ancho;
		v2[2] = v2[2] - 0.5;
		v3[0] = valores[i % 10] - ancho;
		v3[2] = v2[2] - 0.5;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(1.0, 0.0, 0.0);
		quad(v0, v1, v2, v3);
	}

	GLfloat u0[3] = { -0.1, 0.0, -0.5 };
	GLfloat u1[3] = { 0.1, 0.0, -0.5 };
	GLfloat u2[3] = { 0.1, 0.0, 0.5 };
	GLfloat u3[3] = { -0.1, 0.0, 0.5 };

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 1.0, 0.0);
	quad(u3, u2, u1, u0);



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
	gluPerspective(10.0, 1.0, 0.1, 10000.0);
	
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
