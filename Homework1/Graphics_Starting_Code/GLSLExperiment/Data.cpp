#include "Data.h"

/* Generates shader variables; Generic as all images needed the same shader set up */
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

/* Generic Resize method for maintaining aspect ratio */
void Data::ResizeImage(int newWidth, int newHeight) {
	width = newWidth;
	height = newHeight;

	float ratio = (this->right - this->left) / (this->top - this->bottom);
	float windowRatio = width / height;

	if (ratio > windowRatio)
	{
		glViewport(0, 0, width, width / ratio);
	}
	else if (ratio < windowRatio)
	{
		glViewport(0, 0, height * ratio, height);
	}
	else
	{
		glViewport(0, 0, width, height);
	}
}



