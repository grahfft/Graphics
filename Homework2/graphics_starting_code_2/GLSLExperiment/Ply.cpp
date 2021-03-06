#include "Ply.h"

bool Ply::LoadGeometry()
{
	if (this->builder->isLoaded()) return true;

	bool success = this->builder->LoadPlyFile(this->filename);
	
	if (success)
	{
		this->vertices = this->builder->getVertices();
		this->faces = this->builder->getFaces();

		this->boundingBox.PopulateBox(this->vertices);
	}

	return success;
}

void Ply::UpdateColor(bool toggle)
{
	for (unsigned int index = 0; index < this->vertices[0].size(); index++)
	{
		color4 currentColor = RED;
		if (toggle)
		{
			currentColor = this->colorRandomizer.GetRandomColor();
		}

		this->vertices[0][index]->SetColor(currentColor);
	}
}

/* modelMat = modelMat * Angel::Translate(0.0, 0.0, -2.0f) * Angel::RotateY(45.0f) * Angel::RotateX(35.0f); // Remember to post multiply

These produce the same result

pre-multiply -> queue FIFO
modelMat = Angel::RotateX(35.0f) * modelMat;
modelMat = Angel::RotateY(45.0f) * modelMat;
modelMat = Angel::Translate(0.0, 0.0, -2.0f) * modelMat;

post-multiply -> stack LIFO
modelMat = modelMat * Angel::Translate(0.0, 0.0, -2.0f) ;
modelMat = modelMat * Angel::RotateY(45.0f);
modelMat = modelMat * Angel::RotateX(35.0f);

currentPolygon.AddModelTransformation(Angel::RotateX(35.0f));
currentPolygon.AddModelTransformation(Angel::RotateY(45.0f));
currentPolygon.AddModelTransformation(Angel::Translate(0.0, 0.0, -2.0f));

*/
mat4 Ply::getModelMatrix()
{
	//return Angel::identity() * this->boundingBox.CreateInitiatlPosition();
	
	float highestValue = abs(this->boundingBox.Left);

	if (highestValue < abs(this->boundingBox.Right)) highestValue = abs(this->boundingBox.Right);
	if (highestValue < abs(this->boundingBox.Near)) highestValue = abs(this->boundingBox.Near);
	if (highestValue < abs(this->boundingBox.Far)) highestValue = abs(this->boundingBox.Far);


	return this->boundingBox.CreateInitiatlPosition(); //* Ortho(highestValue * -1, highestValue, this->boundingBox.Bottom, this->boundingBox.Top, 10 * (highestValue * -1), 10 * highestValue);
}