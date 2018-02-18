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
	Showcase() {};

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
	mat4 Display(Ply *currentPolygon, mat4 currentModel);

	/*
	* Updates the showcase rotation and signals if the current polygon needs updating
	*/
	bool UpdateShowcase();

	/*
	* Clears the showcase's state data
	*/
	void ResetShowcase()
	{
		this->grandShowcase = false;
		this->theta = STARTROTATIONANGLE;
	}
	
private:
	/*
	* Bool to determine if the showcase is on or off
	*/
	bool grandShowcase = false;

	/*
	* Determines whether to rotate the image clockwise or counterclockwise
	*/
	bool clockwise = false;

	/*
	* Angle to rotate the image
	*/
	int theta = STARTROTATIONANGLE;

	bool printed = false;
};

#endif