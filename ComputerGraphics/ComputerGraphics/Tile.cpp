#include "stdafx.h"
#include "Tile.h"
#include "SceneSystem.h"
#include "Transform.h"
#include "Ball.h"
#include "Object.h"
#include "rigidbody.h"


Tile::Tile(Object* object) : Component(object)
{
	type = TileType::BLACK;
	angle = 30;
}

void Tile::OnCreate()
{
	auto tileTransform = GetBelongingTransform();
	GlobalUtility::PrintVec3("타일 위치: ",tileTransform->GetWorldPosition());
}

void Tile::OnUpdate()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto ball = ss.GetObjectByName("Ball");
	
	//--- 충돌 체크합니다. 
	if (ball != nullptr)
	{
		bool isCollide = false;								// 충돌판정 플레그입니다.

		auto ballBall = ball->GetComponent<Ball>();			// ball의 Ball 컴포넌트입니다.
		auto ballTransform = ball->GetTransform();			// ball의 Transform 컴포넌트입니다.

		/*
		여기에 충돌하는 알고리즘을 작성하면 됩니다.
		다음의 작동방식을 참고하십시오.
		- isCollide변수가 기본적으로 false상태일 것입니다. 만일 충돌하면 true로 변경하십시오
		- isCollide변수가 true가 되면 이 타일의 타입에 따라 ball에게 충돌정보를 줄 것 입니다.
		- ball의 위치는 (0, y, z)의 형태일 것이며 z는 음수이며 고정되어 있을 것입니다. y값은 공이 떨어지면서 변할 것입니다.
		다음의 Tip을 참고하십시오.
		- 이 타일의 Trnasform의 rotation에 접근하여 충돌 판정이 되는 각도인지 확인하십시오.
		- 공의 radius와 높이 그리고 이 타일의 높이를 비교하십시오
		다음 주의사항을 참고하십시오.
		- 타일의 중심각도, 공의 radius는 모델 크기와 맞지 않을 수 있습니다. 충돌알고리즘을 작성하고 크기를 조절하면서 맞추십시오.
		*/

		auto tileTransform = GetBelongingTransform();		
		auto tileAngle = tileTransform->GetWorldRotation();				// 로컬 로테이션 -> 월드 로테이션
		auto tilePosition = tileTransform->GetWorldPosition();			// 로컬 포지션 -> 월드 포지션
		auto ballPosition = ballTransform->GetWorldPosition();			// 로컬 포지션 -> 월드 포지션
		auto ballRigidbody = ball->GetComponent<Rigidbody>();
		auto rigidbody = ballRigidbody->GetPresentDirection();

		if (tileAngle.y > 360)
			tileAngle.y = tileAngle.y - 360;
		else if (tileAngle.y < -360)
			tileAngle.y = tileAngle.y + 360;
	
		if (tileAngle.y <= 0 && tileAngle.y >= -45 || tileAngle.y >= 315 && tileAngle.y <= 360)
		{
			if (ballPosition.y - ballBall->radius <= tilePosition.y && ballPosition.y - ballBall->radius >= tilePosition.y - 1)
			{
				isCollide = true;
				//std::cout << tileAngle.y << std::endl;
				//std::cout << tilePosition.y << std::endl;
				//std::cout << ballPosition.y - ballBall->radius << std::endl;
			}
		}

		else
		{
			isCollide = false;
			//std::cout << tileAngle.y << std::endl;
		}
		
		if (isCollide == true && rigidbody.y < 0)
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
