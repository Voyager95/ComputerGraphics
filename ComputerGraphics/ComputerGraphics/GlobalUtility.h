#pragma once
#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <stdio.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#define PI 3.14

#pragma region Struct

struct Transform
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform()
	{
		position.x = 0;
		position.y = 0;
		position.z = 0;

		rotation.x = 0;
		rotation.y = 0;
		rotation.z = 0;

		scale.x = 0;
		scale.y = 0;
		scale.z = 0;
	}

};

#pragma endregion


static void ReadObj(FILE* objFile)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}
	//--- 2. 메모리 할당
	glm::vec4* vertex;
	glm::vec4* face;
	int vertIndex = 0;
	int faceIndex = 0;
	vertex = (glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	face = (glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	char* bind;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&vertex[vertIndex].x, &vertex[vertIndex].y,
				&vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&face[faceIndex].x, &face[faceIndex].y, &face[faceIndex].z);
			faceIndex++;
		}
	}
}

static float getRadian(float angle)
{
	return angle * (PI / 180);
}

struct Vec2
{
public:
	GLfloat x, y;

	Vec2()
	{
		x = 0;
		y = 0;
	}
};

struct Colorf
{
public:
	GLclampf r, g, b, a;

	Colorf()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}

	Colorf(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

