#include "Triangle.h"

/* Generates the triangles geometry */
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

/* Draws a 6 x 6 tiling of triangles */
void Triangle::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	float w, h;
	w = this->width / 6;
	h = this->height / 6;
	for (int k = 0; k<6; k++) {
		for (int m = 0; m<6; m++) {
			glViewport(k * w, m * h, w, h);
			glDrawArrays(GL_LINE_LOOP, 0, this->points.size());
		}
	}
	glFlush();
}