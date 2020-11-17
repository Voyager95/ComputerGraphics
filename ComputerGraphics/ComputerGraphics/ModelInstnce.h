#pragma once
#include "stdafx.h"

/// <summary>
/// 모델정보를 가지고 있는 인스턴스입니다.
/// VAO, BEO를 가지고 있습니다.
/// </summary>
class ModelInstance
{
public:


public:
    //--- Obj 데이터
    std::vector<glm::vec3> verticesPos;        // 버텍스 위치
    std::vector<glm::vec3> verticesColor;      // 버텍스 컬러
    std::vector<glm::vec3> verticesNormal;     // 버텍스 노멀
    std::vector<glm::vec2> verticesUV;         // 버텍스 UV

    std::vector<glm::ivec3> triesIndex;          // 삼각형 위치 인덱스

    //--- Buffer 참조 변수
    GLuint vao, ebo;
    GLuint vbo_Pos;
    GLuint vbo_Color;
    GLuint vbo_Normal;
    GLuint vbo_UV;

    //--- 설정
    GLuint usage;
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

    /// <summary>
    /// 각 버텍스에 렌덤한 색상을 부여합니다.
    /// </summary>
    void RandomColor();
};

