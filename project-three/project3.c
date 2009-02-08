#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tga.h"
#if defined(__APPLE__) && defined(__MACH__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

const static int WIDTH = 800;
const static int HEIGHT = 600;
int window;
int spin = 0;
float movementy = -5;
int direction = 1;
GLboolean animate = GL_FALSE;

GLuint texture1;
GLuint texture2;

float m1color[] = { 0.0f, 1.0f, 0.0f, 1.0f};
float m1diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f};
float m1emissive[] = { 0.0f, 0.0f, 0.0f, 0.0f};
float m1specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};

float m2color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
float m2emissive[] = { 0.0f, 0.0f, 0.0f, 0.0f};
float m2diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f};
float m2specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};

float m3color[] = { 0.3f, 0.3f, 0.3f, 0.0f};
float m3emissive[] = { 0.0f, 0.0f, 0.0f, 0.0f};
float m3diffuse[] = { 0.0f, 0.0f, 1.0f, 0.0f};
float m3specular[] = { 0.3f, 0.3f, 0.3f, 1.0f};

float m4color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
float m4emissive[] = { 1.0f, 0.0f, 0.0f, 1.0f};
float m4diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f};
float m4specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};



/**
 * Cordinate all scene drawing.
 * Args:
 * 		none
 */
static void display ( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glTranslatef(0.0,0.0,-30.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m1color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m1specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m3emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glColor3f(0.8f,0.22f,0.2f);
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    for (int i = 0; i < 360; i=i+15) {
        glPushMatrix();
            glRotatef(spin,1.0,1.0,1.0);
            glPushMatrix();
                int rad = 10;
                float deginRad = i*(3.1459/180.0);
                glTranslatef(cos(deginRad)*rad, sin(deginRad)*rad, 0.0f);
                glPushMatrix();
                    glRotatef(-(spin),1.0,1.0,0.0);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture2);
                    gluSphere(quad,1,20,20);
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    }

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m2color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m2specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m2emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 60);
    glColor3f(0.2,0.2,0.8);
    glPushMatrix();
        glRotatef(spin,0.0,1.0,0.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glutSolidTeapot(3);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m3color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m3specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m3emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
    glColor3f(0.2,0.2,0.5);
    glPushMatrix();
        glTranslatef(0.0,-4.0,0.0);
        glRotatef(90.0,-1.0,0.0,0.0);
        glutSolidCone(3,3,20,20);
    glPopMatrix();


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m4color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m4specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m4emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 60);
    glColor3f(0.11,0.8,0.13);
    glPushMatrix();
        glTranslatef(0.0,movementy,0.0);
        glPushMatrix();
            glScalef(1.0,movementy/2,1.0);
            glRotatef(90,1.0,0.0,0.0);
            glutSolidTorus(.5,14,50,50);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

/**
 * Description: Catch keyboard args handle appropriately.
 * Args:
 * 		key - key which has been called. 
 * 		x - The X cordinate in the window when key was pressed.
 * 		y - The Y cordinate in the window when key was pressed.
 */
static void keyboard ( unsigned char key, int x, int y )
{
    switch ( key ) {
        case 'q':
        case 'Q':
        case 033:
                glDeleteTextures(1,&texture1);
                glDeleteTextures(1,&texture2);
                glutDestroyWindow(window);
                exit( EXIT_SUCCESS );
                break;
        case '1':
               //Select camera position 2
                glMatrixMode(GL_PROJECTION); // set the view volume shape
                glLoadIdentity();
                gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
                glMatrixMode(GL_MODELVIEW); // position and aim the camera
                glutPostRedisplay();
                break;
        case '2':
                //Select camera position 1
                glMatrixMode(GL_PROJECTION); // set the view volume shape
                glLoadIdentity();
                glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
                glMatrixMode(GL_MODELVIEW); // position and aim the camera
                glLoadIdentity();
                gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
                glutPostRedisplay();
                break;
        case '5':
                //Toggle first light source
                glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
                glutPostRedisplay();
                break;
        case '6':
                //Toggle second light source
                glIsEnabled(GL_LIGHT1) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
                glutPostRedisplay();
                break;
        case 'a':
                //Toggle animation state
                animate = (animate == GL_FALSE) ? GL_TRUE : GL_FALSE;
                break;
	}
}

/**
 * Description: Handle timer events
 * Args:
 * 		timernum - integer identifying which timer was called
 */
void timer(int timernum) 
{
    if (0 == timernum ) {
        if (animate == GL_TRUE) {
            spin++;
            if (abs(movementy) >= 10 ) {
                if (direction == 1) {
                    direction = 0;
                } else {
                    direction = 1;
                }
            }
            movementy = (direction == 0) ? movementy+.03:movementy-.03;
            glutPostRedisplay();
        }
        glutTimerFunc(15,timer,0);
    }
}

/**
 * Description: Setup openGL viewport/lookat, enable lighting etc.  
 * Args:
 *  	 none
 */
static void init ( void )
{
    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0 );
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera

    glEnable(GL_LIGHTING);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;

    GLfloat light_pos[] = {3.0,3.0,3.0,0.0};
    GLfloat light_spec[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

    GLfloat light2_pos[] = {-3.0,-3.0,3.0,1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_spec);

    glGenTextures( 1, &texture1 );
    glGenTextures( 1, &texture2 );

    glBindTexture( GL_TEXTURE_2D, texture1 );
    if (loadTGA("metal.tga", texture1)) {
        printf("Texture \"weird.tga\" successfully loaded\n");
    } else {
        printf("Texture \"weird.tga\" failed to load\n");
    }

    glBindTexture( GL_TEXTURE_2D, texture2 );
    if (loadTGA("grid.tga", texture2)) {
        printf("Texture \"metal.tga\" successfully loaded\n");
    } else {
        printf("Texture \"metal.tga\" failed to load\n");
    }

     glEnable (GL_BLEND);
     glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
}


/**
 * Define our GLUT Window and callbacks
 * Args:
 * 		argc - number of args
 *		argv - char pionter array to commanline args
 */
int main ( int argc, char** argv ) 
{
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH)/2)-(WIDTH/2), (glutGet(GLUT_SCREEN_HEIGHT)/2)-(HEIGHT/2));
	glutInitWindowSize( WIDTH, HEIGHT );
	window = glutCreateWindow( "Project #3" );
	init();
	glutDisplayFunc( display );
	glutTimerFunc(0,timer,0);
	glutKeyboardFunc( keyboard );
	glutMainLoop();
	return( 0 );
}
