#pragma once

#ifndef __PLY__
#define __PLY__

#include "Face.h"
#include "BoundingBox.h"
#include "PlyBuilder.h"

/*
* Contains topology and geometry of the polygon given by the filename
*/
class Ply
{
public:
	/*
	* Constructors
	*/
	Ply() {};
	Ply::Ply(GLuint program, string filename)
	{
		this->program = program;
		this->filename = filename;
		this->vertices = vector<Vertex>();
		this->faces = vector<Face>();
	}

	/*
	* Destructor
	*/
	~Ply() {};

	/*
	* This method Loads the geomtry from the given ply file
	*/
	bool LoadGeometry();

	/*
	* Main Program can update the color of the mesh per assignment requirements
	*/
	void UpdateColor(bool toggle);

	/*
	* Updates the current glut window width and height; sets the viewport
	*/
	void UpdateWindow(int width, int height)
	{
		this->width = width;
		this->height = height;
		glViewport(0, 0, this->width, this->height);
	}

	/*
	* Gets all loaded Vertices
	*/
	vector<Vertex> getVertices()
	{
		return this->vertices;
	}

	/*
	* Gets all loaded Faces
	*/
	vector<Face> getFaces()
	{
		return this->faces;
	}

	/*
	* Gets filename
	*/
	string getFilename()
	{
		return this->filename;
	}

	/*
	* Calculates the model matrix in a post-multiply manner
	*/
	mat4 getModelMatrix();

	/*
	* Gets the current projection view
	*/
	mat4 getProjectionMatrix()
	{
		return this->projView;
	}

	/*
	* Gets the polygon's bounding box
	*/
	BoundingBox getBoundingBox() { return this->boundingBox; }

private:
	/*
	* Current Window width
	*/
	int width = STARTWIDTH;

	/*
	* Current window height
	*/
	int height = STARTHEIGHT;

	/*
	* Current Projection View
	*/
	mat4 projView = Angel::Perspective((GLfloat)45.0, (GLfloat)this->width / (GLfloat)this->height, (GLfloat)0.1, (GLfloat) 100.0);

	/*
	* Vertex list to reference from 
	*/
	vector<Vertex> vertices;

	/*
	* face that contain vertices; to draw look up in vertex list
	*/
	vector<Face> faces;

	/*
	* program to send shader variables
	*/
	GLuint program;

	/*
	* ply filename
	*/
	string filename;

	/*
	* Builds polygon from file
	*/
	PlyBuilder builder;

	/*
	* Generates random colors for vertices
	*/
	ColorRandomizer colorRandomizer;

	/*
	* Image bounding box
	*/
	BoundingBox boundingBox;
};

#endif
