#include "ModelInstnce.h"
#include "stdafx.h"
ModelInstance::ModelInstance()
{
	//--- 초기 플레그 설정
	isBufferGen = false;

	//--- 버퍼 생성
	GenerateBuffer();
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

	//--- 2개의 VBO를 지정하고 할당하기
	glGenBuffers(1, &vbo_Pos);
	glGenBuffers(1, &vbo_Color);

	//--- 2개의 EBO를 지정하고 할당하기
	glGenBuffers(1, &evo_Pos);
	glGenBuffers(1, &evo_Color);

}

void ModelInstance::DeleteBuffer()
{
	//--- vao, vbo, evo를 해제합니다.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_Pos);
	glDeleteBuffers(1, &vbo_Color);
	glDeleteBuffers(1, &evo_Pos);
	glDeleteBuffers(1, &evo_Color);

	//--- 플레그 변경
}

void ModelInstance::UpdateBuffer()
{
	//--- VAO를 바인드하기
	glBindVertexArray(vao);

	//--- vbo_Pos를 활성화하여 버텍스 데이터를 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Pos);

	if (verticesPos->size() > 0)							//변수 triShape 에서 버텍스 데이터 값을 버퍼에 복사한다.
	{
		glBufferData(GL_ARRAY_BUFFER, verticesPos->size() * sizeof(glm::vec4), &verticesPos.get()->begin(), GL_STATIC_DRAW);
	}

	//--- ebo_Pos를 활성화 하여 삼각형 정보를 바인드한다.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo_Pos);		// GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tries->size() * sizeof(glm::ivec3), &tries.get()->begin(), GL_STATIC_DRAW);

	//--- vertex 속성 포인터를 전달
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	// 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glEnableVertexAttribArray(0);							// attribute 인덱스 0번을 사용가능하게 함

	//--- vbo_Color를 활성화하여 버텍스 컬러를 바인드하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Color);

	if (vecticesColor->size() > 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecticesColor->size() * sizeof(GLfloat) * 3, &vecticesColor.get()->begin(), GL_STATIC_DRAW);
	}

	//--- ebo_Pos를 활성화 하여 삼각형 정보를 바인드한다.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo_Color);		// GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tries->size() * sizeof(glm::ivec3), &tries.get()->begin(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 4*float
	glEnableVertexAttribArray(1);							// attribute 인덱스 1번을 사용 가능하게 함.
}
