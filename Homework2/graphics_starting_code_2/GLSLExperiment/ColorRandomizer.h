#pragma once

#ifndef __VERTEXCOLORS__
#define __VERTEXCOLORS__

#include "HelperHeader.h"

#define BLACK	color4(0.0, 0.0, 0.0, 1.0)
#define RED		color4(1.0, 0.0, 0.0, 1.0)
#define YELLOW	color4(1.0, 1.0, 0.0, 1.0)
#define GREEN	color4(0.0, 1.0, 0.0, 1.0)
#define BLUE	color4(0.0, 0.0, 1.0, 1.0)
#define MAGENTA	color4(1.0, 0.0, 1.0, 1.0)
#define WHITE	color4(1.0, 1.0, 1.0, 1.0)
#define CYAN	color4(0.0, 1.0, 1.0, 1.0)

class ColorRandomizer
{
public:
	/*
	* Constructor
	*/
	ColorRandomizer() { this->populateVertexColors(); };

	/*
	* Deconstructor
	*/
	~ColorRandomizer() {};

	/*
	* Generates a random color
	*/
	color4 GetRandomColor()
	{
		int colorIndex = rand() % this->vertexColors.size();
		return vertexColors[colorIndex];
	}

private:

	/*
	* Contains all possible colors the vertex can be
	*/
	vector<color4> vertexColors;

	/*
	* Populates the vertex vector with start colors
	*/
	void populateVertexColors()
	{
		this->vertexColors = vector<color4>();
		this->vertexColors.push_back(BLACK);
		this->vertexColors.push_back(RED);
		this->vertexColors.push_back(YELLOW);
		this->vertexColors.push_back(GREEN);
		this->vertexColors.push_back(BLUE);
		this->vertexColors.push_back(MAGENTA);
		this->vertexColors.push_back(WHITE);
		this->vertexColors.push_back(CYAN);
	}
};

#endif
