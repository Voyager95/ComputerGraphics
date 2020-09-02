// WarmingUp1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <math.h>
using namespace std;

class SquareMatrix
{
private:
    int m_Size;

    int GetDeterminant(SquareMatrix& s)
    {
        int result = 0;

        if (s.GetSize() > 2)
        {
            for (int i = 0; i < s.GetSize(); ++i)
            {
                SquareMatrix* excepted = s.RowColumnExceptedMatrix(0, i);
                result += s.value[0][i] * GetDeterminant( *excepted ) * (int)pow(-1, i);

                delete excepted;
            }
        }
        else if(s.GetSize() == 2)
        {
            result = s.value[0][0] * s.value[1][1] - s.value[0][1] * s.value[1][0];
        }
        else
        {
            cout << "행렬 크기에 문제가 있습니다" << endl;
        }

        return result;
    }

public:
    int** value;

    SquareMatrix(int size)
    {
        this->m_Size = size;
        value = new int*[size];
        for (int i = 0; i < size; ++i)
        {
            value[i] = new int[size];
        }

        InitializeValue();
    }

    ~SquareMatrix()
    {
        for (int i = 0; i < m_Size; ++i)
        {
            delete[] value[i];
        }

        delete[] value;
    }

    int GetSize() const
    {
        return m_Size;
    }

    void InitializeValue()
    {
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

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                int randValue = rand();

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

    void Copy(const SquareMatrix& target)
    {
        int targetSize = target.GetSize();

        if (targetSize > m_Size)
            targetSize = m_Size;

        for (int r = 0; r < targetSize; ++r)
        {
            for (int c = 0; c < targetSize; ++c)
            {
                value[r][c] = target.value[r][c];
            }
        }
    }

    SquareMatrix* RowColumnExceptedMatrix(int rowToExcept, int columnToExcept)
    {
        int size = GetSize() - 1;
        SquareMatrix* result = new SquareMatrix(size);

        if (size < 2)
        {
            cout << "사이즈가 너무 작습니다" << endl;
            return result;
        }


        for (int r = 0; r < m_Size; ++r)
        {
            if (rowToExcept != r)
            {
                for (int c = 0; c < m_Size; ++c)
                {
                    if (columnToExcept != c)
                    {
                        int rowCorrectionValue = 0;
                        int columnCorrectionValue = 0;

                        if (r > rowToExcept)
                            rowCorrectionValue -= 1;

                        if (c > columnToExcept)
                            columnCorrectionValue -= 1;

                        result->value[r + rowCorrectionValue][c + columnCorrectionValue] = value[r][c];
                    }
                }
            }
        }

        return result;
    }

    int GetDeterminant()
    {
        return GetDeterminant(*this);
    }

    SquareMatrix* GetTransposedMatrix()
    {
        SquareMatrix* result = new SquareMatrix(GetSize());

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                result->value[r][c] = value[c][r];
            }
        }

        return result;
    }


    SquareMatrix* operator*(const SquareMatrix& m)
    {
        SquareMatrix* result = new SquareMatrix(m.GetSize());

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                int element = 0;
                for (int i = 0; i < m_Size; ++i)
                {
                    element += value[r][i] * m.value[i][c];
                }

                result->value[r][c] = element;
            }
        }

        return result;
    }

    SquareMatrix* operator+(const SquareMatrix& m)
    {
        SquareMatrix* result = new SquareMatrix(m.GetSize());

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                result->value[r][c] = value[r][c] + m.value[r][c];
            }
        }

        return result;
    }

    SquareMatrix* operator-(const SquareMatrix& m)
    {
        SquareMatrix* result = new SquareMatrix(m.GetSize());

        for (int r = 0; r < m_Size; ++r)
        {
            for (int c = 0; c < m_Size; ++c)
            {
                result->value[r][c] = value[r][c] - m.value[r][c];
            }
        }

        return result;
    }

};

int main()
{
    srand((unsigned int)time(NULL));

    SquareMatrix* A = new SquareMatrix(3);
    A->ChangeRandomValue();
    SquareMatrix* B = new SquareMatrix(3);
    B->ChangeRandomValue();

    while(true)
    {
        system("cls");
        // 안내
        cout << "A = " << endl;
        A->Show();
        cout << "B = " << endl;
        B->Show();
        cout << " - m : 행렬의 곱셈 \n - a : 행렬의 덧셈 \n - d : 행렬의 뺄셈 \n - r : 행렬식의 값(Determinant) \n - t : 전치 행렬(Transposed matrix)과 그 행렬식의 값" <<
        "\n - h : 3X3 행렬을 4X4 행렬로 변환하고 행렬식의 값(4행4열 행렬식 값) 출력  \n - s : 행렬의 값을 새로 랜덤하게 설정한다. \n - q : 프로그램 종료" << endl;

        char code = getchar(); getchar();
        
        switch (code)
        {
        case 'm':
        {
            SquareMatrix* m = (*A * *B);
            m->Show();

            delete m;
        }
        break;
        case 'a':
        {
            SquareMatrix* a = (*A + *B);
            a->Show();

            delete a;
        }
        break;
        case 'd':
        {
            SquareMatrix* d = (*A - *B);
            d->Show();

            delete d;
        }
        break;
        case 'r':
            cout << "Det(A) = " << A->GetDeterminant() << endl;
            cout << "Det(B) = " << A->GetDeterminant() << endl;
            break;
        case 't':
        {
            SquareMatrix* t1 = A->GetTransposedMatrix();
            SquareMatrix* t2 = B->GetTransposedMatrix();
            cout << "T(A) = " << endl;
            t1->Show();
            cout << "Det(T(A)) = " << t1->GetDeterminant() << endl;
            cout << "T(B) = " << endl;
            t2->Show();
            cout << "Det(T(B)) = " << t2->GetDeterminant() << endl;
            delete t1, t2;
        }
            break;
        case 'h':
        {
            SquareMatrix* h1 = new SquareMatrix(4);
            SquareMatrix* h2 = new SquareMatrix(4);
            h1->Copy(*A);
            h2->Copy(*B);

            cout << "A의 4X4 = " << endl;
            h1->Show();
            cout << "Det(A의 4X4) = " << h1->GetDeterminant() << endl;

            cout << "B의 4X4 = " << endl;
            h2->Show();
            cout << "Det(B의 4X4) = " << h2->GetDeterminant() << endl;

            delete h1, h2;
        }
        break;
        case 's':
            A->ChangeRandomValue();
            B->ChangeRandomValue();
            cout << "바뀌었습니다" << endl;
            break;
        case 'q':
            exit(1);
            break;
        default:
            cout << "명령어를 다시 입력해주세요" << endl;
            break;
        }

        system("PAUSE");
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
