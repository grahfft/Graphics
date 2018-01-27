#pragma once

#ifndef __DATA__
#define __DATA__

#include "Data.h"

#endif // !__DATA__

class Triangle :
	public Data
{
public:
	Triangle(GLuint program) { this->program = program; };
	virtual ~Triangle() {};

	void GenerateGeometry();
	void DrawImage();
};

