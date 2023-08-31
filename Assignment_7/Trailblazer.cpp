/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "random.h"
using namespace std;

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
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */

Vector<Loc> shortestPath(	Loc start, Loc end,	Grid<double>& world, 
	double costFn(Loc from, Loc to, Grid<double>& world),
	double heuristic(Loc start, Loc end, Grid<double>& world)) {

	Vector<Loc> result; //This variable save the way to the destination
	Grid<Node> grid = filling(start.row, end.row, start.col, end.col, world); //Coloring all elements with gray
	findingPath(grid, world, start, end, costFn, result, heuristic); // Finding way to the dest and save information in result
    return result;
}

Set<Edge> createMaze(int numRows, int numCols) {
	TrailblazerPQueue<Edge> edges; //Priority queue for the edges
	fillingEdges(edges, numRows, numCols);
	Map<Loc, Set<Loc>> clusters = create(numRows, numCols);
	Set<Edge> result = findTree(edges, clusters);
    return result;
}

/*Methods for the shortest path*/

//Color all nodes with gray
Grid<Node> filling(int x1, int x2, int y1, int y2, Grid<double>& world){
	Grid<Node> result(world.nRows, world.nCols);
	for(int r = 0; r < result.nRows; r ++){
		for(int c = 0; c <  result.nCols; c ++){
			result[r][c].color = GRAY;
		}
	}
	return result;
}

/*While finding we should check neighbours of the current vertice*/
void findingPath(Grid<Node>& grid, Grid<double>& world, Loc& start, Loc& end, double costFn(Loc from, Loc to, Grid<double>& world), Vector<Loc>& result, double heuristic(Loc start, Loc end, Grid<double>& world)){
	TrailblazerPQueue<Loc> toVisit; //Saving vertices we should visit
	grid[start.row][start.col].color = YELLOW; //Color start node with yellow
	grid[start.row][start.col].weight = 0; //Give the start node 0 weight
	toVisit.enqueue(start, 0); //Add start node in toVisit queue
	/*Check vertices while toVisit is not empty*/
	while(!toVisit.isEmpty()){ 
		Loc loc = toVisit.dequeueMin(); //Take first element from the priority queue
		if(grid[loc.row][loc.col].color != GREEN){ 
			/*Coloring the vertice with green*/
			grid[loc.row][loc.col].color = GREEN; 
			colorCell(world, loc, GREEN);
			if(loc == end){ //If we reach final vertice we should stop
				saving(loc , world, grid, start,result); //Saving information(way to the destination) in result
				break;
			}
			checkingNeighbours(grid, loc , world, toVisit, costFn, heuristic, end); //Checking neighbouurs
		}
	}
}

/*This method save the information about the way*/
void saving(Loc loc, Grid<double>& world, Grid<Node>& grid, Loc& start, Vector<Loc>& result){
	while(true){
		Node curr = grid[loc.row][loc.col];
		result.add(loc);
		if(loc == start){
			break;
		}
		loc = curr.prev;
	}
}

/*Checking neughbours*/
void checkingNeighbours(Grid<Node>& grid, Loc& loc, Grid<double>& world, TrailblazerPQueue<Loc>& toVisit, double costFn(Loc from, Loc to, Grid<double>& world), double heuristic(Loc start, Loc end, Grid<double>& world), Loc& end){
	for(int r = max(0, loc.row-1) ; r <= min(grid.nRows-1, loc.row + 1); r ++){
		for(int c = max(0, loc.col-1); c <= min(grid.nCols-1, loc.col + 1); c++){
			if(loc.row != r || loc.col != c){
				Loc newLoc; newLoc.row = r; newLoc.col = c; 
				if(grid[r][c].color == GRAY){ //If vertice is gray
					/*Color this vertice with yellow*/
					colorCell(world, newLoc, YELLOW); 
					grid[r][c].color = YELLOW; 
					grid[r][c].weight = costFn(loc, newLoc, world) + grid[loc.row][loc.col].weight;
					grid[r][c].prev = loc;
					toVisit.enqueue(newLoc, grid[r][c].weight + heuristic(newLoc, end, world));

					/*If we have better way to the vertice which is already yellowed we should replace old way with the new way*/
				} else if(grid[r][c].color == YELLOW && costFn(loc, newLoc, world) + grid[loc.row][loc.col].weight < grid[r][c].weight){ 
					grid[r][c].weight = costFn(loc, newLoc, world) + grid[loc.row][loc.col].weight;
					grid[r][c].prev = loc;
					toVisit.decreaseKey(newLoc, grid[r][c].weight + heuristic(newLoc, end, world)); //Replace old way with new way
				}
			}
		}
	}
}

/*Methods for the createMaze*/

/*Saving edges in priority queue*/
void fillingEdges(TrailblazerPQueue<Edge>& edges, int& numRows, int& numCols){
	for(int r = 0; r < numRows - 1; r ++){
		for(int c = 0; c < numCols - 1; c ++){
			Loc curr; curr.row = r; curr.col = c; //Variable to save current vertice's location
			if(r + 1 < numRows){ //Vertice down to the current location 
				Loc newLoc; newLoc.row = r + 1; newLoc.col = c;
				Edge newEdge; newEdge.start = curr; newEdge.end = newLoc;
				edges.enqueue(newEdge, randomReal(0, 1));
			}
			if(c + 1 < numCols){//Vertice right to the curr location
				Loc newLoc; newLoc.row = r; newLoc.col = c + 1;
				Edge newEdge; newEdge.start = curr; newEdge.end = newLoc;
				edges.enqueue(newEdge, randomReal(0, 1));
			}
		}
	}
}

/*Map which save vertice as the key and vertices' collection as the cluster*/
Map<Loc, Set<Loc>> create(int numRows, int numCols){
	Map<Loc, Set<Loc>> result;
	for(int r = 0; r < numRows; r ++){
		for(int c = 0; c < numCols; c++){
			/*Saving information in the map*/
			Loc loc; loc.row = r; loc.col = c;
			Set<Loc> newSet; newSet.add(loc); 
			result.put(loc, newSet);	
		}
	}
	return result;
}	

/*Finding covering tree*/
Set<Edge> findTree(TrailblazerPQueue<Edge>& edges, Map<Loc, Set<Loc>>& clusters){
	Set<Edge> result; //Result to save edges of covering tree
	while(!edges.isEmpty()){ //While there are edges we should check 
		Edge output = edges.dequeueMin();
		/*If vertices locations of current edge are not in the same cluster*/
		if(clusters.get(output.start) != clusters.get(output.end)){
			merge(output.start, output.end, clusters); //Merging their clusters 
			result.add(output);//Adding new edge in the result 
		}
	}
	return result;
}

/*Merging clusters of two vertices' locations*/
void merge(Loc start, Loc end, Map<Loc, Set<Loc>>& clusters){
	Set<Loc> all = clusters[start] + clusters[end]; //New set which is merged cluster of two vertices' location
	foreach(Loc loc in all){
		clusters.put(loc, all); //Put new set as the value of vertices which are in this new set
	}
}
