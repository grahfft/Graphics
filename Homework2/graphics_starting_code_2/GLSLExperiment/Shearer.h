#pragma once
#include "HelperHeader.h"

/*
* Class responsible for shearing the mesh
*/
class Shearer
{
public:
	/*
	* Constructor
	*/
	Shearer() {};

	/*
	* Deconstructor
	*/
	~Shearer() {};

	/*
	* Creates the shear transformation
	*/
	mat4 CreateShear()
	{
		mat4 shear;
		float converted = ConvertDegreesToRadians(this->shearInDegrees);

		float cosX = cos(converted);
		float sinX = sin(converted);

		shear[0][1] = cosX / sinX;

		return shear;
	}

	/*
	* Increases the shear by decrementing the angle; prevents a cot(0) which is undefined
	*/
	void IncreaseShear()
	{
		this->shearInDegrees = this->shearInDegrees <= 1 ? 1 : shearInDegrees - SHEARINCREMENT;
	};

	/*
	* Decreases the shear by incrementing the angle; prevents a cot(180) which is undefined
	*/
	void DecreaseShear()
	{
		this->shearInDegrees = this->shearInDegrees >= 179 ? 179 : shearInDegrees + SHEARINCREMENT;
	};

	/*
	* Resets the shear angle
	*/
	void ResetShear() { this->shearInDegrees = STARTSHEARANGLE; }

private:
	int shearInDegrees = STARTSHEARANGLE;
};

