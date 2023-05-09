
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
float left = -40, top = 40, right = 40, bottom = -40;
float inverseSpeed = 4;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    // Use the Projection Matrix
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
float x = -10;
float y = -10;
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

struct vertex snake[8];

struct vertex arr[10000];

void init(){
    glClearColor(0, 0, 0, 1);
}

void display(){
    //clears frame buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //resets transformation matrix (resets transformations and coordinate system)
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

    for(int i = 7; i >= 1; i--){
        printf("box %d's position: (%f, %f)\n", i, snake[i].vX, snake[i].vY);
    }

    for(int i = 7; i >= 1; i--){
        snake[i].vX = snake[i + 1].vX;
        snake[i].vY = snake[i + 1].vY;
        printf("changing box %d to box %d's position: (%f, %f) --> (%f, %f)\n", i, i + 1, snake[i].vX, snake[i].vY,  snake[i + 1].vX, snake[i + 1].vY);
    }
    snake[0].vX += xincrement;
    snake[0].vY += yincrement;

    glColor4f(1, 1, 1, 1);
    for(int i = 0; i < 8; i++){
        glBegin(GL_POLYGON);
        float x = snake[i].vX;
        float y = snake[i].vY;

        glVertex2d(x-1,y+1);
        glVertex2d(x-1,y-1);
        glVertex2d(x+1.0,y-1);
        glVertex2d(x+1.0,y+1);

        glEnd();
    }

    glColor4f(1, 1, 1, 1);
    glBegin(GL_LINES);

    glVertex2d(snake[0].vX, snake[0].vY);
    glVertex2d(snake[0].vX + xincrement * 9, snake[0].vY + yincrement * 9);

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

void buttons(unsigned char key, int x, int y){
    puts("triggered");
    if(key == 'a'){
        angle+=0.1f;
        if(angle >= 2 * M_PI)
            angle = 0;
        xincrement = cosf(angle)/inverseSpeed;
        yincrement = sinf(angle)/inverseSpeed;
        printf("%f, yinc: %f, xinc: %f\n", angle, xincrement, yincrement);
    }
    if(key == 'd'){
        angle-=0.1f;
        if(angle < 0)
            angle = 2 * M_PI;
        xincrement = cosf(angle)/inverseSpeed;
        yincrement = sinf(angle)/inverseSpeed;
        printf("%f, xinc: %f, yinc: %f\n", angle, xincrement, yincrement);
    }
    if(key == 'w'){
        if(inverseSpeed > 0.6f) {
            inverseSpeed -= 0.3f;
        }
        xincrement = cosf(angle)/inverseSpeed;
        yincrement = sinf(angle)/inverseSpeed;
    }
    if(key == 's'){
        if(inverseSpeed < 20) {
            inverseSpeed += 0.3f;
        }
        xincrement = cosf(angle)/inverseSpeed;
        yincrement = sinf(angle)/inverseSpeed;
    }
}

void animate(){
    glutPostRedisplay();
    glutTimerFunc(1000/60, animate, 0);

    if(snake[0].vX > right){
        snake[0].vX = left;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(snake[0].vX < left){
        snake[0].vX = right;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(snake[0].vY > top){
        snake[0].vY = bottom;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }

    if(snake[0].vY < bottom){
        snake[0].vY = top;
        initRandomColors();
        if(drawLineMode == 1){
            addVertex();
        }
    }



}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    //reset projection matrix
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

    drawLineMode = 0;

    angle = M_PI/(3.23523525);
    printf("Angle: %f rad\n", angle);
    printf("Angle: %f deg\n", (180/M_PI) * angle);
    r = random();
    g = random();
    b = random();
    //init snake
    for(int i = 0; i < 8; i++){
        snake[i].vX = x - (float)i * 2;
        snake[i].vY = y - (float)i * 2;
        printf("box %d's position: (%f, %f)\n", i, snake[i].vX, snake[i].vY);
    }
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
    glutInitWindowSize(900,900);
    glutCreateWindow("dvd logo (real dvd logo (real))");

    // register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, animate, 0);
    glutKeyboardFunc(buttons);
    init();
    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
