#pragma once

#ifndef __DATA__
#define __DATA__

#include "Data.h"

#endif // !__DATA__

/* Interfaced for generating a triangle */
class Triangle :
	public Data
{
public:
	Triangle(GLuint program) { this->program = program; };
	virtual ~Triangle() {};

	void GenerateGeometry();
	void DrawImage();
};

