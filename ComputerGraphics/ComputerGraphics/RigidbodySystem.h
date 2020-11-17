#pragma once

/// <summary>
/// Rigidbody컴포넌트가 추가된 오브젝트가 OnCreate때, 혹은 OnEnable, Disable일때,
/// 이 시스템에 자기를 등록함,
/// 그리고 서로 충돌했는지 체크하는 함수를 만들어서 SceneSystem의 루프에 해당함수를 호출한다.
/// 
/// 체크하는 함수에서 OnCollide함수를 호출해서 
/// </summary>
class RigidbodySystem
{
public:
	//--- 싱글톤 디자인
	RigidbodySystem(const RigidbodySystem&) = delete;
	RigidbodySystem& operator=(const RigidbodySystem&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스를 얻습니다.
	/// *없는 경우 새로 만들어서 반환해줄 것입니다.
	/// </summary>
	/// <returns>싱글톤 인스턴스</returns>
	static RigidbodySystem& GetInstance();
private:
	RigidbodySystem();
};

