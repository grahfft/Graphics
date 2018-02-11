#pragma once

#ifndef __BUILDER__
#define __BUILDER__

#include "Face.h"

/*
* Class responsible for parsing ply files and storing polygon geometry
*/
class PlyBuilder
{
public:
	/*
	* Constructor
	*/
	PlyBuilder() { this->resetValues(); };

	/*
	* Destructor
	*/
	~PlyBuilder() {};

	/*
	* Contains the logic for loading a ply file and parses the file if a valid file
	*/
	bool LoadPlyFile(string filename);

	/*
	* Check to see if the builder successfully loaded the polygon
	*/
	bool isLoaded() { return this->loaded; }

	/*
	* Can be used to reset the geometry and color of the file
	*/
	void ReloadFile(string filename)
	{
		this->loaded = false;
		if (!this->LoadPlyFile(filename)) cout << "Failed to reload file" << endl;
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

private:

	/*
	* Current Loaded state
	*/
	bool loaded = false;

	/*
	* Expected number of Vertices; used for validation
	*/
	int totalVertices;

	/*
	* Expected number of Faces; used for validation
	*/
	int totalFaces;

	/*
	* Vertex list to reference from
	*/
	vector<Vertex> vertices;

	/*
	* face that contain vertices; to draw look up in vertex list
	*/
	vector<Face> faces;

	/*
	* Directs to the parse paths for each token size
	*/
	void parseTokens(vector<string> tokens);

	/*
	* Parses out the coordinates of each vertex; Also catches for skip lines per assignment; sets total number of vertices and faces for verification
	*/
	void parseCoordinates(vector<string> tokens);

	/*
	* Parses a face from the given file; ignores tokens[0] per the assignment
	*/
	void parseFace(vector<string> tokens);
	
	/*
	* Validate file is a ply file
	*/
	bool validateFile(vector<string> tokens, string fileLocation);

	/*
	* Verify all vertices loaded correctly; prints out vertices if fails
	*/
	bool verifyVertices();

	/*
	* Verify all faces loaded correctly; prints out faces if fails
	*/
	bool verifyFaces();

	/*
	* Reset all information for builder
	*/
	void resetValues()
	{
		this->loaded = false;
		this->totalVertices = 0;
		this->totalFaces = 0;
		this->vertices = vector<Vertex>(); //Vertex list to reference from
		this->faces = vector<Face>(); // face that contain vertices; to draw look up in vertex list
	};
};

#endif