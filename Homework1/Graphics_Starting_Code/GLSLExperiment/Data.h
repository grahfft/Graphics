#pragma once

#ifndef __ANGEL__
#define __ANGEL__

#include "Angel.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

typedef vec2 point2;

#define MAXPOINTS 10000

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
	void SetupShader();
	void virtual DrawImage() {};
	void ResizeImage(int newWidth, int newHeight);

	int width, height;
	float right, left, bottom, top;
	vector<point2> points;
	GLuint program;
};