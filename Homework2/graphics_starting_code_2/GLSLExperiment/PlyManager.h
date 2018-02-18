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
	PlyManager()
	{
		this->polygons = vector<Ply*>();
		this->plyLock = new mutex();
		this->current = new Ply();
	};

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

	Ply* current;

	/*
	* List of all displayable polygons
	*/
	vector<Ply*> polygons;

	vector<string> files;

	mutex* plyLock;

	/*
	* Creates and builds each polygon; if the file loads successfully added to polygon list
	*/
	void createPly(string filename);

	/*
	* Returns current index
	*/
	int getIndex() { return this->currentPly % this->files.size(); }

	Ply* PlyManager::swapCurrent();

	/*
	* Prevents loading all polygons while developing
	*/
	bool devMode = false;
};

#endif

