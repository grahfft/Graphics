#pragma once
#ifndef __DATA__
#define __DATA__

#include "Data.h"

#endif // !__DATA__

/*
Interface for loading a homegrown dat file
*/
class DatFile :
	public Data
{
public:
	DatFile(GLuint program, string filename) 
	{
		this->program = program; 
		this->filename = filename; 
	};

	~DatFile() {};

	void GenerateGeometry();
	void DrawImage();

	vector<int> pointsPerLine;
	string filename;
};

