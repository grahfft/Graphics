#include "Snowflake.h"
#include <cmath>

// Computes the bearing in degrees from the point A(a1,a2) to
// the point B(b1,b2). Note that A and B are given in terms of
// screen coordinates.
double bearing(double a1, double a2, double b1, double b2) {
	static const double TWOPI = 6.2831853071795865;
	static const double RAD2DEG = 57.2957795130823209;
	// if (a1 = b1 and a2 = b2) throw an error 
	double theta = atan2(b1 - a1, a2 - b2);
	if (theta < 0.0)
		theta += TWOPI;
	return RAD2DEG * theta;
}

void Snowflake::GenerateGeometry()
{
	// Leave empty?
	this->left = -1;
	this->right = 1;
	this->bottom = -1;
	this->top = 1;

	this->points = vector<point2>();
	point2 vertex1 = point2(-0.5, 0.0);
	point2 vertex2 = point2(0.5, 0.0);
	/*point2 vertex3 = point2(0.5, -0.5);*/

	int n = this->iteration;

	this->DrawKoch(vertex1, vertex2, n, degree2radian(0));
	/*this->DrawKoch(vertex2, vertex3, n, degree2radian(bearing(vertex2.x, vertex2.y, vertex3.x, vertex3.y)));
	this->DrawKoch(vertex3, vertex1, n, degree2radian(bearing(vertex3.x, vertex3.y, vertex1.x, vertex1.y)));*/
}

void Snowflake::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window
	this->ResizeImage(this->width, this->height);
	glDrawArrays(GL_LINE_LOOP, 0, this->points.size());    // draw the points
	glFlush();
}

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

float Snowflake::CalculateDistance(point2 v1, point2 v2)
{
	float adjustedX = (v2.x - v1.x) * (v2.x - v1.x);
	float adjustedY = (v2.y - v1.y) * (v2.y - v1.y);

	float distance = sqrt(adjustedX + adjustedY);
	return distance;
}

point2 Snowflake::CreatePointFromStartpoint(point2 vertex, float length, float direction)
{
	float x = vertex.x +  length * cos(direction);
	float y = vertex.y + length * sin(direction);

	point2 *newPoint = new point2(x, y);
	return *newPoint;
}
