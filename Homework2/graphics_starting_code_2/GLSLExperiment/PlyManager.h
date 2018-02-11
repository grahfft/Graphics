#pragma once

#ifndef __MANAGER__
#define __MANAGER__

#include "Ply.h"

/*
* Manages the list of polygons to be drawn
*/
class PlyManager
{
public:
	/*
	* Constructors
	*/
	PlyManager(GLuint program)
	{
		this->polygons = vector<Ply>();
	};	
	PlyManager() {};

	/*
	* Destructor
	*/
	~PlyManager() {};

	/*
	* Creates and loads up all polygons
	*/
	void LoadPlyFiles();

	/*
	* Gets the current polygon to draw
	*/
	Ply GetCurrentPly();

	/*
	* Gets the next polygon to draw
	*/
	Ply GetNextPly();

	/*
	* Gets the previous polygon to draw
	*/
	Ply GetPreviousPly();

private:
	GLuint program; // location of shader program
	int currentPly = 0; // current polygon index to display
	vector<Ply> polygons; // List of all displayable polygons

	/*
	* Creates and builds each polygon; if the file loads successfully added to polygon list
	*/
	void createPly(string filename);
};

#endif

