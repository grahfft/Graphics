#include "Ply.h"

bool Ply::LoadGeometry()
{
	if (!this->builder.isLoaded())
	{
		this->builder.LoadPlyFile(this->filename);
	}

	this->vertices = this->builder.getVertices();
	this->faces = this->builder.getFaces();

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
