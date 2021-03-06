#include "stdafx.h"
#include "ModelInstnce.h"

ModelInstance::ModelInstance()
{	
	//--- 버퍼 생성
	GenerateBuffer();

	usage = GL_STATIC_DRAW;
}

ModelInstance::~ModelInstance()
{
	//--- 버퍼 제거
	DeleteBuffer();
}

void ModelInstance::GenerateBuffer()
{
	//--- VAO 를 지정하고 할당하기
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//--- 2개의 VBO를 지정하고 할당하기
	glGenBuffers(1, &vbo_Pos);
	glGenBuffers(1, &vbo_Color);
	glGenBuffers(1, &vbo_UV);
	glGenBuffers(1, &vbo_Normal);

	//--- EBO를 지정하고 할당하기
	glGenBuffers(1, &ebo);

	//--- 플레그 설정
	m_IsBufferGen = true;
}

void ModelInstance::DeleteBuffer()
{
	//--- vao, vbo, evo를 해제합니다.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_Pos);
	glDeleteBuffers(1, &vbo_Color);
	glDeleteBuffers(1, &vbo_Normal);
	glDeleteBuffers(1, &ebo);

	//--- 플레그 변경
	m_IsBufferGen = false;
}

void ModelInstance::UpdateBuffer()
{
	//--- VAO를 바인드하기
	glBindVertexArray(vao);

	//--- vbo_Pos를 활성화하여 버텍스 데이터를 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Pos);

	if (verticesPos.size() > 0)							//변수 triShape 에서 버텍스 데이터 값을 버퍼에 복사한다.
	{
		glBufferData(GL_ARRAY_BUFFER, verticesPos.size() * sizeof(glm::vec3), &verticesPos[0], usage);
	}

	//--- vertex 속성 포인터를 전달
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);	// 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(0);							// attribute 인덱스 0번을 사용가능하게 함


	//--- vbo_Color를 활성화하여 버텍스 컬러를 바인드하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Color);

	if (verticesColor.size() > 0)
	{
		glBufferData(GL_ARRAY_BUFFER, verticesColor.size() * sizeof(glm::vec3), &verticesColor[0], usage);
	}

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 4*float
	glEnableVertexAttribArray(1);

	//--- vbo_Normal를 활성화하여 버텍스노말을 전달
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Normal);

	if (verticesNormal.size() > 0)
	{
		glBufferData(GL_ARRAY_BUFFER, verticesNormal.size() * sizeof(glm::vec3), &verticesNormal[0], usage);
	}

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 4*float
	glEnableVertexAttribArray(2);

	//--- vbo_UV를 활성화하여 텍스쳐좌표를 전달
	glBindBuffer(GL_ARRAY_BUFFER, vbo_UV);

	if (verticesUV.size() > 0)
	{
		glBufferData(GL_ARRAY_BUFFER, verticesUV.size() * sizeof(glm::vec2), &verticesUV[0], usage);
	}

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 4*float
	glEnableVertexAttribArray(3);



	//--- ebo_Pos를 활성화 하여 삼각형 정보를 바인드한다.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);		// GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩

	if (triesIndex.size() > 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triesIndex.size() * sizeof(glm::ivec3), &triesIndex[0], usage);
	}
}

void ModelInstance::RandomColor()
{
	verticesColor.clear();

	for (int i = 0; i < verticesPos.size(); ++i)
	{
		verticesColor.push_back(glm::vec3(colorDis(gen), colorDis(gen), colorDis(gen)));
	}
}

void ModelInstance::SetSize(float size)
{
	for (auto i = verticesPos.begin(); i != verticesPos.end(); ++i)
	{
		(*i) *= size;
	}
}

void ModelInstance::SetColor(glm::vec3 color)
{
	verticesColor.clear();

	for (int i = 0; i < verticesPos.size(); ++i)
	{
		verticesColor.push_back(color);
	}
}
