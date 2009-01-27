/* 
** File:	drawFilledPolygon.c
** Author:	Brian Gianforcaro
** Template by:	Warren R. Carithers
*/

#include <GL/glut.h>
#include <stdlib.h> //needed for abs()
#include <drawFilledPolygon.h>

typedef struct {
	int y_max;
        int x;
        int dx;
        int dy;
        int sum;
	struct Edge *next;
} Edge;


/**
 * update - update the value of the X using dx and dy without floating point .
 * args:
 *      b - The bucket that is to be adjusted
 *
 * return - The updated bucket
 */
Edge* update(Edge *e) {
    if( 0 != e->dx && 0 != e->dy ) {
        e->sum += e->dx;
        while(e->sum >= abs(e->dy)) {
            if(0 <= e->dy) {
                ++(e->x);
            } else {
                --(e->x);
            }
            e->sum -= abs(e->dy);
        }
    }
    return e;
}

/**
 * sortline - Iterate through, sort on x-values.  
 * args: 
 *       b - pointer to starting "bucket"
 *
 * return - The initial element in the sorted line
 */
Edge* sortline(Edge *line) {
    Edge *nb = line->next; 
    int count;;
    for ( count = 1; NULL != nb; nb = nb->next ) {
        count++;
    }
    
    Edge *first = line;
    for( int i = 0; i < count; i++) {
        Edge *curr = line;
        nb = line->next;
        while( NULL != nb ) {
            if( (nb->x < curr->x) || 
                ( nb->x == curr->x && nb->dx < curr->dx) ) {
                if(curr == first) {
                    first = nb;
                }
                curr->next = nb->next;
                nb->next = curr;
                nb = curr->next;
            } else {
                curr = nb;
                nb = nb->next;
            }
        }
    } return first;
}


/*
** drawFilledPolygon
**
** Draw a filled polygon using the scan-line-based polygon fill algorithm
** discussed in class. The polygon has n distinct vertices. Each vertex is
** a row in the v parameter; for vertex k, v[k][0] is the x coordinate, and
** v[k][1] the y coordinate.
*/

void drawFilledPolygon( GLint n, GLint v[][2] ) {

    int minScan , maxScan = v[0][1]; 
    //find min/max y-values
    for(int i = 0; i < n; i++) { 
        if(v[i][1] > maxScan) {
            maxScan = v[i][1];
        }

        if(v[i][1] < minScan) {
            minScan = v[i][1]; 
        }
    }

    // Initialize edge table to max possible size
    Edge *glet[maxScan];
    Edge *ael = NULL;  

    for( int i = 0; i <= maxScan; i++) {  
        glet[i] = NULL;
    }

    Edge *curr, *nBkt;
    int scanline;
    //Populate the global edge table
    for(int i = 0; i < n; i++) {  
        curr = (Edge *)malloc(sizeof(Edge));
        //proper rollover for end edge
        int j = ( i + 1 ) % n; 
        if( v[i][1] > v[j][1] ) {
            curr->y_max = v[i][1];
            curr->x = v[j][0];
            scanline = v[j][1];
        } else {
            curr->y_max = v[j][1];
            curr->x = v[i][0];
            scanline = v[i][1];	
        }

        if( v[i][0] > v[j][0] ) {
            curr->dx = v[i][0] - v[j][0];
            curr->dy = v[i][1] - v[j][1];
        } else {
            curr->dx = v[j][0] - v[i][0];
            curr->dy = v[j][1] - v[i][1];
        }
        curr->sum = 0;
        curr->next = NULL;
        if( NULL != glet[scanline] ) {
            nBkt = glet[scanline];
            while( NULL != nBkt->next) {
                nBkt = nBkt->next;
            }

            if( 0 != curr-> dy ) {
                nBkt->next = curr;
            }
        } else if( 0 != curr->dy ) {
            glet[scanline] = curr;
        }
        if( 0 == curr->dy )  {
            free(curr); 
        }
    }
    Edge *bkt1, *bkt2;
    for( int i = minScan; i <= maxScan; i++ ) { //iterate through scan lines, filling AEL
        if( NULL != ael ) {
            curr = ael;
            nBkt = ael->next;
            while( NULL != nBkt ) {
                if(nBkt->y_max == i) {
                    curr->next = nBkt->next;
                    free(nBkt);
                    nBkt = curr;
                }
                curr = nBkt;
                nBkt = nBkt->next;
            }

            if( NULL != glet[i] ) {
                curr->next = glet[i];
            }

            if( ael->y_max == i ) {
                nBkt = ael;
                ael = ael->next;
                free(nBkt);
            }
        }
            
        if( NULL != ael ) {
            ael = sortline(ael);
            bkt1 = ael;
            bkt2 = ael->next;
            while( NULL != bkt1 && NULL != bkt2 ) {
                glBegin(GL_POINTS);
                for( GLint j = bkt1->x; j < bkt2->x; j++ ){
                    glVertex2i(j,i);
                }
                glEnd();
                bkt1 = update(bkt1);
                bkt2 = update(bkt2);
                bkt1 = bkt2->next;
                if( NULL != bkt1 )  {
                    bkt2 = bkt1->next;
                }
            }
        } else if ( NULL != glet[i] ) {
            ael = glet[i];
        }
    }
}


