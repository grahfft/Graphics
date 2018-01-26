#include "Data.h"
#include <vector>

using namespace std;

void Data::GenerateGeometry() 
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
};

void Data::SetupShader()
{
	mat4 ortho = Ortho2D(this->left, this->right, this->bottom, this->top);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void Data::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	glDrawArrays(GL_LINE_LOOP, 0, points.size());    // draw the points
	glFlush();
}

