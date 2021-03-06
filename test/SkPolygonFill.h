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
 *  @file SkPolygonFill.h
 *
 *  Function declarations for the core Sketch Polygon Fill
 *  functions
 *
 */

#ifndef SK_POLYGON_FILL_H
#define SK_POLYGON_FILL_H

#include <vector>

static const int VERT_X = 0;
static const int VERT_Y = 1;

/**
 * Structure for holding information about one Edge
 * (ie. line segment) of a Polygon.
 *
 * Not desgined for use outside this, the SkPolyGonFill function call.
 */
class PolyEdge
{
  private:

    /** Maximum y value for the line */
    unsigned int y_max;
    /** The current x value to draw for the Edge. */
    double x;
    /** Change in x of the line */
    int dx;
    /** Change in y of the line */
    int dy;
    /** Inverse Slope Used to update the dy/dx of the Edge */
    double invSlope;
    /** Pointer to the next line segment on the same scanline. */
    PolyEdge *next;

  public:

    static PolyEdge* updateEdge( PolyEdge *edge );

    static PolyEdge* sortLine( PolyEdge *list );
    //static void sortLine( PolyEdge *line );

    static PolyEdge* pruneAel( const unsigned int indexOfGlet,
                               PolyEdge *activeEdgeList,
                               const std::vector<PolyEdge*> &globalEdgeTable );

    static void newEdge( const unsigned int currentVertex,
                         std::vector<PolyEdge*> &globalEdgeTable,
                         const std::vector<std::vector<int> > bounds );


    static void drawAel( const unsigned int currentScanline,
                         PolyEdge *activeEdgeList );
};

// Function prototypes
void SkPolygonFill( const std::vector<std::vector<int> > bounds );
#endif

