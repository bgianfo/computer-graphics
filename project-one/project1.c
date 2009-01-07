/*
 * Computer Graphics - Project #1 
 *
 * Brian Gianforcaro - bjg1955@cs.rit.edu 
 *
 * GL_POINTS
 * GL_LINES
 * -DONE- At least one of GL_LINE_STRIP, GL_LINE_LOOP
 * -DONE- At least one of GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
 * -DONE- At least one of GL_QUADS, GL_QUAD_STRIP
 * GL_POLYGON
 *
 */

#if defined(__APPLE__) && defined(__MACH__)
#       include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Initialize alpha blending function */
static void init(void) {
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2);
}


void timer(int value) {
    glutPostRedisplay();
    /*
    if (count < (sizeof(tree) / sizeof(tree[0]))) {
        count++;
    } else {
        count = 0;
    }
    */
    glutTimerFunc(250, timer, 0);  // re-register
}

/* LINE SMOOTHING
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
*/

void drawCircle(float radius) {
    glBegin(GL_POLYGON);
    for (int i=0; i < 360; i++) {
        float degInRad = i*(3.14159/180);
        glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
    }
    glEnd();
}



void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    /*
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
    */

    
    glColor3f(0.6,0.3,0.0);
    glBegin(GL_QUADS);
        glVertex2f(-1,0);
        glVertex2f(1,0);
        glVertex2f(1,1);
        glVertex2f(-1,1);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1,-1.1);
        glVertex2f(1,-1.1);
        glVertex2f(1,-0.1);
        glVertex2f(-1,-0.1);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
        glTranslatef(-.65,-.15,0);
        glColor3f(0.2,1.0,.2);
        glBegin(GL_TRIANGLES);
            glVertex2f(0,0);
            glVertex2f(-.3,-.3);
            glVertex2f(.3,-.3);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-.65,.95,0);
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(0,0);
            glVertex2f(-.3,-.3);
            glVertex2f(.3,-.3);
        glEnd();
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


    glFlush();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w/(GLfloat)h, 1, 20);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: /* esc */
            exit(0);
            break;
        default:
            break;
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
    glutTimerFunc(250, timer, 0);
    glutMainLoop();
    return 0;
}
