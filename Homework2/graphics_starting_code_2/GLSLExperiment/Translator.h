#pragma once

#include "Ply.h"

/*
* Responsible for the transformations applied to mesh
*/
class Translator
{
public:
	/*
	* Constructor
	*/
	Translator() 
	{
		this->transformations = vector<mat4>();
		this->TurnOff();
	};

	/*
	* Destructor
	*/
	~Translator() {};

	/*
	* Toggles Translation in the Positive X direction
	*/
	void TogglePosX() { this->positiveX = !this->positiveX; };

	/*
	* Toggles Translation in the Negative X direction
	*/
	void ToggleNegX() { this->negativeX = !this->negativeX; };

	/*
	* Toggles Translation in the Positive Y direction
	*/
	void TogglePosY() { this->positiveY = !this->positiveY; };

	/*
	* Toggles Translation in the Negative Y direction
	*/
	void ToggleNegY() { this->negativeY = !this->negativeY; };

	/*
	* Toggles Translation in the Positive Z direction
	*/
	void TogglePosZ() { this->positiveZ = !this->positiveZ; };

	/*
	* Toggles Translation in the Negative Z direction
	*/
	void ToggleNegZ() { this->negativeZ = !this->negativeZ; };

	/*
	* Turns off all translations
	*/
	void TurnOff()
	{
		this->positiveX = false;
		this->negativeX = false;

		this->positiveY = false;
		this->negativeY = false;

		this->positiveZ = false;
		this->negativeZ = false;
	}

	/*
	* Clears out translations
	*/
	void ResetTranslations()
	{
		this->transformations = vector<mat4>();
	}

	/*
	* Adds translations in the appropriate directions
	*/
	void AddTranslations(bool preventTranslation)
	{
		if (preventTranslation) return;

		this->AddXaxisTranslation();
		this->AddYaxisTranslation();
		this->AddZaxisTranslation();
	}

	/*
	* Calculates and returns the current Translation Matrix
	*/
	mat4 getTranslationMatrix()
	{
		mat4 modelMatrix = Angel::identity();
		vector<mat4> currentTransforms = this->transformations;

		for (int index = currentTransforms.size() - 1; 0 <= index; --index)
		{
			modelMatrix = modelMatrix * currentTransforms[index];
		}

		return modelMatrix;
	}

private:
	/*
	* List of all transformations
	*/
	vector<mat4> transformations;

	/*
	* Toggles X translations
	*/
	bool positiveX = false;
	bool negativeX = false;

	/*
	* Toggles Y translations
	*/
	bool positiveY = false;
	bool negativeY = false;

	/*
	* Toggles Z translations
	*/
	bool positiveZ = false;
	bool negativeZ = false;

	/*
	* Adds a translation in the X direction
	*/
	void AddXaxisTranslation();

	/*
	* Adds a translation in the Y direction
	*/
	void AddYaxisTranslation();

	/*
	* Adds a translation in the Z direction
	*/
	void AddZaxisTranslation();
};

