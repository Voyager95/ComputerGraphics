#pragma once
#include <memory>
#include <array>
#include <vector>
#include <gl/glm/glm.hpp>
#include <gl/glew.h>

/// <summary>
/// �������� ������ �ִ� �ν��Ͻ��Դϴ�.
/// VAO, BEO�� ������ �ֽ��ϴ�.
/// </summary>
class ModelInstance
{
public:
    //--- Obj ������
    std::vector<glm::vec3> verticesPos;        // ���ؽ� ��ġ
    std::vector<glm::vec3> verticesColor;      // ���ؽ� �÷�
    std::vector<glm::vec3> verticesNormal;     // ���ؽ� ���
    std::vector<glm::vec3> verticesUV;         // ���ؽ� UV

    std::vector<glm::ivec3> triesPos;          // �ﰢ�� ��ġ �ε���
    std::vector<glm::ivec3> triesColor;        // �ﰢ�� ���� �ε���
    std::vector<glm::ivec3> triesNormal;       // �ﰢ�� ��� �ε���
    std::vector<glm::ivec3> triesUV;           // �ﰢ�� UV �ε���

    //--- Buffer ���� ����
    GLuint vao, ebo;
    GLuint vbo_Pos;
    GLuint vbo_Color;    // 00: vertexPosition 01: vertexColor

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
};

