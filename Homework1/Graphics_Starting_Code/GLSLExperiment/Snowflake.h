#pragma once

#ifndef __DATA__
#define __DATA__

#include "Data.h"

#endif // !__DATA__

/* Interface for drawing the Koch Snowflake */
class Snowflake :
	public Data
{
public:
	Snowflake(GLuint program) { this->program = program; };
	~Snowflake() {};

	void GenerateGeometry();
	void DrawImage();
	void SetIteration(int iteration) { this->iteration = iteration; };

	int iteration;
private:
	void DrawKoch(point2 v1, point2 v2, int iteration, float direction);
	float CalculateDistance(point2 v1, point2 v2);
	point2 CreatePointFromStartpoint(point2 vertex, float length, float direction);
	float GetAngle(point2 start, point2 target);
};

