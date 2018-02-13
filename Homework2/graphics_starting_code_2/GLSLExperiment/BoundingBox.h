#pragma once

#ifndef __BOUNDINGBOX__
#define __BOUNDINGBOX__
#include "Vertex.h"

class BoundingBox
{
	public:
		BoundingBox() {}

		~BoundingBox() {};

		void PopulateBox(vector<Vertex> vertices)
		{
			float centerX, centerY, centerZ = 0;

			this->Right = INT_MIN;
			this->Top = INT_MIN;
			this->Far = INT_MIN;

			this->Left = INT_MAX;
			this->Bottom = INT_MAX;
			this->Near = INT_MAX;

			for (int index = 0; index < vertices.size(); ++index)
			{
				point4 vertex = vertices[index].GetPosition();

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

		mat4 CreateInitiatlPosition()
		{
			float distance = 2 * (abs(this->Near) + abs(this->Far));

			return Angel::Translate(this->Center.x, this->Center.y, this->Center.z) * Angel::Translate(0,0, distance * -1) * Angel::Translate(this->Center.x * -1, this->Center.y * -1, this->Center.z * -1);
		}

		point4 Center = point4(0, 0, 0, 1);
		float Left = -1.0;
		float Bottom = -1.0;
		float Near = -1.0;

		float Right = 1.0;
		float Top = 1.0;
		float Far = 1.0;
};


#endif