#pragma once

#ifndef __FACE__
#define __FACE__

#include "HelperHeader.h"
#include "Vertex.h"

/*
* Data Structure for mapping vertices to triangle
*/
class Face
{
public:
	
	/*
	* Constructors
	*/
	Face() {};
	Face(int v1, int v2, int v3)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	/*
	* Destructor
	*/
	~Face() {};

	/*
	* 3 vertices that make up the face
	*/
	int v1, v2, v3;
};

#endif