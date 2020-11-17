#pragma once
#include "stdafx.h"

/// <summary>
/// �������� ������ �ִ� �ν��Ͻ��Դϴ�.
/// VAO, BEO�� ������ �ֽ��ϴ�.
/// </summary>
class ModelInstance
{
public:


public:
    //--- Obj ������
    std::vector<glm::vec3> verticesPos;        // ���ؽ� ��ġ
    std::vector<glm::vec3> verticesColor;      // ���ؽ� �÷�
    std::vector<glm::vec3> verticesNormal;     // ���ؽ� ���
    std::vector<glm::vec2> verticesUV;         // ���ؽ� UV

    std::vector<glm::ivec3> triesIndex;          // �ﰢ�� ��ġ �ε���

    //--- Buffer ���� ����
    GLuint vao, ebo;
    GLuint vbo_Pos;
    GLuint vbo_Color;
    GLuint vbo_Normal;
    GLuint vbo_UV;

    //--- ����
    GLuint usage;
private:
    //--- �÷���
    bool m_IsBufferGen;   // ���۰� �����Ǿ����� �Ǵ��մϴ�.

public:
    ModelInstance();
    ~ModelInstance();

    /// <summary>
    /// ���۸� �����մϴ�.
    /// </summary>
    void GenerateBuffer();

    /// <summary>
    /// ���۸� �����մϴ�.
    /// </summary>
    void DeleteBuffer();

    /// <summary>
    /// ���۸� �ֽ�ȭ�մϴ�.
    /// </summary>
    void UpdateBuffer();

    /// <summary>
    /// �� ���ؽ��� ������ ������ �ο��մϴ�.
    /// </summary>
    void RandomColor();
};

