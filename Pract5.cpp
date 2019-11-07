#include <iostream>
#include <cmath>
#include <GL\freeglut.h>
#include <time.h>

static float ojox = 1.0;
static float ojoy = 2.0;
static float ojoz = 3.0;

static GLuint estrella;
static GLuint figura;
static GLuint circulo;
static GLuint manilla1;
static GLuint manilla2;
static GLuint manilla3;

static float PI = 3.141592;

static float angulo1;
static float angulo2;
static float angulo3;
static float anguloCont;
static int lineCount = 20;
static float lineWidth = 1.0;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(ojox, ojoy, ojoz, 0, 0, 0, 0, 1, 0);

	GLUquadricObj* quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.1);
	glColor3f(0.3, 0.3, 0.3);
	gluCylinder(quadratic, 1.0, 1.0, 0.1, 40, 40);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glRotatef(-angulo1, 0.0, 0.0, 1);
	glCallList(manilla1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.0, 0.0);
	glRotatef(-angulo2, 0.0, 0.0, 1);
	glCallList(manilla2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1, 0.0);
	glRotatef(-angulo3, 0.0, 0.0, 1);
	glCallList(manilla3);
	glPopMatrix();

	//crea los 12 circulos que marcaran las horas
	for (int i = 0; i < 12; i++) {
		
		glPushMatrix();

		if (i % 3 == 0) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		
		glRotatef((360 / 12) * i, 0.0, 0.0, 1.0);
		glRotatef(anguloCont, 0.0, 1.0, 0.0);
		glTranslatef(0.0, +0.9, 0.0);
		glScalef(0.1, 0.1, 0.1);
		glCallList(circulo);
		
		glPopMatrix();
	}
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
	 modifica cuando variamos la altura del viewport */
	double cateto1 = sqrt(ojox * ojox + ojoy * ojoy + ojoz * ojoz);
	printf("%f", asin(1 / (cateto1)) * (180 / PI));
	gluPerspective(2 * asin(1 / (cateto1)) * (180 / PI), razon, 1, 100);
}

void init() {
	
	glEnable(GL_DEPTH_TEST);

	//circulo
	circulo = glGenLists(1);
	glNewList(circulo, GL_COMPILE);
	float x, y;
	float radius = 0.5f;
	glPushMatrix();
	glLineWidth(lineWidth);
	glBegin(GL_LINES);


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
	glPopMatrix();
	glEndList();

	//manilla1
	manilla1 = glGenLists(1);
	glNewList(manilla1, GL_COMPILE);

	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutWireSphere(0.1f, lineCount, lineCount);
	glutWireCone(0.1, 0.7, lineCount, lineCount);

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

	time_t currentTime;
	struct tm localTime;
	time(&currentTime);
	localtime_s(&localTime, &currentTime);

	int hour = localTime.tm_hour;
	int min = localTime.tm_min;
	int sec = localTime.tm_sec;

	


	angulo1 = 360.0 * (hour / 12.0);
	angulo2 = 360.0 * (min / 60.0);
	angulo3 = 360.0 * (sec / 60.0);

}

void onIdle()
// Funcion de atencion al evento idle
{
	
	//Calculamos el tiempo transcurrido desde la última vez
	static int antes = 0;
	int ahora, tiempo_transcurrido;
	ahora = glutGet(GLUT_ELAPSED_TIME); //Tiempo transcurrido desde el inicio
	tiempo_transcurrido = ahora - antes; //Tiempo transcurrido desde antes en msg.
	// angulo = angulo anterior + velocidad x tiempo
	angulo3 += (360.0/60) * tiempo_transcurrido / 1000.0; //60s
	angulo2 += (360.0 / (60.0*60.0)) * tiempo_transcurrido / 1000.0; //60min*60s
	angulo1 += (360.0 / (60.0 * 60.0 * 12.0)) * tiempo_transcurrido / 1000.0; //12h*60min*60s

	anguloCont += 0.1;
	antes = ahora;
	glutPostRedisplay();	
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("ARTURO SAMPEDRO REIG PRACT5");
	std::cout << "ARTURO SAMPEDRO REIG PRACT5" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	glClearColor(1.0, 1.0, 1.0, 1);
	init();


	glutMainLoop();
}