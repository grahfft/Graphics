#include "DatFile.h"
#include <iostream>
#include <iomanip>
#include <fstream>

void DatFile::GenerateGeometry()
{
	if (this->points.size() <= 0)
	{
		ifstream inFile;
		string fileLocation = "..\\HomegrownFiles\\" + filename;

		inFile.open(fileLocation);

		if (!inFile)
		{
			printf("Failed to open File: %s\n", fileLocation);
			return;
		}

		/* TODO: 
			- Load in file
			The structure of GRS files is:

				a number of comment lines, followed by a line starting with at least one asterisk: '*'. - ignore
				The "extent" of the figure: (left, top, right, bottom). - set to left top right bottom
				The number of polylines in the figure. - init pointsPerLine
				The list of polylines: each starts with the number of points in the polyline, followed by the (x, y) pairs for each point. - add first value to pointsPerLine, create point out of subsequent lines
		
		*/
	}
}

void DatFile::SetupShader() 
{
	mat4 ortho = Ortho2D(this->left, this->right, this->bottom, this->top);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void DatFile::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window

	int startPoint = 0;

	for (int index = 0; index < this->pointsPerLine.size(); index++)
	{
		glDrawArrays(GL_LINE_STRIP, startPoint, pointsPerLine[index]);    // draw the points
		startPoint = startPoint + pointsPerLine[index];
	}
	
	glFlush();
}