#include "Showcase.h"

mat4 Showcase::Display(Ply *currentPolygon, mat4 currentModel)
{
	bool showcase = this->grandShowcase;
	if (!showcase) return this->currentImageRotation;

	mat4 display = this->currentImageRotation;
	BoundingBox box = currentPolygon->getBoundingBox();

	point4 newCenter = currentPolygon->getModelMatrix() * currentModel * box.Center;
	display = Angel::Translate(newCenter.x, newCenter.y, newCenter.z) * Angel::RotateY(this->theta) * Angel::Translate(newCenter.x * -1, newCenter.y * -1, newCenter.z * -1); // Y in degrees
	this->currentImageRotation = display;

	return display;
}

bool Showcase::UpdateShowcase()
{
	if (this->clockwise)
	{
		--this->theta;

		if (this->theta == 0)
		{
			this->clockwise = false;
			return true;
		}
	}
	else
	{
		++this->theta;

		if (this->theta == 360) {
			this->clockwise = true;
			return true;
		}
	}

	return false;
}