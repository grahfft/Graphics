#pragma once
#ifndef __DATA__
#define __DATA__

#include "Data.h"

#endif // !__DATA__

class Sierpinski :
	public Data
{
public:
	Sierpinski(GLuint program) { this->program = program; };
	~Sierpinski() {};

	void GenerateGeometry();
	void DrawImage();
};

