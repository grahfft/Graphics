#pragma once

#ifndef __PLY__
#define __PLY__

#include "Face.h"
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

private:

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
};

#endif
