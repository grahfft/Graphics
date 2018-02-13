#include "Ply.h"

bool Ply::LoadGeometry()
{
	if (!this->builder.isLoaded())
	{
		this->builder.LoadPlyFile(this->filename);
		this->boundingBox.PopulateBox(this->builder.getVertices());
	}

	this->vertices = this->builder.getVertices();
	this->faces = this->builder.getFaces();
	this->transformations = vector<mat4>();

	return this->builder.isLoaded();
}

void Ply::UpdateColor(bool toggle)
{
	for (int index = 0; index < this->vertices.size(); index++)
	{
		color4 currentColor = RED;
		if (toggle)
		{
			currentColor = this->colorRandomizer.GetRandomColor();
		}

		this->vertices[index].SetColor(currentColor);
	}
}

void Ply::AddXaxisTranslation(bool positive, bool negative)
{
	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(TRANSLATEINCREMENT, 0.0, 0.0));
	if (negative) this->transformations.push_back(Angel::Translate(TRANSLATEINCREMENT * -1, 0.0, 0.0));
}

void Ply::AddYaxisTranslation(bool positive, bool negative)
{
	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(0.0, TRANSLATEINCREMENT, 0.0));
	if (negative) this->transformations.push_back(Angel::Translate(0.0, TRANSLATEINCREMENT * -1, 0.0));
}

void Ply::AddZaxisTranslation(bool positive, bool negative)
{
	if (positive && negative) return;
	if (positive) this->transformations.push_back(Angel::Translate(0.0, 0.0, TRANSLATEINCREMENT));
	if (negative) this->transformations.push_back(Angel::Translate(0.0, 0.0, TRANSLATEINCREMENT * -1));
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
	mat4 modelMatrix = Angel::identity() * this->boundingBox.CreateInitiatlPosition() * this->CreateShear();
	vector<mat4> currentTransforms = this->transformations;

	for (int index = currentTransforms.size() - 1; 0 <= index; --index)
	{
		modelMatrix = modelMatrix * currentTransforms[index];
	}

	// modelMatrix = this->CreateShear() * modelMatrix;

	return modelMatrix;
}

mat4 Ply::CreateShear()
{
	mat4 shear;
	float converted = ConvertDegreesToRadians(this->shearInDegrees);

	float cosX = cos(converted);
	float sinX = sin(converted);

	shear[0][1] = cosX / sinX;

	return shear;
}