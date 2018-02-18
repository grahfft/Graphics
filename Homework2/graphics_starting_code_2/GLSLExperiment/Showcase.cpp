#include "Showcase.h"

mat4 Showcase::Display(Ply *currentPolygon, mat4 currentModel)
{
	// For opposite turning angles
	int angle = this->theta;
	mat4 display = Angel::identity();
	BoundingBox box = currentPolygon->getBoundingBox();
	
	if (this->clockwise) angle = angle * -1;

	string filename = currentPolygon->getFilename();
	if (!filename.compare("ant.ply") && !this->printed)
	{
		this->printed = true;
		cout << "File " << filename << " is going clockwise: " << this->clockwise << endl;
	}

	point4 newCenter = currentPolygon->getModelMatrix() * currentModel * box.Center;
	display = Angel::Translate(newCenter.x, newCenter.y, newCenter.z) * Angel::RotateY(angle) * Angel::Translate(newCenter.x * -1, newCenter.y * -1, newCenter.z * -1); // Y in degrees

	return display;
}

bool Showcase::UpdateShowcase()
{
	if (!this->grandShowcase) return this->grandShowcase;

	this->theta = this->theta + ROTATIONINCREMENT;

	if (this->theta > ROTATIONLIMIT)
	{
		this->printed = false;
		this->clockwise = !this->clockwise;
		this->theta = STARTROTATIONANGLE;
		return true;
	}

	return false;
}