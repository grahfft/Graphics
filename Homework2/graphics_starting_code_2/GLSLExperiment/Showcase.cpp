#include "Showcase.h"

mat4 Showcase::Display(Ply *currentPolygon)
{
	bool showcase = this->grandShowcase;
	mat4 display = Angel::identity();

	if (showcase)
	{
		BoundingBox box = currentPolygon->getBoundingBox();

		if (this->currentTransformations.size() == 0)
		{
			this->currentTransformations = currentPolygon->getTransformations();
		}
		else
		{
			currentPolygon->setTransformations(this->currentTransformations);
		}

		mat4 currentModel = currentPolygon->getModelMatrix();

		point4 newCenter = currentModel * box.Center;
		display = Angel::Translate(newCenter.x, newCenter.y, newCenter.z) * Angel::RotateY(this->theta) * Angel::Translate(newCenter.x * -1, newCenter.y * -1, newCenter.z * -1); // Y in degrees
	}

	return display;
}

bool Showcase::UpdateShowcase()
{
	if (this->clockwise)
	{
		--this->theta;
	}
	else
	{
		++this->theta;
	}

	if (this->theta == 360) {
		this->clockwise = true;
		return true;
	}

	if (this->theta == 0)
	{
		this->clockwise = false;
		return true;
	}

	return false;
}