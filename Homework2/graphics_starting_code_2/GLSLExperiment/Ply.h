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
	Ply::Ply(string filename)
	{
		this->filename = filename;
		this->builder = new PlyBuilder();
		this->vertices = new vector<Vertex*>();
		this->faces = new vector<Face*>();
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
	vector<Vertex*>* getVertices()
	{
		vector<Vertex*>* vs = this->vertices;
		return vs;
	}

	/*
	* Gets all loaded Faces
	*/
	vector<Face*>* getFaces()
	{
		vector<Face*>* vs = this->faces;
		return vs;
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
		
		// This breaks rotation why!?
		float highestValue = abs(this->boundingBox.Left);

		if (highestValue < abs(this->boundingBox.Right)) highestValue = abs(this->boundingBox.Right);
		if (highestValue < abs(this->boundingBox.Near)) highestValue = abs(this->boundingBox.Near);
		if (highestValue < abs(this->boundingBox.Far)) highestValue = abs(this->boundingBox.Far);


		// this->projView = Ortho(highestValue * -1, highestValue, this->boundingBox.Bottom, this->boundingBox.Top, 10 * (highestValue * -1), 10 * highestValue);
		return Angel::Perspective((GLfloat)60.0, (GLfloat)this->width / (GLfloat)this->height, (GLfloat)0.1, (GLfloat) 1000.0);
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
	* Vertex list to reference from 
	*/
	vector<Vertex*>* vertices;

	/*
	* face that contain vertices; to draw look up in vertex list
	*/
	vector<Face*>* faces;

	/*
	* ply filename
	*/
	string filename;

	/*
	* Builds polygon from file
	*/
	PlyBuilder* builder;

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
