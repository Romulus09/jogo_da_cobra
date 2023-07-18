#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>





#define ROWS 40.0
#define COLUMNS 40.0

#define GAME_H_INCLUDED

#define MAX 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

void initGrid(int, int);
void draw_grid();
void draw_food();
void draw_snake();


bool game_over = false;
extern int sDirection;
int score = 0;

void init();
void display_callback();
void input_callback(int, int, int);
void reshape_callback(int, int);
void timer_callback(int);

void unit(int, int);
int random(int, int);

bool length_inc = false;
bool seedflag = false;
extern int score;
extern bool game_over;
bool food = false,game_start = true;
int rows = 0, columns = 0;
int sDirection = RIGHT;
int foodx, foody, menuId;//obsy, obsx, obsx2, obsy2, obsx3, obsy3,menuId;
float obsy, obsx, obsx2, obsy2, obsx3, obsy3;


int posx[MAX + 1] = { 4,3,2,1,0,-1,-1 };
int posy[MAX + 1] = { 10,10,10,10,10,10,10 };
int length = 7;
int cont = 0;

GLfloat triangleX = 0.2f;
GLfloat triangleY = 0.2f;



void menu(int option)
{
    if (option == 0)
    {
        glutDestroyWindow(glutGetWindow());
        exit(0);
    }
    else if (option == 1)
        glutFullScreen();

    /*if (option == 2)
    {
        game_start = true;
        glutPostRedisplay();
    } */
}



void createMenu()
{
    // Create the menu and set the menu function
    menuId = glutCreateMenu(menu);

    // Add menu items
    glutAddMenuEntry("Quit", 0);
    glutAddMenuEntry("Fullscreen", 1);
    //glutAddMenuEntry("Start", 2);

    // Attach the menu to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void displayStartScreen()
{
    
    
    glViewport(0, 0, 600, 600);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render the start screen text
    std::string text = "Game Over !";
    glRasterPos2f(600 / 2 - 40, 600 / 2);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glFlush();
}

void display() {
    if (game_start)
        display_callback();
    else
        displayStartScreen();
}
void initGrid(int x, int y)
{
    columns = x;
    rows = y;
}

void draw_grid()
{
    for (int i = 0;i < columns;i++)
    {
        for (int j = 0;j < rows;j++)
        {
            unit(i, j);
        }
    }
}




void draw_obstacle()
{
    if (!food) {
        using namespace std::this_thread; // sleep_for, sleep_until
        using namespace std::chrono; // nanoseconds, system_clock, seconds
        obsx = random(2, columns - 5);
        obsy = random(2, rows - 3);

        
        
        obsx2 = random(2, columns - 5);
        obsy2 = random(2, rows - 3);
        
        
        obsx3 = random(2, columns - 5);
        obsy3 = random(2, rows - 3);
        

    }


    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
   // glPushMatrix();
    glTranslatef(triangleX,0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0,0.0);
    glVertex2d(obsx, obsy); glVertex2d(obsx + 3, obsy); glVertex2d(obsx + 3, obsy + 3); glVertex2d(obsx, obsy + 3);
    glEnd();
    //glPopMatrix();

    
    glLoadIdentity();
    //glPushMatrix();
    glTranslatef(0.0f, triangleY, 0.0f);
    glBegin(GL_POLYGON);
    glColor3f(0.32, 0.5, 1.0);
    glVertex2d(obsx2, obsy2); glVertex2d(obsx2 + 3, obsy2); glVertex2d(obsx2 + 3, obsy2 + 3); glVertex2d(obsx2, obsy2 + 3);
    glEnd();
    //glPopMatrix();


    //glLoadIdentity();
    //glPushMatrix();
    glTranslatef(triangleX, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.3, 1.0);
    glVertex2d(obsx3, obsy3); glVertex2d(obsx3 + 3, obsy3); glVertex2d(obsx3 + 3, obsy3 + 3); glVertex2d(obsx3, obsy3 + 3);
    glEnd();
    //glPopMatrix();

   

}

void draw_snake()
{
    for (int i = length - 1;i > 0;i--)
    {
        posx[i] = posx[i - 1];
        posy[i] = posy[i - 1];
    }
    for (int i = 0;i < length;i++)
    {
        glColor3f(0.0, 1.0, 0.0);
        if (i == 0)
        {
            glColor3f(0.0, 0.0, 1.0);
            switch (sDirection)
            {
            case UP:
                posy[i]++;
                break;
            case DOWN:
                posy[i]--;
                break;
            case RIGHT:
                posx[i]++;
                break;
            case LEFT:
                posx[i]--;
                break;
            }
            if (posx[i] == 0 || posx[i] == columns - 1 || posy[i] == 0 || posy[i] == rows - 1)
                game_over = true;
               // displayStartScreen();

            else if (posx[i] >= obsx && posx[i] <= obsx + 3 && posy[i] >=obsy && posy[i] <= obsy + 3)
                game_over = true;

            else if (posx[i] >= obsx2 && posx[i] <= obsx2 + 3 && posy[i] >= obsy2 && posy[i] <= obsy2 + 3)
                game_over = true;

            else if (posx[i] >= obsx3 && posx[i] <= obsx3 + 3 && posy[i] >= obsy3 && posy[i] <= obsy3 + 3)
                game_over = true;

            else if (posx[i] == foodx && posy[i] == foody)
            {
                food = false;
                score++;
                if (length <= MAX)
                    length_inc = true;
                
            }
            for (int j = 1;j < length;j++)
            {
                if (posx[j] == posx[0] && posy[j] == posy[0])
                    game_over = true;
                
            }
        }
        glBegin(GL_QUADS);
        glVertex2d(posx[i], posy[i]); glVertex2d(posx[i] + 1, posy[i]); glVertex2d(posx[i] + 1, posy[i] + 1); glVertex2d(posx[i], posy[i] + 1);
        glEnd();
    }
    if (length_inc)
    {
        length++;
        length_inc = false;
    }
}

void draw_food()
{
    if (!food)
    {
        foodx = random(2, columns - 2);
        foody = random(2, rows - 2);
       



        food = true;
    }
    glBegin(GL_QUADS);
    glVertex2d(foodx, foody); glVertex2d(foodx + 1, foody); glVertex2d(foodx + 1, foody + 1); glVertex2d(foodx, foody + 1);
    
    glEnd();
}

void unit(int x, int y)
{
    glLoadIdentity();
    if (x == 0 || x == columns - 1 || y == 0 || y == rows - 1)
    {
        glLineWidth(4.0);
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0);
        glLineWidth(1.0);
    }
    glBegin(GL_LINES);
    glVertex2d(x, y); glVertex2d(x + 1, y);
    glVertex2d(x + 1, y); glVertex2d(x + 1, y + 1);
    glVertex2d(x + 1, y + 1); glVertex2d(x, y + 1);
    glVertex2d(x, y + 1); glVertex2d(x, y);
    glEnd();
}
int random(int _min, int _max)
{
    cont+=rand()%100;
    srand(time(NULL)*cont);
    return _min + rand() % (_max - _min);
}







int main(int argc, char** argv)
{
    
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowPosition(10, 10);
        glutInitWindowSize(600, 600);
        glutCreateWindow("SNAKE v1.0");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape_callback);
        glutSpecialFunc(input_callback);
        glutTimerFunc(100, timer_callback, 0);
        init();
        createMenu();
        glutMainLoop();
        return 0;
    
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(COLUMNS, ROWS);
}

//Callbacks
void display_callback()
{
    //if (game_over)glutDestroyWindow(glutGetWindow());
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if (game_over) { displayStartScreen(); }
    draw_grid();
    draw_food();
    draw_snake();
    draw_obstacle();
   
    
    glutSwapBuffers();
}
void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLfloat)w, GLfloat(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int)
{
    int i = 0;
    

    triangleX = 0.2f;
    triangleY = 0.2f;
    obsx += 0.2f;
    obsy2 += 0.2f;
    obsy3 += 0.2f;

    

    if (triangleX > 10.0f)
        triangleX = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(100, timer_callback, 0);
}
void input_callback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    }
}

