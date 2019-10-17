#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

static GLuint estrella;
static GLuint figura;

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(-0.5, +0.5, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(figura);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(-30, 0, 0, 1);
	glCallList(figura);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(+0.5, +0.5, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(-30, 0, 0, 1);
	glCallList(figura);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(+0.5, -0.5, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(0, 0, 0, 1);
	glCallList(figura);
	glPopMatrix();

	glFlush();
}
void reshape(GLint w, GLint h)
{
}

void init() {
	std::cout << "w" << std::endl;
	float PI = 3.1415926;
	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);


	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		float a = i * (2.0 / 3.0)*PI + PI / 2.0;
		printf("%d\t%d", 1 * cos(a), 1 * sin(a));
		glVertex3f(1 * cos(a), 1 * sin(a), 0.0);
		glVertex3f(0.7*cos(a), 0.7 * sin(a), 0.0);
	}
	glVertex3f(cos(PI / 2), sin(PI / 2), 0.0);
	glVertex3f(0.7 *cos(PI / 2), 0.7* sin(PI / 2), 0.0);



	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 3; i++) {
		float b = i * (2.0 / 3.0)*PI - PI / 2.0;
		printf("%d\t%d", 1 * cos(b), 1 * sin(b));
		glVertex3f(1 * cos(b), 1 * sin(b), 0.0);
		glVertex3f(0.7*cos(b), 0.7 * sin(b), 0.0);
	}
	glVertex3f(cos(-PI / 2), sin(-PI / 2), 0.0);
	glVertex3f(0.7 *cos(-PI / 2), 0.7* sin(-PI / 2), 0.0);



	glEnd();

	glEndList();


	figura = glGenLists(1);
	glNewList(figura, GL_COMPILE);

	glPushMatrix();
	glRotatef(15, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.8);
	glCallList(estrella);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glRotatef(-15, 0, 0, 1);
	glColor3f(0.0, 0.0, 0.8);
	glCallList(estrella);
	glPopMatrix();

	glEnd();

	glEndList();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 600);
	glutCreateWindow("ARTURO SAMPEDRO REIG PRACT1");
	std::cout << "ARTURO SAMPEDRO REIG PRACT1" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glClearColor(1.0, 1.0, 1.0, 1);
	init();
	display();

	glutMainLoop();
}