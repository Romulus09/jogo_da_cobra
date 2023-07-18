
//controle do ombro é feito com as teclas "s" e "d"
 //controle do antebraço é feito com teclas "e" e "r"
 // controle da mão é feito com teclas "x" e "c"





#include <GL/glut.h>



#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, hand = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();


    glTranslatef(0.25, 0.0, 0.0);
    glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    //glScalef(2.0, 0.4, 1.0);
    glutWireCube(0.5);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {

        // rotação do ombro
    case 's':
        shoulder = (shoulder + 5) % 360;
        glutPostRedisplay();                     
        break;
    case 'd':
        shoulder = (shoulder - 5) % 360;
        glutPostRedisplay();
        break;


        // rotação do antebraço
    case 'e':
        elbow = (elbow + 5) % 360;
        glutPostRedisplay();
        break;
    case 'r':
        elbow = (elbow - 5) % 360;
        glutPostRedisplay();                     
        break;

        //rotação da mão

    case 'x':
        hand = (hand + 5) % 360;               
        glutPostRedisplay();
        break;
    case 'c':
        hand = (hand - 5) % 360;
        glutPostRedisplay();
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
