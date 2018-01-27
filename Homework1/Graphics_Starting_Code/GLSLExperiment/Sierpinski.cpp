#include "Sierpinski.h"

void Sierpinski::GenerateGeometry()
{
	this->left = -2.0;
	this->top = 2.0;
	this->right = 2.0;
	this->bottom = -2.0;
	
	this->points = vector<point2>(MAXPOINTS);
	point2 vertices[3];

	vertices[0] = point2(-1.0, -1.0);
	vertices[1] = point2(0.0, 1.0);
	vertices[2] = point2(1.0, -1.0);

	points[0] = point2(.25, .5);

	for (int index = 1; index < this->points.size(); index++)
	{
		int determineVertex = rand() % 3;
		points[index] = (points[index - 1] + vertices[determineVertex]) / 2.0;
	}
}

void Sierpinski::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	glDrawArrays(GL_POINTS, 0, this->points.size());    // draw the points
	glFlush();
}
