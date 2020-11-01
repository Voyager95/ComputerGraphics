#include "ModelInstnce.h"
#include "stdafx.h"
ModelInstance::ModelInstance()
{	
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
	glBindVertexArray(vao);

	//--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(1, &vbo_Pos);
	glGenBuffers(1, &vbo_Color);

	//--- EBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(1, &ebo);

	//--- �÷��� ����
	m_IsBufferGen = true;
}

void ModelInstance::DeleteBuffer()
{
	//--- vao, vbo, evo�� �����մϴ�.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_Pos);
	glDeleteBuffers(1, &vbo_Color);
	glDeleteBuffers(1, &ebo);

	//--- �÷��� ����
	m_IsBufferGen = false;
}

void ModelInstance::UpdateBuffer()
{
	//--- VAO�� ���ε��ϱ�
	glBindVertexArray(vao);

	//--- vbo_Pos�� Ȱ��ȭ�Ͽ� ���ؽ� �����͸� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Pos);

	if (verticesPos.size() > 0)							//���� triShape ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	{
		glBufferData(GL_ARRAY_BUFFER, verticesPos.size() * sizeof(glm::vec3), &verticesPos[0], GL_STATIC_DRAW);
	}

	//--- vertex �Ӽ� �����͸� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);	// ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glEnableVertexAttribArray(0);							// attribute �ε��� 0���� ��밡���ϰ� ��


	//--- vbo_Color�� Ȱ��ȭ�Ͽ� ���ؽ� �÷��� ���ε��ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo_Color);

	if (verticesColor.size() > 0)
	{
		glBufferData(GL_ARRAY_BUFFER, verticesColor.size() * sizeof(GLfloat) * 3, &verticesColor[0], GL_STATIC_DRAW);
	}

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);	// ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 4*float
	glEnableVertexAttribArray(1);

	//--- ebo_Pos�� Ȱ��ȭ �Ͽ� �ﰢ�� ������ ���ε��Ѵ�.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);		// GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triesPos.size() * sizeof(glm::ivec3), &triesPos[0], GL_STATIC_DRAW);
}
