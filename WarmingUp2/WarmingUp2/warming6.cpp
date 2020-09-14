#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
#define BOARDSIZEX 30
#define BOARDSIZEY 30

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
};

void SizeRectangle(Rectangle& target, Rectangle area, int unit, int direction)
{
    switch (direction)
    {
    case 0: // 상
        if ((target.topRight.y + unit <= area.topRight.y) && (target.topRight.y + unit < BOARDSIZEY))
        {
            target.topRight.y += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 1: // 하
        if (target.downLeft.y + unit < area.topRight.y)
        {
            target.downLeft.y += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 2: // 좌
        if (target.downLeft.x + unit < area.topRight.x)
        {
            target.downLeft.x += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    case 3: // 우
        if ((target.topRight.x + unit <= area.topRight.x) && (target.topRight.x + unit < BOARDSIZEX))
        {
            target.topRight.x += unit;
        }
        else
        {
            cout << "영역을 벗어 납니다" << endl;
        }
        break;
    }
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

void ShowGrid(Rectangle rect)
{
    for (int r = BOARDSIZEY - 1; r >= 0; --r)
    {

        for (int c = 0; c < BOARDSIZEX; ++c)
        {
            if (rect.downLeft.y <= r && rect.topRight.y > r && rect.downLeft.x <= c && rect.topRight.x > c)
                cout << " 1";
            else
                cout << " .";;

        }

        cout << endl;
    }
}

void GetSize(Rectangle& target)
{
    Position downLeft, topRIght;

    cout << "DownLeft 좌표를 입력해주세요 (스페이스바로 구분합니다)" << endl;
    scanf_s("%d %d", &downLeft.x, &downLeft.y);
    cout << "TopRight 좌표를 입력해주세요 (스페이스바로 구분합니다)" << endl;
    scanf_s("%d %d", &topRIght.x, &topRIght.y);

    target.downLeft = downLeft;
    target.topRight = topRIght;
}

int main()
{
    while (true)
    {
        Rectangle area;
        area.topRight.x = BOARDSIZEX;
        area.topRight.y = BOARDSIZEY;
        Rectangle test;
        GetSize(test);

        bool repeat = true;
        while (repeat == true)
        {
            ShowGrid(test);

            cout << "입력 명령어 : x / X - x축 우측 / 좌측으로 한 칸 이동" << endl;
            cout << "    y / Y - y축 아래쪽 / 위쪽으로 한 칸 이동" << endl;
            cout << "    s / S – x와 y 모두 한 칸 축소 / 확대(범위를 넘어가는 축은 변경 안됨)" << endl;
            cout << "    i / j - x축 한 칸 확대 / 축소" << endl;
            cout << "    k / l - y축 한 칸 확대 / 축소" << endl;
            cout << "    r / q - 모든 것을 리셋하고 다시 좌표값을 입력받는다. / 프로그램을 종료한다." << endl;

            char c;
            while (true)
            {
                c = getchar();
                if (c != '\n')
                    break;
            }
         
            switch (c)
            {
            case 'Y':
                MoveRectangle(test, area, 1, 0);
                break;
            case 'y':
                MoveRectangle(test, area, 1, 1);
                break;
            case 'X':
                MoveRectangle(test, area, 1, 2);
                break;
            case 'x':
                MoveRectangle(test, area, 1, 3);
                break;
            case 's':
                SizeRectangle(test, area, 1, 1);
                SizeRectangle(test, area, 1, 2);
                break;
            case 'S':
                SizeRectangle(test, area, 1, 0);
                SizeRectangle(test, area, 1, 3);
                break;
            case 'k':
                SizeRectangle(test, area, 1, 0);
                break;
            case 'l':
                SizeRectangle(test, area, 1, 1);
                break;
            case 'i':
                SizeRectangle(test, area, 1, 3);
                break;
            case 'j':
                SizeRectangle(test, area, 1, 2);
                break;
            case 'r':
                repeat = false;
                break;
            case 'q':
                return 0;
                break;
            default:
                cout << "올바르지 않은 입력입니다" << "endl";
                break;
            }
        }
    }
}