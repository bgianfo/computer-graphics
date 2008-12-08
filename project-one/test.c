#include <stdlib.h>
#include <GL/glut.h>
const GLint HEIGHT = 300;
const GLint WIDTH = 400;
void init (void) {
    /* background color (white) */
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glEnable(GL_DEPTH_TEST);
    /* mapping of vertices to display */
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}
/**
 * Draw a line rectangle
 *
 */
void rect(GLint x, GLint y, GLint z, GLint w, GLint h) {
    glBegin( GL_LINE_LOOP );
        glVertex3i(x,y,z);
        glVertex3i(x+w,y,z);
        glVertex3i(x+w,y+h,z);
        glVertex3i(x,y+h,z);
    glEnd();
}


void display (void) {
    /* clear window to background color */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* draw in red */
    glColor3f( 1.0, 0.0, 0.0 );

    /* draw a line from (180,15) to (10,145) */

    glBegin( GL_LINES );
        glVertex2i( 180, 15 );
        glVertex2i( 10, 145 );
    glEnd();

    glPushMatrix();
        glColor3f( 0.0, 1.0, 0.0 );
        glRotatef(45, 0, 1, 0);

        rect(20,20,0,40,20);
        rect(20,20,1,40,20);
    glPopMatrix();

    /* ensure the display is updated */
    glFlush();
}

void keyboard( unsigned char key, int x, int y ) {
    /* ignores everything except 'q', 'Q', and ESC */
    switch( key ) {
      case 'q' : case 'Q' : case 033 :
        exit( EXIT_SUCCESS );
    }
}

int main( int argc, char** argv ) {

    /* configure and open window */
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH)/2)-(WIDTH/2), (glutGet(GLUT_SCREEN_HEIGHT)/2)-(HEIGHT/2) );
    glutInitWindowSize( WIDTH, HEIGHT );
    glutCreateWindow( "Brian Gianforcaro - CG1 Project #1" );

    /* set up OpenGL state */
    init();

    /* register callbacks */
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );

    glutMainLoop();	/* enter event loop */

    return( 0 );	/* not reached! */
}
