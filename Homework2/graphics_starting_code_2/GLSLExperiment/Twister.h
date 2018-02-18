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
	vector<Vertex*> TwistMesh(Ply *currentPly, mat4 currentModel);

	/*
	* Increment the angle of twist
	*/
	void IncrementTwist()
	{
		if (this->baseTheta < MAXTWISTANGLE)
		{
			this->baseTheta = this->baseTheta + TWISTINCREMENT;
		}
	}

	/*
	* Decrement the angle of twist
	*/
	void DecrementTwist()
	{
		if (this->baseTheta > MINTWISTANGLE)
		{
			this->baseTheta = this->baseTheta - TWISTINCREMENT;
		}
	}

	/*
	* Resets the twist angle
	*/
	void ResetTwist()
	{
		this->baseTheta = MINTWISTANGLE;
	}

private:
	/*
	* base theta to increment rotation by
	*/
	int baseTheta = MINTWISTANGLE;

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
	Vertex* createTwistedVertex(point4 vertex, point4 center, int interval);
};

