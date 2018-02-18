#pragma once

#ifndef __BOUNDINGBOX__
#define __BOUNDINGBOX__
#include "Vertex.h"

class BoundingBox
{
	public:
		/*
		* Constructor
		*/
		BoundingBox() {}

		/*
		* Deconstructor
		*/
		~BoundingBox() {};

		/*
		* Populates the bounding box from the vertices provided
		*/
		void PopulateBox(vector<Vertex*>* v)
		{
			float centerX, centerY, centerZ = 0;

			this->Right = (float)INT_MIN;
			this->Top = (float)INT_MIN;
			this->Far = (float)INT_MIN;

			this->Left = (float)INT_MAX;
			this->Bottom = (float)INT_MAX;
			this->Near = (float)INT_MAX;

			vector<Vertex*> vertices = *v;

			for (unsigned int index = 0; index < vertices.size(); ++index)
			{
				point4 vertex = vertices[index]->GetPosition();

				// X comparisons
				if (vertex.x < this->Left) this->Left = vertex.x;
				if (vertex.x > this->Right) Right = vertex.x;

				// Y comparisons
				if (vertex.y < this->Bottom) this->Bottom = vertex.y;
				if (vertex.y > this->Top) this->Top = vertex.y;

				// z comparisons
				if (vertex.z< this->Near) this->Near = vertex.z;
				if (vertex.z > this->Far) this->Far = vertex.z;
			}

			centerX = (this->Left + this->Right) / 2;
			centerY = (this->Bottom + this->Top) / 2;
			centerZ = (this->Near + this->Far) / 2;

			this->Center = point4(centerX, centerY, centerZ, 1.0);
		}

		/*
		* Current work around for not understanding perspective
		*/
		mat4 CreateInitiatlPosition()
		{
			float distanceZ = (abs(this->Near) + abs(this->Far));
			float distanceX = (abs(this->Left) + abs(this->Right));
			float distanceY = (abs(this->Top) + abs(this->Bottom)) * -1;

			float distance = distanceX;
			if (distance < distanceY) distance = distanceY;
			if (distance < distanceZ) distance = distanceZ;

			return Angel::Translate(0,0, (distance) * -1) * Angel::Translate(this->Center.x * -1, this->Center.y * -1, this->Center.z * -1);
		}

		/*
		* Information on the bounding box of the polygon
		*/
		point4 Center = point4(0, 0, 0, 1);
		float Left = -1.0;
		float Bottom = -1.0;
		float Near = -1.0;

		float Right = 1.0;
		float Top = 1.0;
		float Far = 1.0;
};


#endif