#pragma once

/// <summary>
/// Rigidbody������Ʈ�� �߰��� ������Ʈ�� OnCreate��, Ȥ�� OnEnable, Disable�϶�,
/// �� �ý��ۿ� �ڱ⸦ �����,
/// �׸��� ���� �浹�ߴ��� üũ�ϴ� �Լ��� ���� SceneSystem�� ������ �ش��Լ��� ȣ���Ѵ�.
/// 
/// üũ�ϴ� �Լ����� OnCollide�Լ��� ȣ���ؼ� 
/// </summary>
class RigidbodySystem
{
public:
	//--- �̱��� ������
	RigidbodySystem(const RigidbodySystem&) = delete;
	RigidbodySystem& operator=(const RigidbodySystem&) = delete;

	/// <summary>
	/// �̱��� �ν��Ͻ��� ����ϴ�.
	/// *���� ��� ���� ���� ��ȯ���� ���Դϴ�.
	/// </summary>
	/// <returns>�̱��� �ν��Ͻ�</returns>
	static RigidbodySystem& GetInstance();
private:
	RigidbodySystem();
};

