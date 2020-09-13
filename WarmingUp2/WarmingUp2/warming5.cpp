#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
#define SIZE 50

class Grid
{
private:
    bool m_grid[SIZE][SIZE];
    int m_presentPosX = 0;
    int m_presentPosY = 0;
public:
    Grid()
    {
        Initialize();
    }

    void Initialize()
    {
        for (int c = 0; c < SIZE; ++c)
        {
            for (int r = 0; r < SIZE; ++r)
            {
                m_grid[r][c] = false;
            }
        }
        m_presentPosX = 0;
        m_presentPosY = 0;
    }

    void Show()
    {
        for (int r = 0; r < SIZE; ++r)
        {
            cout << " " ;
            for (int c = 0; c < SIZE; ++c)
            {
                if (m_grid[r][c] == false)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }

    bool Movable(int unit, int direction)
    {
        switch (direction)
        {
        case 0: // 상
            if (m_presentPosY - unit >= 0)
                return true;
            else
                return false;
            break;
        case 1: // 하
            if (m_presentPosY + unit < SIZE)
                return true;
            else
                return false;
            break;
        case 2: // 좌
            if (m_presentPosX - unit >= 0)
                return true;
            else
                return false;
            break;
        case 3: // 우
            if (m_presentPosX + unit < SIZE)
                return true;
            else
                return false;
            break;
        }

    }

    void Move(int unit, int direction)
    {
        switch (direction)
        {
            case 0: // 상
            {
                int modifier = 0;
                for (int i = 0; i < unit; ++i)
                {
                    modifier++;
                    m_grid[m_presentPosY - modifier][m_presentPosX] = 1;
                }
                m_presentPosY -= unit;
            }
            break;
        case 1: // 하
            {
                int modifier = 0;
                for (int i = 0; i < unit; ++i)
                {
                    modifier++;
                    m_grid[m_presentPosY + modifier][m_presentPosX] = 1;
                }
                m_presentPosY += unit;
            }
            break;
        case 2: // 좌
            {
                int modifier = 0;
                for (int i = 0; i < unit; ++i)
                {
                    modifier++;
                    m_grid[m_presentPosY][m_presentPosX - modifier] = 1;
                }
                m_presentPosX -= unit;
            }
            break;
        case 3: // 우
            {
                int modifier = 0;
                for (int i = 0; i < unit; ++i)
                {
                    modifier++;
                    m_grid[m_presentPosY][m_presentPosX + modifier] = 1;
                }
                m_presentPosX += unit;
            }
            break;
        }
    }

};


int main()
{
    // 시드값을 얻기 위한 random_device 생성.
    random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    mt19937 gen(rd());

    // 랜덤한 사이즈 지정
    uniform_int_distribution<int> distanceSize(54, 80);

    // 방향 설정 
    uniform_int_distribution<int> randDirection(0, 3);

    Grid grid;

    int beforeDirection = 0;

    while (true)
    {
        grid.Initialize();

        int rightMoveDistance = distanceSize(gen);
        int leftMoveDistance = rightMoveDistance - 49;
        int downMoveDistance = distanceSize(gen);
        int topMoveDistance = downMoveDistance - 49;

        while (rightMoveDistance + leftMoveDistance + downMoveDistance + topMoveDistance != 0)
        {
            int direction = beforeDirection;

            while(direction == beforeDirection )
                direction = randDirection(gen);

            beforeDirection = direction;

            int unit = 0;

            cout << direction << endl;

            switch (direction)
            {
            case 0: // 상
                if (topMoveDistance >= 5)
                {
                    uniform_int_distribution<int> randUnit(0, 5);
                    unit = randUnit(gen);
                }
                else
                {
                    uniform_int_distribution<int> randUnit(0, topMoveDistance);
                    unit = randUnit(gen);
                }
                break;
            case 1: // 하
                if (downMoveDistance >= 5)
                {
                    uniform_int_distribution<int> randUnit(0, 5);
                    unit = randUnit(gen);
                }
                else
                {
                    uniform_int_distribution<int> randUnit(0, downMoveDistance);
                    unit = randUnit(gen);
                }
                break;
            case 2: // 좌
                if (leftMoveDistance >= 5)
                {
                    uniform_int_distribution<int> randUnit(0, 5);
                    unit = randUnit(gen);
                }
                else
                {
                    uniform_int_distribution<int> randUnit(0, leftMoveDistance);
                    unit = randUnit(gen);
                }
                break;
            case 3: // 우
                if (rightMoveDistance >= 5)
                {
                    uniform_int_distribution<int> randUnit(0, 5);
                    unit = randUnit(gen);
                }
                else
                {
                    uniform_int_distribution<int> randUnit(0, rightMoveDistance);
                    unit = randUnit(gen);
                }
                break;
            }

            if (grid.Movable(unit, direction))
            {
                switch (direction)
                {
                case 0: // 상
                    topMoveDistance -= unit;
                    break;
                case 1: // 하
                    downMoveDistance -= unit;
                    break;
                case 2: // 좌
                    leftMoveDistance -= unit;
                    break;
                case 3: // 우
                    rightMoveDistance -= unit;
                    break;
                }

                grid.Move(unit, direction);
            }
        }

        grid.Show();

        cout << " q를 제외한 모든 입력 - 경로를 다시 만든다. q - 프로그램을 종료한다" << endl;

        char c;
        while (true)
        {
            c = getchar();
            if (c != '\n')
                break;
        }
        if (islower(c) != 0)
            c = toupper(c);


        switch (c)
        {
        case 'Q':
            return 0;
            break;
        default:
            break;
        }

    }
}