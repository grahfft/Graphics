#include "Ply.h"

bool Ply::LoadGeometry()
{
	if (!this->builder.isLoaded())
	{
		this->builder.LoadPlyFile(this->filename);
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

void Ply::AddModelTransformation(mat4 transformation)
{
	this->transformations.push_back(transformation);
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

*/
mat4 Ply::getModelMatrix()
{
	mat4 modelMatrix = Angel::identity();
	vector<mat4> currentTransforms = this->transformations;

	for (int index = currentTransforms.size() - 1; 0 <= index; --index)
	{
		modelMatrix = modelMatrix * currentTransforms[index];
	}

	return modelMatrix;
}
