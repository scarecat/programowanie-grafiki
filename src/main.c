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
  
	//glOrtho(0.0f, (GLdouble)w, 0.0f, (GLdouble)h, -300.0f, 300.0f);
	glOrtho(-w/2.0, w/2.0, -h/2.0, h/2.0, -300.0f, 300.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawRect(int x, int y, int w, int h) {
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);
	glVertex2f(x, y);
	glVertex2f(x, y + h);
}


GLuint drawList;


// funkcja wyświetlająca obraz
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

  int time = glutGet(GLUT_ELAPSED_TIME);
  glNewList(drawList, GL_COMPILE_AND_EXECUTE);
	glPushMatrix();
  glTranslatef(0,100,0);
  glTranslatef(+100,0,0);
	glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glRotatef(time/10.0f, 0.5f, 1.0f, 0.5f);
  glutSolidTeapot(50.0f);
  glPopMatrix();

  glColor3f(0.0, 0.0f, 1.0f);
  glTranslatef(-200,0,0);
  glutSolidCube(50.0f);
	glPopMatrix();

  glEndList();

  glPushMatrix();
  glScalef(1.0f, -1.0f, 1.0f);
  
  glCallList(drawList);
  glPopMatrix();

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
  glBegin(GL_QUADS);
  glVertex2f(-width/2.0f, 0.0f);
  glVertex2f(+width/2.0f, 0.0f);
  glVertex2f(+width/2.0f, -height/2.0f);
  glVertex2f(-width/2.0f, -height/2.0f);
  glEnd();


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
  

  drawList = glGenLists(1);  

	//glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
	glutMainLoop(); // wejście do głównej pętli programu
	return 0;
}
