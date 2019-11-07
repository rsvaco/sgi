#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <math.h>

#define ojox 7.5
#define ojoy 3.0
#define ojoz 2.0
#define numfiguras 6
#define PI 3.1415926

static GLuint estrella;
static GLuint figura;

void display()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ojox, ojoy, ojoz, 0, 0, 0, 0, 1, 0);

	for (int i = 0; i < numfiguras; i++) {
		glPushMatrix();
		glRotatef((180.0/numfiguras)*i, 0, 1, 0);
		glColor3f(0.0+i*(1.0/numfiguras), 0.0, 1.0-i*(1.0/numfiguras));
		glCallList(figura);
		glPopMatrix();
	}

	
	glColor3f(0.3, 0.3, 0.3);
	glutWireSphere(1.0, 20, 20); // Dibuja la esfera



	glFlush();
}
void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Usamos toda el area de dibujo
	glViewport(0, 0, w, h);

	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float) w / h;

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
	 modifica cuando variamos la altura del viewport */
	double cateto1 = sqrt(ojox*ojox + ojoy*ojoy + ojoz*ojoz);
	printf("%f", asin(1 / (cateto1))*(180 / PI));
	gluPerspective(2*asin(1 / (cateto1))*(180 / PI), razon, 1, 100);
}

void init() {
	std::cout << "inicio" << std::endl;
	glEnable(GL_DEPTH_TEST);
	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);


	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		float a = i * (2.0 / 3.0)*PI + PI / 2.0;
		glVertex3f(1.0 * cos(a), 1.0 * sin(a), 0.0);
		glVertex3f(0.7*cos(a), 0.7 * sin(a), 0.0);
	}
	glVertex3f(cos(PI / 2.0), sin(PI / 2.0), 0.0);
	glVertex3f(0.7 *cos(PI / 2.0), 0.7* sin(PI / 2.0), 0.0);



	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		float b = i * (2.0 / 3.0)*PI - PI / 2.0;
		glVertex3f(1.0 * cos(b), 1.0 * sin(b), 0.0);
		glVertex3f(0.7*cos(b), 0.7 * sin(b), 0.0);
	}
	glVertex3f(cos(-PI / 2.0), sin(-PI / 2.0), 0.0);
	glVertex3f(0.7 *cos(-PI / 2.0), 0.7* sin(-PI / 2.0), 0.0);



	glEnd();

	glEndList();


	figura = glGenLists(1);
	glNewList(figura, GL_COMPILE);

	glPushMatrix();
	glRotatef(15, 0, 0, 1);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glRotatef(-15, 0, 0, 1);
	glCallList(estrella);
	glPopMatrix();

	glEnd();

	glEndList();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("ARTURO SAMPEDRO REIG PRACT4");
	std::cout << "ARTURO SAMPEDRO REIG PRACT4" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(1.0, 1.0, 1.0, 1);
	init();
	display();

	glutMainLoop();
}