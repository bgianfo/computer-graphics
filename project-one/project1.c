/*
 * Computer Graphics - Project #1 
 *
 * Brian Gianforcaro - bjg1955@cs.rit.edu 
 * 
 *
 * 2.1
 * -DONE- GL_POINTS
 * -DONE- GL_LINES
 * -DONE- At least one of GL_LINE_STRIP, GL_LINE_LOOP
 * -DONE- At least one of GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
 * -DONE- At least one of GL_QUADS, GL_QUAD_STRIP
 * -DONE- GL_POLYGON
 * 2.2
 * -DONE- glutBitmapCharacter()
 * 2.3
 * -DONE- Filled polygon  	glPolygonStipple()
 * -DONE- glColor*()
 * -DONE- Line style 	glLineStipple(), glEnable(GL_LINE_STIPPLE)
 * -DONE- Line width 	glLineWidth()
 *
 * 2.4 
 * -DONE- User Input, quit on Q;
 */

#if defined(__APPLE__) && defined(__MACH__)
#       include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static const GLubyte stippleBits[32*4] = {
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
};

/* Initialize alpha blending function */
static void init(void) {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    glPointSize(2);
}


static void drawCircle(float radius) {
    glBegin(GL_POLYGON);
    for (int i=0; i < 360; i++) {
        float degInRad = i*(3.14159/180);
        glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
    }
    glEnd();
}

static void triangle(void) {
    glBegin(GL_TRIANGLES);
        glVertex2f(0,0);
        glVertex2f(-.3,-.3);
        glVertex2f(.3,-.3);
    glEnd();
}

/**
 * Draw a rectangle 
 * ARGS: var - which method to draw as.
 */
static void rectangle(int var) {
    glBegin(var);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(1,1);
        glVertex2f(-1,1);
    glEnd();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glEnable (GL_POLYGON_SMOOTH);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

    
    glColor3f(0.6,0.3,0.0);
    rectangle(GL_QUADS);

    glColor3f(1.0,1.0,1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1,-0.7);
        glVertex2f(1,-0.7);
        glVertex2f(1,-0.1);
        glVertex2f(-1,-0.1);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
        glTranslatef(-.65,-.15,0);
        glColor3f(0.2,1.0,.2);
        triangle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-.65,.95,0);
        glColor3f(0.0,0.0,0.0);
        triangle(); 
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0,0.0,0.0);
        glTranslatef(0.0,.78,0.0);
        drawCircle(0.18f);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0,0.0,0.0);
        glTranslatef(0.0,-0.3,0.0);
        drawCircle(0.18f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-0.05,0.0);
    glScalef(0.08,0.007,0.08);
    //glPointSize(0.5f);
    glBegin(GL_POINTS);
    for (float i=-19.0f; i < 109.5f; i += .5f) {
        glColor3f(0,i*.1,i*-.1);
        glVertex2f(i,sin(i)*3);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    char* string = "Brian Gianforcaro - RIT 2008/2009";
    int len = (int) strlen(string);
    glColor3f(1.0,1.0,1.0);
    glRasterPos2f(-0.4,1.05);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.45,-.54,0);
        glEnable(GL_POLYGON_STIPPLE);
        glPolygonStipple(stippleBits);
        glBegin(GL_POLYGON);
            glColor3f(1.0,0,0);
            glVertex2f(0,0);
            glColor3f(0,1.0,0);
            glVertex2f(.4,0);
            glColor3f(0,0,1.0);
            glVertex2f(.4,.4);
            glColor3f(1.0,1.0,1.0);
            glVertex2f(0,.4);
        glEnd();
    glPopMatrix();
    glDisable(GL_POLYGON_STIPPLE);

    glColor3f(0,0,0);
    glPushMatrix();
        glTranslatef(0.45,.56,0);
        glBegin(GL_POLYGON);
            glVertex2f(0,0);
            glVertex2f(.4,0);
            glVertex2f(.4,.4);
            glVertex2f(0,.4);
        glEnd();
    glPopMatrix();


    glColor3f(1,1,1);
    glDisable(GL_LINE_STIPPLE);
    glPushMatrix();
    glTranslatef(-1,-1.1,0);
        glBegin(GL_LINES);
        for (float i = 0; i < 2.1; i+=.1f) {
            glVertex2f(i, 0);
            glVertex2f(i, .3);
        }
        for (float i = 0; i < .35; i+=.05f) {
            glVertex2f(0, i);
            glVertex2f(2, i);
        }
        glEnd();
    glPopMatrix();


    glFlush();
}


static void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w/(GLfloat)h, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /* esc */
            exit(0);
            break;
        case 'q' :
        case 'Q' : 
            exit( EXIT_SUCCESS );
            break;
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            glPointSize(key*.03);
        default:
            glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(400, 400);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
