#include <GL/freeglut.h> // dodanie biblioteki GLUT
#include <GL/glu.h>
#include <stdlib.h>

// funkcja obsługi klawiatury
void klawiatura(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 27:
    case 'q':
    exit(0);
    break;
  }
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawRect(int x, int y, int w, int h) {
  glVertex2f(x+w, y+h);
  glVertex2f(x+w, y);
  glVertex2f(x, y);
  glVertex2f(x, y+h);
}


// funkcja wyświetlająca obraz
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 1.0, 0.0);
  /*
  glBegin(GL_QUADS);
  drawRect(120, 120, 30, 200);
  drawRect(150, 290, 100, 30);
  drawRect(150, 220, 100, 30);
  glEnd();
  */

  glTranslatef(120.0f, 120.0f, 0.0f);
  glutSolidTeapot(100);
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ustawienie podwójnego
  glutInitWindowSize(640, 480); // rozmiar okna
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display); // ustawienie funkcji odpowiedzialnej za
  glutReshapeFunc(reshape); // ustawienie funkcji wywoływanej przy
  glutKeyboardFunc(klawiatura); // ustawienie funkcji obsługi klawiatury
  glutMainLoop(); // wejście do głównej pętli programu
  return 0;
}
