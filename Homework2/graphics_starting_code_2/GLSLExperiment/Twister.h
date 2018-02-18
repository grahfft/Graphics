#pragma once
#include "Vertex.h"
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
	vector<Vertex> TwistMesh(Ply *currentPly);

	/*
	* Increment the angle of twist
	*/
	void IncrementTwist()
	{
		if (this->baseTheta < 90)
		{
			this->baseTheta = this->baseTheta + 10;
		}
	}

	/*
	* Decrement the angle of twist
	*/
	void DecrementTwist()
	{
		if (this->baseTheta > 0)
		{
			this->baseTheta = this->baseTheta - 10;
		}
	}

	/*
	* Resets the twist angle
	*/
	void ResetTwist()
	{
		this->baseTheta = 0;
	}

private:
	/*
	* base theta to increment rotation by
	*/
	int baseTheta = 0;

	/*
	* The number of intervals for distance
	*/
	int numberOfIntervals = 4;

	/*
	* Gets the max distance for a vertex
	*/
	float getMaxDistanceFromCenter(BoundingBox box);

	/*
	* Determines the distance of v from the center
	*/
	float distanceFromCenter(point4 v, point4 center);

	/*
	* determines the rotation for the vertex
	*/
	int determineRotationAngle(float distance, float maxDistance);

	/*
	* Rotates the point and creates a new vertex
	*/
	Vertex createTwistedVertex(point4 vertex, int interval);
};

