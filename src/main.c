#include <GL/freeglut.h> // dodanie biblioteki GLUT
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

enum Shapes {
	SPHERE,
	TEAPOT,
	CONE,
};

int width;
int height;


enum Shapes shape; // co ma narysować


// funkcja obsługi klawiatury
void klawiatura(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		shape = SPHERE;
		break;
	case '2':
		shape = CONE;
		break;
	case '3':
		shape = TEAPOT;
		break;


	case 27:
	case 'q':
		exit(0);
		break;
	}
}

void reshape(int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
	//gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
	glOrtho(0.0f, (GLdouble)w, 0.0f, (GLdouble)h, -300.0f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawRect(int x, int y, int w, int h) {
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
}


GLuint quadList;


// funkcja wyświetlająca obraz
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
  

  // 'F'
  /*
	glBegin(GL_QUADS);
	drawRect(10, 120, 30, 200);
	drawRect(10, 290, 100, 30);
	drawRect(10, 220, 100, 30);
	glEnd();
  */

  int time = glutGet(GLUT_ELAPSED_TIME);
	glPushMatrix();

	glTranslatef(width / 2.0f - 100.0f, height / 2.0f - 100.0f, 0.0f);
  glRotatef(time / 10.0f, 0.5f, 0.5f, 0.5f);

  // draw here
  //
  

  glColor3f(1.0f, 0.0f, 0.0f);
  glCallList(quadList);
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glCallList(quadList);
  glTranslatef(00.0f, 0.0f, -200.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glCallList(quadList);
  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  glTranslatef(00.0f, -200.0f, +200.0f);
  glColor3f(0.0f, 1.0f, 1.0f);
  glCallList(quadList);

  glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glCallList(quadList);

  glTranslatef(00.0f, 000.0f, 200.0f);
  glColor3f(1.0f, 0.0f, 1.0f);
  glCallList(quadList);
  glEnd();

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ustawienie podwójnego
	glutInitWindowSize(640, 480); // rozmiar okna
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display); // ustawienie funkcji odpowiedzialnej za
	glutReshapeFunc(reshape); // ustawienie funkcji wywoływanej przy
	glutKeyboardFunc(klawiatura); // ustawienie funkcji obsługi klawiatury
  

  quadList = glGenLists(1);  
  glNewList(quadList, GL_COMPILE);
  glBegin(GL_QUADS);
  drawRect(0,0,200,200);
  glEnd();
  glEndList();

	glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
	glutMainLoop(); // wejście do głównej pętli programu
	return 0;
}
