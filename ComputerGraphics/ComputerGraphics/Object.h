#pragma once
#include "stdafx.h"

class Component;
class Transform;
class Renderer;

class Object : public std::enable_shared_from_this<Object>
{
public:
	std::string name;
	std::string tag;
private:
	bool m_TransformExist;

	std::list<std::shared_ptr<Component>> m_Components;
	std::shared_ptr<Transform> m_Transform;
public:

	//-- Constructor
	Object();
	Object(std::string name);
	~Object();

	//---Getter
	std::shared_ptr<Transform> GetTransform() { return m_Transform; }
	std::list<std::shared_ptr<Component>> GetComponents() { return m_Components; }

	template<class T>
	std::shared_ptr<T> AddComponent();

	void OnAddTransform();
	void AddComponent(std::shared_ptr<Component> component);

	/// <summary>
	/// ������Ʈ���� OnUpdate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnUpdate();

	/// <summary>
	/// ������Ʈ���� OnLateUpdate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnLateUpdate();

	/// <summary>
	/// ������Ʈ���� OnPreDraw�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnPreRender();
};
