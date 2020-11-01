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
    std::vector<glm::vec3> verticesPos;        // 버텍스 위치
    std::vector<glm::vec3> verticesColor;      // 버텍스 컬러
    std::vector<glm::vec3> verticesNormal;     // 버텍스 노멀
    std::vector<glm::vec3> verticesUV;         // 버텍스 UV

    std::vector<glm::ivec3> triesPos;          // 삼각형 위치 인덱스
    std::vector<glm::ivec3> triesColor;        // 삼각형 색상 인덱스
    std::vector<glm::ivec3> triesNormal;       // 삼각형 노멀 인덱스
    std::vector<glm::ivec3> triesUV;           // 삼각형 UV 인덱스

    //--- Buffer 참조 변수
    GLuint vao, ebo;
    GLuint vbo_Pos;
    GLuint vbo_Color;    // 00: vertexPosition 01: vertexColor

private:
    //--- 플레그
    bool m_IsBufferGen;   // 버퍼가 생성되었는지 판단합니다.

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

