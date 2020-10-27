#pragma once
#include <memory>
#include <array>
#include <vector>
#include <gl/glm/glm.hpp>
#include <gl/glew.h>

/// <summary>
/// 모델정보를 가지고 있는 인스턴스입니다.
/// VAO, BEO를 가지고 있습니다.
/// </summary>
class ModelInstance
{
public:
    //--- Obj 데이터
    std::unique_ptr<std::vector<glm::vec4>> verticesPos;
    std::unique_ptr<std::vector<glm::vec4>> vecticesColor;
    std::unique_ptr<std::vector<glm::ivec3>> tries;

    //--- Buffer 참조 변수
    GLuint vao;
    GLuint vbo_Pos;
    GLuint vbo_Color;    // 00: vertexPosition 01: vertexColor
    GLuint evo_Pos;
    GLuint evo_Color;    // 00: vertexPosition 01: vertexColor

    //--- 플레그
    bool isBufferGen;   // 버퍼가 생성되었는지 판단합니다.

public:
    ModelInstance();
    ~ModelInstance();

    /// <summary>
    /// 버퍼를 생성합니다.
    /// </summary>
    void GenerateBuffer();

    /// <summary>
    /// 버퍼를 삭제합니다.
    /// </summary>
    void DeleteBuffer();

    /// <summary>
    /// 버퍼를 최신화합니다.
    /// </summary>
    void UpdateBuffer();
};

