#pragma once
#include <memory>
#include <list>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <array>
#include <algorithm>
#include <random>
#include <cmath>
#include <random>
#include <queue>
#include <map>
#include <fstream>
#include <sstream>
#include <numeric>
#include <unordered_map>

#include "GlobalUtility.h"


#define LOOPSPEED 16.7
#define DELTATIME 0.016f

enum class WinSize : int
{
	WINSIZE_X = 800,
	WINSIZE_Y = 800
};

enum class ShaderType
{
	VERTEX_ELEMENT,
	TEXTURE_ELEMENT,
	VERTEX_ARRAY,
	TEXTURE_ARRAY,
	LINE
};

//--- ���� �Լ� ����
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> colorDis(0.0f, 1.0f);