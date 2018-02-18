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
#include <limits.h>

#define MAXPOINTS 50000
#define MAXCOLOR 50000

#define STARTWIDTH 512
#define STARTHEIGHT 512

#define STARTROTATIONANGLE 0
#define ROTATIONINCREMENT 1
#define ROTATIONLIMIT	360

#define STARTSHEARANGLE 90
#define TRANSLATEINCREMENT 0.25f
#define SHEARINCREMENT	1

#define MAXTWISTANGLE	90
#define MINTWISTANGLE	0
#define TWISTINCREMENT	1

#define ConvertDegreesToRadians(degrees) (degrees * DegreesToRadians)

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

using namespace std;
#endif