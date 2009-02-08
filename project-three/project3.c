#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tga.h" //Using Nate Miller's TGA library
#if defined(__APPLE__) && defined(__MACH__)
#	include <GLUT/glut.h>
#else
#	include <GL/glut.h>
#endif

//Window WIDTH/HEIGHT
const static int WIDTH = 800;
const static int HEIGHT = 600;

int window; //Keep window ID so we can dispose it later
int spin = 0; // spinning for teapot/sphere's
float movementy = 9; //current y value of the donought
int direction = 1; //which direction the donought is currently going
GLboolean animate = GL_FALSE; //Animation control

GLuint texture1; //teapot texture
GLuint texture2; //sphere texture

//Material Properties for big and small sphere's
float m1color[] = { 0.0f, 0.0f, 0.0f, 1.0f};
float m1emissive[] = { 0.0f, 0.0f, 0.0f, 0.0f};
float m1specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};

//Material properties for the Teapot
float m2color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
float m2emissive[] = { 0.0f, 0.0f, 0.0f, 0.0f};
float m2specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};

//Material properties for the Teapot stand
float m3color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
float m3emissive[] = { 0.2f, 0.2f, 0.2f, 1.0f};
float m3specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};


//Material properties for the donought
float m4color[] = { 0.0f, 0.0f, 0.0f, 1.0f};
float m4emissive[] = { 1.0f, 0.0f, 0.0f, 1.0f};
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
    glMaterialfv(GL_FRONT, GL_EMISSION, m1emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    for (int i = 0; i < 360; i=i+15) {
        glPushMatrix();
            glRotatef(spin,1.0,1.0,1.0);
            glPushMatrix();
				//Draw large sphere's
                int rad = 10;
                float deginRad = i*(3.1459/180.0);
                glTranslatef(cos(deginRad)*rad, sin(deginRad)*rad, 0.0f);
                glPushMatrix();
                    glRotatef(-(spin),1.0,1.0,0.0);
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texture2);
    				glColor3f(0.9f,0.1f,0.3f);
                    gluSphere(quad,.75,20,20);
					glPushMatrix();
						//Draw smaller sphere's
						glRotatef(-spin,1.0,1.0,1.0);
						for (int j = 0; j < 360; j=j+15) {
							float rad2 = .3;
							float deginRad2 = j*(3.1459/180.0);
							glTranslatef(cos(deginRad2)*rad2, sin(deginRad2)*rad2, 0.0f);
							glPushMatrix();
								glTranslatef(0.0,-1.1,0.0);
								glRotatef((spin),1.0,1.0,0.0);
								//Augment color based on spin val
								glColor3f(spin*.001,0.5,spin*.001);
								gluSphere(quad,.10,20,20);
							glPopMatrix();
						}
					glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    }
	gluDeleteQuadric(quad);

	//Draw the pimp'd out teapot
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m2color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m2specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m2emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 60);
    glColor3f(0.6,0.7,0.7);
    glPushMatrix();
        glRotatef(spin,0.0,1.0,0.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glutSolidTeapot(3);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	//Draw the cone for the bottom of the 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, m3color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m3specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, m3emissive);
    glMateriali(GL_FRONT, GL_SHININESS, 120);
    glColor3f(0.5,0.5,0.9);
	//Augment color of the cone based on movement of the donought
    glColor3f((abs(movementy)*.3)+.1,(movementy*.3)+.1,(abs(movementy)*.3)+.1);
    glPushMatrix();
        glTranslatef(0.0,-5.0,0.0);
        glRotatef(90.0,-1.0,0.0,0.0);
        glutWireCone(3,3,30,30);
    glPopMatrix();

	//Draw the orange donought around the outside
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
				//Clean Up textures/window and exit
                glDeleteTextures(1,&texture1);
                glDeleteTextures(1,&texture2);
                glutDestroyWindow(window);
                exit( EXIT_SUCCESS );
                break;
        case '1':
               //Select camera position 1 "normal"
        		printf("Camera #1 Selected.\n");
                glMatrixMode(GL_PROJECTION); 
                glLoadIdentity();
                gluPerspective(90.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
                glMatrixMode(GL_MODELVIEW); 
                glutPostRedisplay();
                break;
        case '2':
                //Select camera position 2 "zoomed out"
        		printf("Camera #3 Selected.\n");
				glMatrixMode(GL_PROJECTION); 
                glLoadIdentity();
                gluPerspective(35.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
                glMatrixMode(GL_MODELVIEW);
                glutPostRedisplay();
                break;
		case '3':
                //Select camera position 3 "zoomed in"
        		printf("Camera #3 Selected.\n");
                glMatrixMode(GL_PROJECTION); 
                glLoadIdentity();
                glOrtho(-2.0*64/48.0, 2.0*64/48.0, -2.0, 2.0, 0.1, 100);
                glMatrixMode(GL_MODELVIEW); 
                glLoadIdentity();
                gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
                glutPostRedisplay();
				break;

        case '5':
                //Toggle first light source
        		printf("Light Source #1 toggled.\n");
                glIsEnabled(GL_LIGHT0) ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
                glutPostRedisplay();
                break;
        case '6':
                //Toggle second light source
        		printf("Light Source #2 toggled.\n");
                glIsEnabled(GL_LIGHT1) ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
                glutPostRedisplay();
                break;
        case 'a':
                //Toggle animation state
        		printf("Amimation toggled.\n");
                animate = (animate == GL_FALSE) ? GL_TRUE : GL_FALSE;
                glutPostRedisplay();
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
			//alternate motion back and forth
            if (abs(movementy) >= 10 ) {
				direction = (direction == 1) ? 0 : 1;
            }
            movementy = (direction == 0) ? movementy+.09:movementy-.09;
            glutPostRedisplay();
        }
        glutTimerFunc(15,timer,0);
    }
}

/**
 * Description: Setup camera, enable lighting, textures etc.  
 * Args
 *  	 none
 */
static void init ( void )
{
    glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0 );
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
	
	//Setup initial camera
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(90.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW); 

    glEnable(GL_LIGHTING);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable ( GL_COLOR_MATERIAL ) ;

	//Setup our two lights
    GLfloat light_pos[] = {3.0,3.0,3.0,0.0};
    GLfloat light_spec[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

    GLfloat light2_pos[] = {-3.0,-3.0,3.0,1.0};
    GLfloat light2_spec[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light2_pos);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2_spec);

	//Generate our textures, then bind them to the .tga's
    glGenTextures( 1, &texture1 );
    glGenTextures( 1, &texture2 );

    glBindTexture( GL_TEXTURE_2D, texture1 );
    if (loadTGA("metal.tga", texture1)) {
        printf("Texture \"metal.tga\" successfully loaded.\n");
    } else {
        printf("Texture \"metal.tga\" failed to load\n");
    }

    glBindTexture( GL_TEXTURE_2D, texture2 );
    if (loadTGA("grid.tga", texture2)) {
        printf("Texture \"grid.tga\" successfully loaded.\n");
    } else {
        printf("Texture \"grid.tga\" failed to load\n");
    }
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
	//Center window on screen
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
