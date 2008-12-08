/* This example shows the effect of not enabling depth testing.  
 *
 * The camera is in a fixed position and two spheres are drawn.
 * The second sphere (red) rotates around the first sphere (green)
 * on the y axis.
 */

#if defined(__APPLE__) && defined(__MACH__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

static int depth = GL_TRUE;
int count = 0;
static float tree[12][3] = { {0,  0,  0}, {-.1,-.1,0}, {.1, -.1,0},
                             {-.2,-.2,0}, {0,  -.2,0}, {.2, -.2,0},
                             {-.1,-.3,0}, {.1, -.3,0}, {-.3,-.3,0},
                             {.3, -.3,0}, {0,  -.4,0}, {0,  -.5,0},
                           };
/* Initialize alpha blending function */
static void init(void) {
    glEnable(GL_DEPTH_TEST);
    printf("depth test enabled: %d\n", depth);
    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2);
}

void drawTree(void) {

    glEnable (GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = 0; i < count; ++i) {
        glVertex3f(tree[i][0],tree[i][1],tree[i][2]);
    }
    glEnd();

    glPushMatrix();
    glBegin(GL_LINES); 
        glVertex3f(0,-0.6,-0.9);
        glVertex3f(tree[count][0],tree[count][1],tree[count][2]);
    glEnd();
    glPopMatrix();
}

void drawLaser(void) {

}

void timer(int value) {
    glutPostRedisplay();
    if (count < (sizeof(tree) / sizeof(tree[0]))) {
        count++;
    } else {
        count = 0;
    }
    glutTimerFunc(250, timer, 0);  // re-register
}

void rect(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h, GLfloat d) {
    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

    glBegin( GL_LINE_LOOP );
        glVertex3f(x,y,z);
        glVertex3f(x+w,y,z);
        glVertex3f(x+w,y+h,z);
        glVertex3f(x,y+h,z);
    glEnd();

    glBegin( GL_LINE_LOOP );
        glVertex3f(x,y,z+d);
        glVertex3f(x+w,y,z+d);
        glVertex3f(x+w,y+h,z+d);
        glVertex3f(x,y+h,z+d);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(x,y,z);
        glVertex3f(x,y,z+d);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(x+w,y,z);
        glVertex3f(x+w,y,z+d);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(x+w,y+h,z);
        glVertex3f(x+w,y+h,z+d);
    glEnd();
        
    glBegin(GL_LINES);
        glVertex3f(x,y+h,z);
        glVertex3f(x,y+h,z+d);
    glEnd();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glColor3f( 0.0, 1.0, 0.0 );
        glRotatef(90, 0, 1, 0);
        rect(-.4,-.4,0,.4,.4,.4);
        glColor3f(1.0,0.0,0.0);
        glTranslatef(-.2,-.1,.4);
        glScalef(.5,.5,0);
        drawTree();
        glScalef(1,1,1);
    glPopMatrix();

    glutSwapBuffers();
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
        case 'd':
        case 'D':
            depth = !depth;
            if (depth) 
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
            printf("depth test enabled: %d\n", depth);
            glutPostRedisplay();
            break;
        case 27: /* esc */
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
