#pragma once
#include "Angel.h"
#include <vector>
typedef vec2 point2;

using namespace std;

class Data
{
public:
	Data(GLuint program) 
	{
		this->program = program;
	};
	
	virtual ~Data() {
	};

	void GenerateGeometry();
	void SetupShader();
	void DrawImage();

	float right, left, bottom, top;
	vector<point2> points;
	vector<int> pointsPerLine;
private:
	GLuint program;
};

