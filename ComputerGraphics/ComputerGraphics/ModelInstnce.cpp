#include "ModelInstnce.h"
#include "stdafx.h"
ModelInstance::ModelInstance()
{
	//--- �ʱ� �÷��� ����
	isBufferGen = false;

	//--- ���� ����
	GenerateBuffer();
}

ModelInstance::~ModelInstance()
{
	//--- ���� ����
	DeleteBuffer();
}

void ModelInstance::GenerateBuffer()
{
	//--- VAO �� �����ϰ� �Ҵ��ϱ�
	glGenVertexArrays(1, &vao);

	//--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(1, &vbo_Pos);
	glGenBuffers(1, &vbo_Color);

	//--- 2���� EBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(1, &evo_Pos);
	glGenBuffers(1, &evo_Color);

}

void ModelInstance::DeleteBuffer()
{
	//--- vao, vbo, evo�� �����մϴ�.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_Pos);
	glDeleteBuffers(1, &vbo_Color);
	glDeleteBuffers(1, &evo_Pos);
	glDeleteBuffers(1, &evo_Color);

	//--- �÷��� ����
}

void ModelInstance::UpdateBuffer()
{
	//--- VAO�� ���ε��ϱ�
	glBindVertexArray(vao);

	//--- vbo_Pos�� Ȱ��ȭ�Ͽ� ���ؽ� �����͸� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Pos);

	if (verticesPos->size() > 0)							//���� triShape ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	{
		glBufferData(GL_ARRAY_BUFFER, verticesPos->size() * sizeof(glm::vec4), &verticesPos.get()->begin(), GL_STATIC_DRAW);
	}

	//--- ebo_Pos�� Ȱ��ȭ �Ͽ� �ﰢ�� ������ ���ε��Ѵ�.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo_Pos);		// GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tries->size() * sizeof(glm::ivec3), &tries.get()->begin(), GL_STATIC_DRAW);

	//--- vertex �Ӽ� �����͸� ����
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	// ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glEnableVertexAttribArray(0);							// attribute �ε��� 0���� ��밡���ϰ� ��

	//--- vbo_Color�� Ȱ��ȭ�Ͽ� ���ؽ� �÷��� ���ε��ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_Color);

	if (vecticesColor->size() > 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecticesColor->size() * sizeof(GLfloat) * 3, &vecticesColor.get()->begin(), GL_STATIC_DRAW);
	}

	//--- ebo_Pos�� Ȱ��ȭ �Ͽ� �ﰢ�� ������ ���ε��Ѵ�.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo_Color);		// GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tries->size() * sizeof(glm::ivec3), &tries.get()->begin(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);	// ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 4*float
	glEnableVertexAttribArray(1);							// attribute �ε��� 1���� ��� �����ϰ� ��.
}
