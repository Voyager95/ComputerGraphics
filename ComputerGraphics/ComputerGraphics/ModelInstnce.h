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
    std::unique_ptr<std::vector<glm::vec4>> verticesPos;
    std::unique_ptr<std::vector<glm::vec4>> vecticesColor;
    std::unique_ptr<std::vector<glm::ivec3>> tries;

    //--- Buffer ���� ����
    GLuint vao;
    GLuint vbo_Pos;
    GLuint vbo_Color;    // 00: vertexPosition 01: vertexColor
    GLuint evo_Pos;
    GLuint evo_Color;    // 00: vertexPosition 01: vertexColor

    //--- �÷���
    bool isBufferGen;   // ���۰� �����Ǿ����� �Ǵ��մϴ�.

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

