#include <GL/freeglut.h> // dodanie biblioteki GLUT
#include <GL/freeglut_std.h>
#include <GL/gl.h>
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
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
  //gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
  glOrtho(0.0f, (GLdouble) w, 0.0f, (GLdouble)h, -100.0f, 100.0f);
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
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 1.0, 0.0);
  /*
  glBegin(GL_QUADS);
  drawRect(120, 120, 30, 200);
  drawRect(150, 290, 100, 30);
  drawRect(150, 220, 100, 30);
  glEnd();
  */
  glPushMatrix();
  
  glTranslatef(width / 2.0f, height / 2.0f, 0.0f);


  switch (shape) {
    case SPHERE:
      glutSolidSphere(100, 32, 16);
      break;
    case CONE:
      glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
      glutSolidCone(100.0f, 100.0f, 32, 16);
      break;
    case TEAPOT:
      glutSolidTeapot(100);
      break;
  }

  glPopMatrix();
  glutSwapBuffers();
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ustawienie podwójnego
  glutInitWindowSize(640, 480); // rozmiar okna
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display); // ustawienie funkcji odpowiedzialnej za
  glutReshapeFunc(reshape); // ustawienie funkcji wywoływanej przy
  glutKeyboardFunc(klawiatura); // ustawienie funkcji obsługi klawiatury
  glutMainLoop(); // wejście do głównej pętli programu
  glEnable(GL_DEPTH_TEST);
  return 0;
}
