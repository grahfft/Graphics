#pragma once

#ifndef __SHOWCASE__
#define __SHOWCASE__

#include "Ply.h"

/*
* This class maintains the state of the R keyboard showcase
* The class is designed to return a matrix to add to the CTM when needed
*/
class Showcase
{
public:
	/*
	* Constructor
	*/
	Showcase() 
	{
		this->currentTransformations = vector<mat4>();
	};

	/*
	* Deconstructor
	*/
	~Showcase() {};

	/*
	* Toggles the showcase on or off
	*/
	void ToggleShowcase()
	{
		this->grandShowcase = !this->grandShowcase;
		if (this->grandShowcase)
		{
			this->currentTransformations = vector<mat4>();
		}
	}

	/*
	* Checks whether the showcase is on
	*/
	bool ShowcaseOn() 
	{
		bool current = this->grandShowcase;
		return current;
	}

	/*
	* Checks whether the showcase is running
	* If running, provides a rotated matrix
	* Otherwise returns the identity matrix
	*/
	mat4 Display(Ply *currentPolygon);

	/*
	* Updates the showcase rotation and signals if the current polygon needs updating
	*/
	bool UpdateShowcase();
	
private:
	/*
	* Bool to determine if the showcase is on or off
	*/
	bool grandShowcase;

	/*
	* Determines whether to rotate the image clockwise or counterclockwise
	*/
	bool clockwise = false;

	/*
	* Stores the current tranformations for passing to subsequent polygons
	*/
	vector<mat4> currentTransformations;

	/*
	* Angle to rotate the image
	*/
	int theta = 0;
};

#endif