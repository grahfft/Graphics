#pragma once

#ifndef __SHOWCASE__
#define __SHOWCASE__

#include "Ply.h"

class Showcase
{
public:
	Showcase() 
	{
		this->currentTransformations = vector<mat4>();
	};


	~Showcase() {};

	void ToggleShowcase()
	{
		this->grandShowcase = !this->grandShowcase;
		if (this->grandShowcase)
		{
			this->currentTransformations = vector<mat4>();
		}
	}

	bool ShowcaseOn() 
	{
		bool current = this->grandShowcase;
		return current;
	}

	/*
	* THIS FUCKING WORKS NEED TO ADD IN INCREMENT AND DECREMENT TO IDLE FUNCTION
	*/
	mat4 Display(Ply currentPolygon)
	{
		bool showcase = this->grandShowcase;
		mat4 display = Angel::identity();
		BoundingBox box = currentPolygon.getBoundingBox();

		if (showcase)
		{
			if (this->currentTransformations.size() == 0)
			{
				this->currentTransformations = currentPolygon.getTransformations();
			}
			else
			{
				currentPolygon.setTransformations(this->currentTransformations);
			}

			mat4 currentModel = currentPolygon.getModelMatrix();

			point4 newCenter = currentModel * box.Center;
			mat4 rotate = Angel::Translate(newCenter.x, newCenter.y, newCenter.z) * Angel::RotateY(this->theta) * Angel::Translate(newCenter.x * -1, newCenter.y * -1, newCenter.z * -1); // Y in degrees

			display = display * rotate * currentModel;
		}
		else
		{
			display = display * currentPolygon.getModelMatrix();
		}

		return display;
	}

private:
	bool grandShowcase;

	bool clockwise;

	vector<mat4> currentTransformations;

	int theta = 0;
};

#endif