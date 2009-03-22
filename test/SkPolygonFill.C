//=============================================================================
//
//   (c) Copyright, 2009 Massachusetts Institute of Technology.
//
//   File: $RCSfile$
//   Version: $Revision$  Dated: $Date$
//
//=============================================================================

/**
 *
 *  @file SkPolygonFill.C
 *
 *  A sketch point clipping routine.
 *
 */

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include "GL/glut.h"

#include "SkPolygonFill.h"

#include <vector>
  using std::vector;

/*   
 *  We take all the the vertices of our polygon and build a global edge table
 *  (GLET). This holds a row for every row pixels in our polygon. 
 *
 *  We then start at the bottom of the GLE, and set the Active Edge List (AEL)
 *  to the current pixel row (scanline). All sets of pixels for the polygon are
 *  drawn left to write for this row. All drawn edges are updated to increment
 *  there dx dy value so they draw properly next time. Then go through the 
 *  AEL, checking if any active edges are finished being draw. If so prune 
 *  them, other wise move on to the next. After checking we  move to the next 
 *  pixel row (scanline) add any new active edges to the AEL and go on until the
 *  last pixel row is drawn.
 *
 *  @verbatim
 *  Triangle Example:
 *                                          AEL Contents
 *              (3,7)                      ------------
 *                *             7  maxScan  ^ 2 Edges
 *               * *            6           ^ 2 Edges
 *     Edge #1  *   *  Edge #2  5           ^ 2 Edges
 *             *     *          4           ^ 2 Edges
 *            *       *         3           ^ 2 Edges
 *           *         *        2           ^ 2 Edges  (Edge #3 finished)
 *          * * * * * * *       1  minScan  ^ 3 Edges
 *        (0,1)       (6,1)     0  start    ^  NULL
 *
 *             Edge #3
 *
 *
 *        row      GLET Contents
 *        --------------------
 *         7          NULL
 *         6          NULL
 *         5          NULL
 *         4          NULL
 *         3          NULL
 *         2          NULL
 *         1        Three Edges
 *         0          NULL
 *
 *  Once the three Edges are added to the AEL they stay there until
 *  the Edge has completed drawing. In a more complex example with
 *  Edges being added on various scanlines through out the algorithm
 *  the same would be true. When the AEL has contents (not NULL) the
 *  contents of the current GLET are appended to AEL linked list
 *  then sorted on their x, then dx values.
 *
 *  Example AEL data values.
 *                   |---------|-|   |---------|-|   |---------|-|
 *    AEL at row 1   | Edge #1 |*|-->| Edge #2 |*|-->| Edge #3 |-|
 *                   |---------|-|   |---------|-|   |---------|-|
 *
 *                    Edge #1 has smallest staring x & dx
 *                    Edge #2 has smallest dx
 *                    Edge #3 is last
 *  @endverbatim
 */

/*
 *  Routine to fill only a specified polygon region of a SkArray with actual
 *  data, all data outside the polygon is set to nil. The filling of data
 *  is achieved through the Scanline Fill Algorithm implementation described 
 *  above.
 *
 *  @param[in] input        SkArray you want the filling function to read from.
 *  @param[in] bounds       Set of points (CW) forming a polygon. 
 *
 *  @return             The new SkArray holding data only in the specified
 *                          polygon region.
 */

void SkPolygonFill(const vector<vector<int> > bounds )
{
  unsigned short int minScan = bounds.front()[VERT_Y];
  unsigned short int maxScan = bounds.front()[VERT_Y];

  // Find min/max  scan lines for our polygon
  for( unsigned short int i = 0; i < bounds.size(); i++ )
  {
    if( bounds[i][VERT_Y] > maxScan )
    {
      maxScan = bounds[i][VERT_Y];
    }

    if( bounds[i][VERT_Y] < minScan )
    {
      minScan = bounds[i][VERT_Y];
    }
  }

  // Initialize lLobal Edge Table to max possible size
  vector<PolyEdge*> globalEdgeTable;
  //globalEdgeTable.resize(maxScan);

  // Intialize all scan lines to NULL
  for( unsigned short int i = 0; i <= maxScan; i++ )
  {
    PolyEdge *tmp = NULL;
    globalEdgeTable.push_back(tmp);
  }


  // Populate the global edge table
  for( unsigned short int i = 0; i < bounds.size(); i++ )
  {
    PolyEdge::newEdge( i, globalEdgeTable, bounds );
  }

  // Active Edge List
  PolyEdge *activeEdgeList = NULL;

  // Then drawing if appropriate.
  for( unsigned short int i = minScan; i <= maxScan; i++ )
  {
    // Prune old edges which are not needed,
    // Added new edges to the current scan line Active Edge List
    if ( NULL != activeEdgeList )
    {
        activeEdgeList = PolyEdge::pruneAel( i, activeEdgeList, globalEdgeTable );

        if( NULL != activeEdgeList )
        {
          // Sort the List for the current scan line
          activeEdgeList = PolyEdge::sortLine( activeEdgeList );
          // Draw the current active edge list
          PolyEdge::drawAel( i, activeEdgeList );
        }
    }
    else if ( NULL != globalEdgeTable.at(i) )
    {
      activeEdgeList = globalEdgeTable.at(i);
    }
  }

  globalEdgeTable.clear();
}

/**
 *  Iterate throught the Active Edge List and prune old entries which
 *  have already been drawn and are no longer useful. Once the AEL is  pruned
 *  we add all new edges in the current scanline from the GLET to the AEL.
 *
 *  @param[in] indexOfGlet           Where we currently are in the Global Edge Tabe GLET.
 *  @param[in,out] activeEdgeList    A pointer to current Active Edge List (ael).
 *  @param[in] globalEdgeTable       A reference to the Global Edge Table
 *
 *  @return           A pointer to the front of the modified AEL.
 */

PolyEdge* PolyEdge::pruneAel( const unsigned short int indexOfGlet,
                              PolyEdge *activeEdgeList,
                              const vector<PolyEdge*> &globalEdgeTable )
{
  /*
  if ( 2770 == indexOfGlet )
  {
    asm("int3");
  }
  */
  // Current and Next Edge
  PolyEdge *currEdge = activeEdgeList;
  PolyEdge *nextEdge = activeEdgeList->next;
  while ( NULL != nextEdge )
  {
    // If the edges max scan line is the current
    // scan line, then we can remove it
    // and free it. (already drawn)
    if ( nextEdge->y_max == indexOfGlet )
    {
      currEdge->next = nextEdge->next;
      delete nextEdge;
      nextEdge = currEdge;
    }
    // Move on to the next in the current scanline
    currEdge = nextEdge;
    nextEdge = nextEdge->next;
  }
  // Now that we have pruned the AEL of all old edges
  // we can add all the edges for the new scanline.
  if ( NULL != globalEdgeTable[indexOfGlet] )
  {
    currEdge->next = globalEdgeTable.at(indexOfGlet);
  }

  if ( activeEdgeList->y_max == indexOfGlet )
  {
    nextEdge = activeEdgeList;
    activeEdgeList = activeEdgeList->next;
    if ( NULL != nextEdge )
    {
      delete nextEdge;
      nextEdge = NULL;
    }
  }
  return activeEdgeList;
}

/**
 *
 *  Create and setup a new edge (PolyEdge) for the given vertice i, and the
 *  next vertice in the bounds. Then insert this newly created edge into the
 *  Global Edge Table at the current scanline (pixel row).
 *
 *  @param[in] currentVertex      The current vertex the vector of vertices.
 *  @param[in] globalEdgeTable    A pointer to create Global Edge Table.
 *  @param[in] bounds             The vertices of the bounding polygon.
 *
 */

void PolyEdge::newEdge( const unsigned short int currentVertex,
                        vector<PolyEdge*> &globalEdgeTable,
                        const vector<vector<int> > bounds )
{

  PolyEdge *currEdge = new PolyEdge;

  unsigned short int scanline;

  // Proper rollover for end edge
  unsigned short int previousVertex = ( currentVertex + 1 ) % bounds.size();

  std::cout << "Connecting Point:(" << bounds[previousVertex][VERT_X] << ","  
	  						   << bounds[previousVertex][VERT_Y] << ") to Point:(" 
	  						   << bounds[currentVertex][VERT_X] << "," 
	  						   << bounds[currentVertex][VERT_Y] << ")" << std::endl;
  // Decide which vertex is the smallest which is equivelant
  // to the starting vertex in the GLET.
  if ( bounds[currentVertex][VERT_Y] > bounds[previousVertex][VERT_Y] )
  {
    currEdge->y_max = bounds[currentVertex][VERT_Y];
    currEdge->x = bounds[previousVertex][VERT_X];
    scanline = bounds[previousVertex][VERT_Y];
  }
  else
  {
    currEdge->y_max = bounds[previousVertex][VERT_Y];
    currEdge->x = bounds[currentVertex][VERT_X];
    scanline = bounds[currentVertex][VERT_Y];
  }

  // Make sure we have a positive dy and dx.
  currEdge->dx = abs( bounds[currentVertex][VERT_X]
                      - bounds[previousVertex][VERT_X] );

  currEdge->dy = abs( bounds[currentVertex][VERT_Y]
                      - bounds[previousVertex][VERT_Y] );

  // Initialize to default sane values.
  currEdge->slope = 0;
  currEdge->next = NULL;
 
  asm("int3");
  // If the current scan line happens to be empty
  // then just insert the previously created line segment.
  // Otherwise find the end (singly linked list), and insert it there.

  if( NULL != globalEdgeTable.at(scanline) )
  {
    PolyEdge *nextEdge = globalEdgeTable.at(scanline);
    // Find End of current scanline
    while( NULL != nextEdge->next )
    {
      nextEdge = nextEdge->next;
    }

    if( 0 != currEdge->dy )
    {
      nextEdge->next = currEdge;
    }
  }
  else if( 0 != currEdge->dy )
  {
    globalEdgeTable.at(scanline) = currEdge;
  }

  if( 0 == currEdge->dy )
  {
    delete currEdge;
    currEdge = NULL;
  }
}

/**
 *  Search through Active Edge List (ael) and clear out any edges that are
 *  out of range for the current scanline (already drawn). Next add all new
 *  Edges that are applicable to the current scanline.
 *
 *  @param[in] currentScanline      Index of the currently active scanline
 *  @param[in,out] activeEdgeList       A pointer to create Active Edge List.
 *  @param[in] saved_yp             A pointer to the input data.
 *  @param[in] saved_out_yp         A pointer to the output data.
 *  @param[in] xStride              How far to adjust pointer in x direction.
 *  @param[in] yStride              How far to adjust pointer in x direction.
 *
 */

void PolyEdge::drawAel( const unsigned short int currentScanline,
                        PolyEdge *activeEdgeList )
{
  // Current/Next Edge in the line.
  PolyEdge *currEdge = activeEdgeList;

  PolyEdge *nextEdge = activeEdgeList->next;

  while( NULL != currEdge && NULL != nextEdge )
  {
  
    // Draw at each pixel on the current scan line (y-value).
    // Starting from the current Edge X, until we hit the x
    // of the next in the list.

	glBegin(GL_POINTS);
    for( unsigned short int j = currEdge->x; j < nextEdge->x; j++)
    {
    	glVertex2i( j, currentScanline );
    }
	glEnd();
    // Update the data members for current and next edges.
    currEdge = PolyEdge::updateEdge( currEdge );

    nextEdge = PolyEdge::updateEdge( nextEdge );

    currEdge = nextEdge->next;

    if( NULL != currEdge )
    {
      nextEdge = currEdge->next;
    }
  }
}

/**
 *  Update the current Edges's x value, for non vertical/horizontal
 *  edges, using dx and dy. This allows us to start drawing at the
 *  correct x next time. We do this without using floating point
 *  numbers, because of the pixel (int,int) representation.
 *
 *  @param[in,out] edge  A pointer to  edge that is to be adjusted
 *
 *  @return      A pointer to the updated Edge.
 */

PolyEdge* PolyEdge::updateEdge( PolyEdge *edge )
{
  if( ( 0 != edge->dx ) &&  ( 0 != edge->dy ) )
  {
    edge->slope += edge->dx;
    // Move our x to the intercept of the current position
    // in the edge (line segment).
    while( edge->slope >= abs( edge->dy ) )
    {

      if( 0 < edge->dy )
      {
        (edge->x)++;
      }
      else
      {
        (edge->x)--;
      }

      edge->slope -= abs( edge->dy );
    }
  }
  return edge;
}

/**
 *  Iterate through the linked list of all of the the edges
 *  on the current scan line, sort on smallest x-values first then dx.
 *  Basic rough version of bubble sort.
 *
 *  @param[in] line      A pointer to starting Edge for the current scanline
 *
 *  @return         A pointer to the initial element in the sorted line.
 */

PolyEdge* PolyEdge::sortLine( PolyEdge *line )
{
  PolyEdge *currEdge = line->next;
  unsigned short int count;

  // Find the number of edges on the given scanline
  for ( count = 1; NULL != currEdge; currEdge = currEdge->next )
  {
    count++;
  }

  PolyEdge *nextEdge;
  PolyEdge *frontEdge = line;

  // Sort through N number (count) of times
  // To make all items are in there proper place.
  for( unsigned short int i = 0; i < count; i++ )
  {
    currEdge = line;
    nextEdge = line->next;

    while( NULL != nextEdge )
    {
      if( ( nextEdge->x < currEdge->x ) ||
          ( nextEdge->x == currEdge->x  &&
             ( nextEdge->dx < currEdge->dx ) ) )
      {
        // Update the front pointer Edge if appropriate.
        if( currEdge == frontEdge )
        {
          frontEdge = nextEdge;
        }
        // Swap
        currEdge->next = nextEdge->next;
        nextEdge->next = currEdge;
        nextEdge = currEdge->next;
      }
      else
      {
        // Go on to the the next edge.
        currEdge = nextEdge;
        nextEdge = nextEdge->next;
      }
    }
  }
  return frontEdge;
}
