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
#define radian2degree(a) (a * 57.295779513082)
#define degree2radian(a) (a * 0.017453292519)

using namespace std;

#endif // !__ANGEL__

/* Generic interface for Image Data */
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