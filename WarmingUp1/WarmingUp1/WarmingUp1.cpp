// WarmingUp1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#define LENG_M3 3
#define LENG_M4 4
using namespace std;

class Matrix
{
private:
    int m_Size;
public:
    int** value;

    Matrix(int size)
    {
        this->m_Size = size;
        value = new int*[size];
        for (int i = 0; i < size; ++i)
        {
            value[i] = new int[size];
        }

        InitializeValue();
    }

    ~Matrix()
    {
        for (int i = 0; i < m_Size; ++i)
        {
            delete[] value[i];
        }

        delete[] value;
    }

    int GetSize()
    {
        return m_Size;
    }

    void InitializeValue()
    {
        srand((unsigned int)time(NULL));

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                if (r == c)
                    value[r][c] = 1;
                else
                    value[r][c] = 0;
            }
        }
    }

    void ChangeRandomValue()
    {
        srand((unsigned int)time(NULL));

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                int randValue = rand();

                //cout << randValue << endl;

                value[r][c]= randValue % 2;
            }
        }
    }

    void Show()
    {
        for (int c = 0; c < m_Size; ++c)
        {
            cout << '|';
            for (int r = 0; r < m_Size; ++r)
            {
                cout << value[r][c];
            }
            cout << '|' << endl;
        }
    }

    void Copy(Matrix target)
    {
        int targetSize = target.GetSize();

        if (targetSize > m_Size)
            targetSize = m_Size;

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                value[r][c] = target.value[r][c];
            }
        }
    }

    Matrix operator*(Matrix m)
    {
        Matrix result = Matrix(m.GetSize());

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                int result = 0;
                for (int i = 0; i < m_Size; ++i)
                {
                    result += value[r][i] * m.value[i][c];
                }

                value[r][c] = result;
            }
        }
    }
};

int main()
{
    Matrix A = Matrix(3);
    Matrix B = Matrix(3);
    while(true)
    {
        system("cls");
        // 안내
        cout << "A = " << endl;
        A.Show();
        cout << "B = " << endl;
        B.Show();
        cout << " - m: 행렬의 곱셈 \n - a : 행렬의 덧셈 \n - d : 행렬의 뺄셈 \n - r : 행렬식의 값(Determinant) \n - t : 전치 행렬(Transposed matrix)과 그 행렬식의 값" <<
        "\n - h : 3X3 행렬을 4X4 행렬로 변환하고 행렬식의 값(4행4열 행렬식 값) 출력  \n - s : 행렬의 값을 새로 랜덤하게 설정한다. \n - q : 프로그램 종료" << endl;
        
        fflush(stdin);
        char code = getchar();
        
        switch (code)
        {
        case 'm':
            break;
        case 'a':
            break;
        case 'd':
            break;
        case 'r':
            break;
        case 't':
            break;
        case 'h':
            break;
        case 's':
            break;
        case 'q':
            exit(1);
            break;
        default:
            cout << "명령어를 다시 입력해주세요" << endl;
            break;
        }
        fflush(stdin);
        getchar();
    }


}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
