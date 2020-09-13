#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

struct Position
{
public:
	float x, y, z;

	Position()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Position(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Show()
	{
		cout << "( " << x << ", " << y <<  ", " << z << " )";
	}

	float DistanceWithOrigin()
	{
		return sqrt(x * x + y * y + z * z);
	}
};

struct PosList
{
private:
	array<Position*, 10> list;
public:

	PosList()
	{
		for (auto i = list.begin(); i != list.end(); ++i)
		{
			*i = nullptr;
		}
	}

	void InsertBack(float x, float y, float z)
	{
		for (auto i = list.rbegin(); i != list.rend(); ++i)
		{
			if (*i != nullptr)
			{
				if (i == list.rbegin())
				{
					cout << "더이상 삽입할 수 없습니다" << endl;
					return;
				}

				i--;
				*i = new Position(x, y, z);
				cout << "삽입 완료하였습니다." << endl;
				return;
			}
		}

		// 여기 까지 왔다는 것은 리스트에 아무것도 없다는 것이므로 가장 처음에 넣는다.
		list[0] = new Position(x, y, z);
	}

	void DeleteBack()
	{
		for (auto i = list.rbegin(); i != list.rend(); ++i)
		{
			if (*i != nullptr)
			{
				delete(*i);
				*i = nullptr;
				return;
			}
		}
	}

	void DeleteFront()
	{
		for (auto i = list.begin(); i != list.end(); ++i)
		{
			if (*i != nullptr)
			{
				delete(*i);
				*i = nullptr;
				return;
			}
		}
	}

	int GetLength()
	{
		int size = 0;

		for (auto i = list.begin(); i != list.end(); ++i)
		{
			if (*i != nullptr)
				++size;
		}

		return size;
	}


	void InsertFront(float x, float y, float z)
	{
		for (auto i = list.begin(); i != list.end(); ++i)
		{
			if (*i != nullptr)
			{
				if (i == list.begin())
				{
					cout << "더이상 삽입할 수 없습니다" << endl;
					return;
				}

				i--;
				*i = new Position(x, y, z);
				cout << "삽입 완료하였습니다." << endl;
				return;
			}
		}

		// 여기 까지 왔다는 것은 리스트에 아무것도 없다는 것이므로 가장 처음에 넣는다.
		list[0] = new Position(x, y, z);
	}

	void Clear()
	{
		for (auto i = list.begin(); i != list.end(); ++i)
		{
			if (*i != nullptr)
				delete(*i);
			*i = nullptr;
		}
		cout << "비었습니다" << endl;
	}

	void Show()
	{
		for (int i = 0; i < list.size(); ++i)
		{
			cout << i << " : ";
			if (list[i] == nullptr)
			{
				cout << "Empty" << endl;
			}
			else
			{
				list[i]->Show();
				cout << endl;
			}
		}
	}

	void FindFarthestPos()
	{
		if (list.size() > 0)
		{
			auto FarthestDistance = list[0]->DistanceWithOrigin();
			int FarthestIndex = 0;

			for (int i = 0; i < list.size(); ++i)
			{
				if (list[i] != nullptr)
				{
					if (FarthestDistance < list[i]->DistanceWithOrigin())
					{
						FarthestDistance = list[i]->DistanceWithOrigin();
						FarthestIndex = i;
					}
				}
			}

			cout << "가장 먼 점: ";
			list[FarthestIndex]->Show();
		}
		else
		{
			cout << "사이즈가 작아서 찾을 수 없음" << endl;

		}
	}

	void FindClosetPos()
	{
		if (list.size() > 0)
		{
			auto cloestDistance = list[0]->DistanceWithOrigin();
			int cloestIndex = 0;

			for (int i = 0; i < list.size(); ++i)
			{
				if (list[i] != nullptr)
				{
					if (cloestDistance > list[i]->DistanceWithOrigin())
					{
						cloestDistance = list[i]->DistanceWithOrigin();
						cloestIndex = i;
					}
				}
			}

			cout << "가장 먼 점 :";

			list[cloestIndex]->Show();
		}
		else
		{
			cout << "사이즈가 작아서 찾을 수 없음" << endl;
		}
	}

	void Sort()
	{
		sort(list.begin(), list.end(), [](Position* a, Position* b)->bool 
			{
				if( a != nullptr && b != nullptr)
					return a->DistanceWithOrigin() < b->DistanceWithOrigin();
				else if ((a == nullptr && b == nullptr) || ( a == nullptr && b != nullptr))
				{
					return false;
				}
				else
				{
					return true;
				}
			});
		cout << "정렬되었습니다" << endl;
	}

};


int main()
{
	PosList list;

	list.Show();

	while (true)
	{

		cout << "명령어를 입력해 주세요" << endl;

		cout << "  - + x y z : 리스트의 맨 위에 입력(x, y, z: 숫자) " << endl;
		cout << "  - - : 리스트의 맨 위에서 삭제한다." << endl;
		cout << "  - e x y z : 리스트의 맨 아래에 입력(명령어 + 와 반대의 위치, 리스트에 저장된 데이터값이 위로 올라간다.)" << endl;
		cout << "  - d : 리스트의 맨 아래에서 삭제한다. (리스트에서 삭제된 칸이 비어있다.)" << endl;
		cout << "  - l : 리스트의 길이를 출력한다." << endl;
		cout << "  - c : 리스트를 비운다." << endl;
		cout << "  - m : 원점에서 가장 먼 거리에 있는 점의 좌표값을 출력한다." << endl;
		cout << "  - n : 원점에서 가장 가까운 거리에 있는 점의 좌표값을 출력한다." << endl;
		cout << "  - s : 원점과의 거리를 정렬하여 오름차순(또는 내림차순)으로 정렬하여 출력한다.인덱스 0번부터 빈 칸없이 저장하여 출력한다." << endl;
		cout << "  - q : 프로그램을 종료한다." << endl;
		cout << " *좌표값을 입력해야하는 경우 명령어 입력후 각 값을 스페이스로 구분하여 입력해주세요" << endl;

		char c;
		while (true)
		{
			c = getchar();
			if (c != '\n')
				break;
		}

		if (islower(c) != 0)
			c = toupper(c);

		float x, y, z;

		switch (c)
		{
		case '+':
			cout << "좌표값을 스페이스로 구분하여 입력해주세요" << endl;
			scanf_s("%f%f%f", &x, &y, &z);

			list.InsertBack(x, y, z);
			break;
		case '-':
			list.DeleteBack();
			break;
		case 'E':
			cout << "좌표값을 스페이스로 구분하여 입력해주세요" << endl;
			scanf_s("%f%f%f", &x, &y, &z);

			list.InsertFront(x, y, z);
			break;
		case 'D':
			list.DeleteFront();
			break;
		case 'I':
			cout << "길이: " << list.GetLength() << endl;
			break;
		case 'C':
			list.Clear();
			break;
		case 'M':
			list.FindFarthestPos();
			break;
		case 'N':
			list.FindClosetPos();
			break;
		case 'S':
			list.Sort();
			break;
		case 'Q':
			return 0;
			break;
		default:
			cout << "올바르지 않은 입력입니다" << "endl";
			break;
		}

		list.Show();
	}
}