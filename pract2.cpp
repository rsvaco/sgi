#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#define PROYECTO "arturo sampedro pract2"

static GLuint triangulo;

void init() {

}

void display()
{
	glClearColor(1, 1, 1, 1);


	float PI = 3.1415926;
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		glColor3b(0.0, 0.0, 0.3);
		glVertex3f( cos(i * (2.0 / 3)*PI + PI / 2),  sin(i * (2.0 / 3)*PI + PI / 2), 0.0);
		glColor3b(0.0, 0.0, 0.3);
		glVertex3f( 0.7 *cos(i * (2.0 / 3)*PI + PI / 2),  0.7* sin(i * (2.0 / 3)*PI + PI / 2), 0.0);
	}

	glColor3b(0.0, 0.0, 0.3);
	glVertex3f(cos(0 * (2.0 / 3)*PI + PI / 2), sin(0 * (2.0 / 3)*PI + PI / 2), 0.0);
	glColor3b(0.0, 0.0, 0.3);
	glVertex3f(0.7 *cos(0 * (2.0 / 3)*PI + PI / 2), 0.7* sin(0 * (2.0 / 3)*PI + PI / 2), 0.0);

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		glColor3b(0.0, 0.0, 0.3);
		glVertex3f(cos(-i * (2.0 / 3)*PI - PI / 2), sin(-i * (2.0 / 3)*PI - PI / 2), 0.0);
		glColor3b(0.0, 0.0, 0.3);
		glVertex3f(0.7 *cos(-i * (2.0 / 3)*PI - PI / 2), 0.7* sin(-i * (2.0 / 3)*PI - PI / 2), 0.0);
	}

	glColor3b(0.0, 0.0, 0.3);
	glVertex3f(cos(0 * (2.0 / 3)*PI - PI / 2), sin(0 * (2.0 / 3)*PI - PI / 2), 0.0);
	glColor3b(0.0, 0.0, 0.3);
	glVertex3f(0.7 *cos(0 * (2.0 / 3)*PI - PI / 2), 0.7* sin(0 * (2.0 / 3)*PI - PI / 2), 0.0);

	glEnd();


	glFlush();
	
}

void reshape(GLint w, GLint h)
{
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Inicializacion de GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Alta de buffers a usar
	glutInitWindowSize(400, 400); // Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO); // Creacion de la ventana con su titulo
	std::cout << PROYECTO << " running" << std::endl; // Mensaje por consola
	init();
	glutDisplayFunc(display); // Alta de la funcion de atencion a display
	glutReshapeFunc(reshape); // Alta de la funcion de atencion a reshape
	
	glutMainLoop();
}