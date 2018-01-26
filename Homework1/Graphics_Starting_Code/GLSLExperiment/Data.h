#pragma once

#ifndef __ANGEL__
#define __ANGEL__

#include "Angel.h"
#include <vector>
typedef vec2 point2;

using namespace std;

#endif // !__ANGEL__

class Data
{
public:
	Data() {};

	Data(GLuint program) 
	{
		this->program = program;
	};
	
	virtual ~Data() {
	};

	void virtual GenerateGeometry() {};
	void virtual SetupShader() {};
	void virtual DrawImage() {};

	float right, left, bottom, top;
	vector<point2> points;
	GLuint program;
};