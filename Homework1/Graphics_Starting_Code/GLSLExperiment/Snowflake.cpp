#include "Snowflake.h"
#include <cmath>

/* Creates world window and starting triangle; Begins the recursive calls for all three sides */
void Snowflake::GenerateGeometry()
{
	// Leave empty?
	this->left = -1;
	this->right = 1;
	this->bottom = -1;
	this->top = 1;

	this->points = vector<point2>();
	point2 vertex1 = point2(-0.5, -0.5);
	point2 vertex2 = point2(0.0, 0.5);
	point2 vertex3 = point2(0.5, -0.5);

	int n = this->iteration;

	this->DrawKoch(vertex1, vertex2, n, degree2radian(this->GetAngle(vertex1, vertex2)));
	this->DrawKoch(vertex2, vertex3, n, degree2radian(this->GetAngle(vertex2, vertex3)));
	this->DrawKoch(vertex3, vertex1, n, degree2radian(this->GetAngle(vertex3, vertex1)));
}

/* Draws a linestrip connecting all points */
void Snowflake::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	this->ResizeImage(this->width, this->height);
	glDrawArrays(GL_LINE_STRIP, 0, this->points.size());    // draw the points
	glFlush();
}

/* Recursive method for drawing snowflake */
void Snowflake::DrawKoch(point2 v1, point2 v2, int iteration, float direction)
{
	if (iteration == 0)
	{
		this->points.push_back(v1);
		this->points.push_back(v2);
	}
	else
	{
		iteration--;
		float distance = this->CalculateDistance(v1, v2);
		float adjustedDistance = distance / 3;

		point2 v3 = this->CreatePointFromStartpoint(v1, adjustedDistance, direction);
		this->DrawKoch(v1, v3, iteration, direction);

		direction = direction + degree2radian(60);
		point2 v4 = this->CreatePointFromStartpoint(v3, adjustedDistance, direction);
		this->DrawKoch(v3, v4, iteration, direction);

		direction = direction - degree2radian(120);
		point2 v5 = this->CreatePointFromStartpoint(v4, adjustedDistance, direction);
		this->DrawKoch(v4, v5, iteration, direction);

		direction = direction + degree2radian(60);
		this->DrawKoch(v5, v2, iteration, direction);
	}
}

/* Distance Calculator */
float Snowflake::CalculateDistance(point2 v1, point2 v2)
{
	float adjustedX = (v2.x - v1.x) * (v2.x - v1.x);
	float adjustedY = (v2.y - v1.y) * (v2.y - v1.y);

	float distance = sqrt(adjustedX + adjustedY);
	return distance;
}

/* Creates the next point given a start, distance and direction(in radians) */
point2 Snowflake::CreatePointFromStartpoint(point2 vertex, float length, float direction)
{
	float x = vertex.x +  length * cos(direction);
	float y = vertex.y + length * sin(direction);

	point2 *newPoint = new point2(x, y);
	return *newPoint;
}

/* Creates an angle in degrees */
float Snowflake::GetAngle(point2 start, point2 target) {
	float angle = radian2degree(atan2(target.y - start.y, target.x - start.x));

	if (angle < 0) {
		angle += 360;
	}

	return angle;
}
