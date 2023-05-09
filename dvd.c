#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535
#define PI2 PI/2
#define PI3 3*PI/2

const int WIDTH = 512;
const int HEIGHT = 512;
SOCKET sock;

void changeSize(int w, int h) {

    // abbwabwbaba
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // use projection matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

float random(){
    float randn = ((float) rand() / (float)(RAND_MAX));
    if(randn < 0.05f)
        randn += 0.05f;
    return randn;
}

float angle;
float x = -9;
float y = -9;
int goingRight;
int goingUp;
float xincrement = 0.2f;
float yincrement = 0.2f;

float r, g, b;
int lineVertexCount = 0;
int drawLineMode = 0;

struct vertex {
    float vX;
    float vY;
};

struct vertex arr[10000];

void init(){
    glClearColor(0, 0, 0, 1);
}

void display(){
    //clears frame buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //resets transformation matrix
    glLoadIdentity();

    //draw
    glPointSize(10.0f);

    if(drawLineMode == 1){
        glLineWidth(2);

        glBegin(GL_LINE_STRIP);
        glColor4f(1, 1, 1, 1);
        for(int i = 0; i < 10000; i++){
            if(i >= lineVertexCount)
                break;
            glVertex2d(arr[i].vX, arr[i].vY);
        }
        glVertex2d(x, y);
        glEnd();
    }

    glColor4f(r, g, b, 1);
    glBegin(GL_POLYGON);

    glVertex2d(x-1,y+1);
    glVertex2d(x-1,y-1);
    glVertex2d(x+1.0,y-1);
    glVertex2d(x+1.0,y+1);

    glEnd();

    //displays frame buffer
    glutSwapBuffers();
}

void initRandomColors(){
    r = random();
    g = random();
    b = random();
}

void addVertex(){
    arr[lineVertexCount].vX = x;
    arr[lineVertexCount].vY = y;
    lineVertexCount++;
}

void animate(){
    glutPostRedisplay();
    glutTimerFunc(1000/60, animate, 0);

    if(x > 9){
        goingRight = 0;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(x < -9){
        goingRight = 1;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(y > 9){
        goingUp = 0;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(y < -9){
        goingUp = 1;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    switch(goingRight){
        case 0:
            x-=xincrement;
            break;
        case 1:
            x+=xincrement;
            break;
    }

    switch(goingUp){
        case 0:
            y-=yincrement;
            break;
        case 1:
            y+=yincrement;
            break;
    }

}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    //reset projection matrix
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

    drawLineMode = 1;

    srand(2);
    angle = (rand() % 360) * (M_PI / 180);
    printf("Angle: %f rad\n", angle);
    printf("Angle: %f deg\n", (180/M_PI) * angle);
    r = random();
    g = random();
    b = random();
    xincrement = cosf(angle)/4;
    yincrement = sinf(angle)/4;
    if(fabs(xincrement) < M_PI/2){
        goingRight = 1;
    } else if(fabs(xincrement) < M_PI/2) {
        goingRight = 0;
    }

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("dvd logo (real dvd logo (real))");

    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, animate, 0);
    init();
    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}