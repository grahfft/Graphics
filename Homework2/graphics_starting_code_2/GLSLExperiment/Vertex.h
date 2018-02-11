#pragma once

#ifndef __VERTEX__
#define __VERTEX__

#include "ColorRandomizer.h"

/*
* Boxes around all vertex information
*/
class Vertex
{
public:
	/*
	* Constructors
	*/
	Vertex() {};
	Vertex(point4 position)
	{
		this->position = position;
		this->color = RED;
	}

	/*
	* Deconstructor
	*/
	~Vertex() {};

	/*
	* Gets the position of the vertex in 3D space (homogonized for ease)
	*/
	point4 GetPosition() { return this->position; }

	/*
	* Sets the position of the vertex
	*/
	void SetPosition(point4 position) { this->position = position; }

	/*
	* Sets the color attribute of the vertex
	*/
	void SetColor(color4 color)
	{
		this->color = color;
	}

	/*
	* Gets the color attribute of the vertex
	*/
	color4 GetColor() { return this->color; }

private:
	/* 
	* position of vertex
	*/
	point4 position;

	/*
	* color of vertex
	*/
	color4 color;
};

#endif