#include "Showcase.h"

mat4 Showcase::Display(Ply *currentPolygon, mat4 currentModel)
{
	// For opposite turning angles
	int angle = this->theta;
	BoundingBox box = currentPolygon->getBoundingBox();
	string filename = currentPolygon->getFilename();
	
	if (this->clockwise) angle = angle * -1;


	point4 newCenter = currentPolygon->getModelMatrix() * currentModel * box.Center;
	mat4 display = Angel::Translate(newCenter.x, newCenter.y, newCenter.z) * Angel::RotateY(angle) * Angel::Translate(newCenter.x * -1, newCenter.y * -1, newCenter.z * -1); // Y in degrees

	return display;
}

bool Showcase::UpdateShowcase()
{
	if (!this->grandShowcase) return this->grandShowcase;

	if (this->theta >= ROTATIONLIMIT)
	{
		cout << "Rotation limit hit: " << this->theta << endl;

		this->printed = false;
		this->clockwise = !this->clockwise;
		this->theta = STARTROTATIONANGLE;
		return true;
	}

	this->theta = this->theta + ROTATIONINCREMENT;

	return false;
}