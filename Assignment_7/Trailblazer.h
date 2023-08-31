/******************************************************************************
 * File: Trailblazer.h
 *
 * Exports functions that use Dijkstra's algorithm, A* search, and Kruskal's
 * algorithm as specified in the assignment handout.
 */

#ifndef Trailblazer_Included
#define Trailblazer_Included

#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "set.h"
#include "grid.h"

struct Node{
	Loc prev;
	double weight;
	Color color;
};

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this function prototype and the
 * implementation inside of Trailblazer.cpp.
 */

Vector<Loc> shortestPath(Loc start, Loc end,	Grid<double>& world, 
	double costFn(Loc from, Loc to, Grid<double>& world),
	double heuristic(Loc start, Loc end, Grid<double>& world));

/* Function: createMaze
 * 
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols);

Grid<Node> filling(int x1, int x2, int y1, int y2, Grid<double>& world); //Color all nodes with gray

/*Finding the way to the destination*/
void findingPath(Grid<Node>& grid, Grid<double>& world, Loc& start, Loc& end, double costFn(Loc from, Loc to, Grid<double>& world), Vector<Loc>& result, double heuristic(Loc start, Loc end, Grid<double>& world));
/*While finding we should check neighbours of the current vertice*/
void checkingNeighbours(Grid<Node>& grid, Loc& loc, Grid<double>& world, TrailblazerPQueue<Loc>& toVisit, double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world), Loc& end);
/*This method save the information about the way*/
void saving(Loc loc, Grid<double>& world, Grid<Node>& grid, Loc& start, Vector<Loc>& result);
void fillingEdges(TrailblazerPQueue<Edge>& edges, int& numRows, int& numCols);
Map<Loc, Set<Loc>> create(int numRows, int numCols);
Set<Edge> findTree(TrailblazerPQueue<Edge>& edges, Map<Loc, Set<Loc>>& clusters);
void merge(Loc start, Loc end, Map<Loc, Set<Loc>>& clusters);

#endif
