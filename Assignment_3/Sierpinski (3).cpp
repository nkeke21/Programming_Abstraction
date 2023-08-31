/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "math.h" 
#include "gwindow.h"
#include "simpio.h"
using namespace std;

void coordinates(double& x0, double& y0, double length, GWindow& name); // Method, where we determine start x and y coordinate where the peak of triangle is
void drawFirstTriangle(double& x0, double& y0, double& x1, double& y1, GWindow& name, double& length); // Drawing first triangle
void drawing( double x1, double y1, double y2, GWindow& name, double length, int row); // This is the main function where we use recusion
void drawLines(double x1, double y1, double& y2, GWindow& name, double length); // Drawing 3 line in triangle

int main() {
	double length = getInteger("Enter length: "); 
	int row = getInteger("Enter the row: ");
	GWindow name(800, 600);
	double x0, y0, x1, y1, y2 = 0; //Variables
	coordinates(x0, y0, length, name);
	drawFirstTriangle(x0, y0, x1, y1, name, length);
	drawing(x1, y1, y2, name, length, row);
    return 0;
}

void coordinates(double& x0, double& y0, double length, GWindow& name){
	x0 = double(name.getWidth()/2); // X coordinate of the peak of the triangle
	double height = sqrt(3.0)/2 * length;
	y0 = double(name.getHeight())/2 - double(2)/3 * height; // Y coordinate of the peak of the triangle
}


// To draw fractals i use the way: i choose the middle point on the bottom of the triangle. With this point i can draw 3 polarLines easily in the triangle  
void drawFirstTriangle(double& x0, double& y0, double& x1, double& y1, GWindow& name, double& length){
	GPoint point1 = name.drawPolarLine(x0, y0, length, 240); // Drawing left line of the triangle
	double x2 = point1.getX(); double y2 = point1.getY(); // X2 and Y2 are the coordinates of the left peak of the triangle
	GPoint point2 = name.drawPolarLine(x0, y0, length, 300); // Drawing right line of the triangle
	double x3 = point2.getX(); double y3 = point2.getY(); // X3 and Y3 are the coordinates of the right peak of the triangle
	name.drawPolarLine(x2, y2, length, 360); // Drawing bottom side of the triangle
	x1 = double(x2 + x3)/2; y1 = y2; // X1 and Y1 are the coordinate of the point on the bottom of the triangle
}

void drawing(double x1, double y1, double y2, GWindow& name, double length, int row){ // This is the main recursion function
	if(row != 0){ 
		drawLines(x1, y1, y2, name, double(length)/2); // Drawing three lines

		// In the next Lines we use recursive functions for the new 3 triangle that we get by drawing 3 line in triangle
		drawing(x1 - double(length)/4, y1, y2, name, double(length)/2, row - 1);
		drawing(x1 + double(length)/4, y1, y2, name, double(length)/2, row - 1);
		drawing(x1, y2, y2, name, double(length)/2, row - 1);
	}
}

void drawLines(double x1, double y1, double &y2, GWindow& name, double length){ 
	// I used reference on y2 to remember the y coordinate that is on the base base of the turned over triangle, because we need it for the next steps

	GPoint point0 = name.drawPolarLine(x1, y1, length, 120); // Drawing left side of the turned over triangle
	double x2 = point0.getX(); y2 = point0.getY(); // Remembering the coordinates of the point on the base of the turned over triangle
	name.drawPolarLine(x1, y1, length, 60); // Drawing right side of the turned over triangle
	name.drawPolarLine(x2, y2, length, 360); // Drawing the base of the turned over triangle. 
}
