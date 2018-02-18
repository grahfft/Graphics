#include "Twister.h"

vector<Vertex*> Twister::TwistMesh(Ply *currentPly, mat4 currentModel)
{
	int theta = this->baseTheta;
	vector<Vertex*> points = *currentPly->getVertices();
	if (theta == 0) return points;

	vector<Vertex*> newPoints = vector<Vertex*>(points.size());

	BoundingBox box = currentPly->getBoundingBox();
	float maxDistance = this->getMaxDistanceFromCenter(box);

	for (unsigned int index = 0; index < newPoints.size(); ++index)
	{
		Vertex* v = points[index];
		point4 position = v->GetPosition();

		float distance = this->distanceFromCenter(position, box.Center);
		int interval = this->determineRotationAngle(distance, maxDistance);

		if (position.x < box.Center.x) interval = interval * -1;

		point4 center = currentPly->getModelMatrix() * currentModel * box.Center;

		newPoints[index] = this->createTwistedVertex(position, center, interval);
		newPoints[index]->SetColor(v->GetColor());
	}

	return newPoints;
}

float Twister::getMaxDistanceFromCenter(BoundingBox box)
{
	point4 center = box.Center;
	point4 newPoint = point4(box.Right, box.Top, box.Far, 1.0);

	return this->distanceFromCenter(newPoint, center);
}

float Twister::distanceFromCenter(point4 v, point4 center)
{
	float adjustedX = (v.x - center.x) * (v.x - center.x);
	float adjustedY = (v.y - center.y) * (v.y - center.y);

	float distance = sqrt(adjustedX + adjustedY);
	return distance;
}

int Twister::determineRotationAngle(float distance, float maxDistance)
{
	float distanceInterval = maxDistance / (float)this->numberOfIntervals;
	int interval = 0;

	for (interval; interval < this->numberOfIntervals; ++interval)
	{
		float adjustedDistance = distanceInterval * interval;
		if (distance < adjustedDistance) return interval;
	}

	return interval;
}

Vertex* Twister::createTwistedVertex(point4 vertex, point4 center, int interval)
{
	int theta = this->baseTheta;
	point4 twistedPoint = Angel::Translate(center.x, center.y, center.z) * Angel::RotateX((GLfloat)(interval * theta)) * Angel::Translate( (GLfloat)(center.x * -1), (GLfloat)(center.y * -1), (GLfloat)(center.z * -1)) * vertex; // Angel::RotateX(interval * theta) * vertex;

	return new Vertex(twistedPoint);
}