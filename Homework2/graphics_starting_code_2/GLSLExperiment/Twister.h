#pragma once

#include "Ply.h"

/*
* Class responsible for twisting a mesh
*/
class Twister
{
public:
	/*
	* Constructor
	*/
	Twister() {};

	/*
	* Destructor
	*/
	~Twister() {};

	/*
	* 
	*/
	vector<point4> TwistPolygon(Ply *currentPly);
};

