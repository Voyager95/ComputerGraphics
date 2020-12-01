#include "stdafx.h"
#include "Tile.h"
#include "SceneSystem.h"
#include "Transform.h"
#include "Ball.h"
#include "Object.h"

Tile::Tile(Object* object) : Component(object)
{
	type = TileType::BLACK;
	angle = 30;
}

void Tile::OnUpdate()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto ball = ss.GetObjectByName("Ball");
	
	//--- �浹 üũ�մϴ�. 
	if (ball != nullptr)
	{
		bool isCollide = false;								// �浹���� �÷����Դϴ�.

		auto ballBall = ball->GetComponent<Ball>();			// ball�� Ball ������Ʈ�Դϴ�.
		auto ballTransform = ball->GetTransform();			// ball�� Transform ������Ʈ�Դϴ�.

		/*
		���⿡ �浹�ϴ� �˰������� �ۼ��ϸ� �˴ϴ�.
		������ �۵������ �����Ͻʽÿ�.
		- isCollide������ �⺻������ false������ ���Դϴ�. ���� �浹�ϸ� true�� �����Ͻʽÿ�
		- isCollide������ true�� �Ǹ� �� Ÿ���� Ÿ�Կ� ���� ball���� �浹������ �� �� �Դϴ�.
		- ball�� ��ġ�� (0, y, z)�� ������ ���̸� z�� �����̸� �����Ǿ� ���� ���Դϴ�. y���� ���� �������鼭 ���� ���Դϴ�.
		������ Tip�� �����Ͻʽÿ�.
		- �� Ÿ���� Trnasform�� rotation�� �����Ͽ� �浹 ������ �Ǵ� �������� Ȯ���Ͻʽÿ�.
		- ���� radius�� ���� �׸��� �� Ÿ���� ���̸� ���Ͻʽÿ�
		���� ���ǻ����� �����Ͻʽÿ�.
		- Ÿ���� �߽ɰ���, ���� radius�� �� ũ��� ���� ���� �� �ֽ��ϴ�. �浹�˰������� �ۼ��ϰ� ũ�⸦ �����ϸ鼭 ���߽ʽÿ�.
		*/

		if (isCollide == true)
		{
			switch (type)
			{
			case TileType::BLACK:
				ballBall->Bounce();
				break;
			case TileType::RED:
				ballBall->Damage();
				break;
			default:
				break;
			}
		}
	}
}