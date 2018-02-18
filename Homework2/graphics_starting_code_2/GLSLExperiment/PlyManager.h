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
		this->polygons = vector<Ply*>();
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
	Ply* GetCurrentPly();

	/*
	* Gets the next polygon to draw
	*/
	Ply* GetNextPly();

	/*
	* Gets the previous polygon to draw
	*/
	Ply* GetPreviousPly();

private:

	/*
	* location of shader program
	*/
	GLuint program;

	/*
	* current polygon index to display
	*/
	int currentPly = 0;

	/*
	* List of all displayable polygons
	*/
	vector<Ply*> polygons;

	/*
	* Creates and builds each polygon; if the file loads successfully added to polygon list
	*/
	void createPly(string filename);

	/*
	* Prevents loading all polygons while developing
	*/
	bool devMode = true;
};

#endif

