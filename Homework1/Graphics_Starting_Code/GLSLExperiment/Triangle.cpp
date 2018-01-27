#include "Triangle.h"

void Triangle::GenerateGeometry()
{
	this->left = -1.0;
	this->right = 1.0;
	this->bottom = -1.0;
	this->top = 1.0;

	if (this->points.size() <= 0)
	{
		this->points = vector<point2>(3);

		this->points[0] = point2(-0.5, -0.5);
		this->points[1] = point2(0.0, 0.5);
		this->points[2] = point2(0.5, -0.5);
	}
}


void Triangle::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	glDrawArrays(GL_LINE_LOOP, 0, points.size());    // draw the points
	glFlush();
}