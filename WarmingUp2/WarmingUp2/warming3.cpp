#include <iostream>
#include <random>
using namespace std;

struct Position
{
public:
    int x, y;

    Position()
    {
        x = 0;
        y = 0;
    }

    void Show()
    {
        cout << "( " << x << ", " << y << " )";
    }
};

struct Rectangle
{
public:
    Position downLeft;
    Position topRight;

    Rectangle()
    {

    }

    void Show()
    {
        downLeft.Show();
        topRight.Show();
    }

    bool CollisionCheck(Rectangle s)
    {
        bool yCollision = false;
        if (downLeft.y <= s.topRight.y && topRight.y >= s.downLeft.y)
            yCollision = true;

        bool xCollision = false;
        if (downLeft.x <= s.topRight.x && topRight.x >= s.downLeft.x)
            xCollision = true;

        if (yCollision == true && xCollision == true)
            return true;
        else
            return false;
    }
    
};

void RectangleRandomPosition(Rectangle& target,Rectangle area, int minSize, int maxSize)
{
    // 시드값을 얻기 위한 random_device 생성.
    random_device rd;

    // random_device 를 통해 난수 생성 엔진을 초기화 한다.
    mt19937 gen(rd());

    // 랜덤한 사이즈 지정
    uniform_int_distribution<int> disSize(minSize, maxSize);
    
    int sizeX = disSize(gen);
    int sizeY = disSize(gen);

    // 좌표 설정
    Position randomDownLeftPos, randomTopRightPos;

    // 가능한 downLeft의 위치 X좌표 설정하기
    int areaSizeX = (area.topRight.x - area.downLeft.x);
    uniform_int_distribution<int> disPosX(area.downLeft.x, area.downLeft.x + areaSizeX - sizeX);
    randomDownLeftPos.x = disPosX(gen);

    // 가능한 downLeft의 위치 Y좌표 설정하기
    int areaSizeY = (area.topRight.y - area.downLeft.y);
    uniform_int_distribution<int> disPosY(area.downLeft.y, area.downLeft.y + areaSizeY - sizeY);
    randomDownLeftPos.y = disPosY(gen);

    randomTopRightPos.x = randomDownLeftPos.x + sizeX;
    randomTopRightPos.y = randomDownLeftPos.y + sizeY;

    target.downLeft = randomDownLeftPos;
    target.topRight = randomTopRightPos;
}


/// <summary>
/// 사각형을 움직입니다.
/// </summary>
/// <param name="target">움직이고자 하는 사각형</param>
/// <param name="area">제한 범위 입니다</param>
/// <param name="unit">움직임 단위 입니다</param>
/// <param name="direction"> 상:0 하:1 좌:2 우:3 </param>
void MoveRectangle(Rectangle& target, Rectangle area, int unit, int direction)
{
    switch (direction)
    {
    case 0: // 상
        if (target.topRight.y + unit <= area.topRight.y)
        {
            target.topRight.y += unit;
            target.downLeft.y += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 1: // 하
        if (target.downLeft.y - unit >= area.downLeft.y)
        {
            target.topRight.y -= unit;
            target.downLeft.y -= unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 2: // 좌
        if (target.downLeft.x - unit >= area.downLeft.x)
        {
            target.topRight.x -= unit;
            target.downLeft.x -= unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 3: // 우
        if (target.topRight.x + unit <= area.topRight.x)
        {
            target.topRight.x += unit;
            target.downLeft.x += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    }
}

int main()
{
    // 2개의 사각형
    Rectangle a, b;

    // 사각형이 그려질 영역
    Rectangle area;
    area.downLeft.x = 0;
    area.downLeft.y = 0;
    area.topRight.x = 500;
    area.topRight.y = 500;

    // 움직임 단위
    int moveUnit = 10;

    // 사각형의 사이즈 정하기
    int minSizeX = 30;
    int maxSizeY = 80;

    // 랜덤한 위치로 바꾸기
    RectangleRandomPosition(a,area, minSizeX, maxSizeY);
    RectangleRandomPosition(b, area, minSizeX, maxSizeY);

    while (true)
    {
        cout << "Shape 1:";
        a.Show();
        cout << "Shape 2:";
        b.Show();

        cout << "커맨드를 입력하세요 (WSAD)" << endl;
        
        
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
        case 'W':
            cout << "상으로 이동합니다." << endl;
            MoveRectangle(b, area, moveUnit, 0);

            if (b.CollisionCheck(a) == true)
                cout << "충돌합니다" << endl;
            break;
        case 'S':
            cout << "하로 이동합니다." << endl;
            MoveRectangle(b, area, moveUnit, 1);

            if (b.CollisionCheck(a) == true)
                cout << "충돌합니다" << endl;
            break;
        case 'A':
            cout << "좌로 이동합니다." << endl;
            MoveRectangle(b, area, moveUnit, 2);

            if (b.CollisionCheck(a) == true)
                cout << "충돌합니다" << endl;
            break;
        case 'D':
            cout << "우로 이동합니다." << endl;
            MoveRectangle(b, area, moveUnit, 3);

            if (b.CollisionCheck(a) == true)
                cout << "충돌합니다" << endl;
            break;
        default:
            cout << "올바르지 않은 입력입니다" << "endl";
            break;
        }
    }
}