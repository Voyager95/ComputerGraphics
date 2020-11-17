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
	std::queue<std::shared_ptr<Component>> m_OnCreateComponents;
	std::shared_ptr<Transform> m_Transform;
public:

	//-- Constructor
	Object();
	Object(std::string name);
	~Object();

	//---Getter
	std::shared_ptr<Transform> GetTransform() { return m_Transform; }
	std::list<std::shared_ptr<Component>> GetComponents() { return m_Components; }

	template <typename T>
	std::shared_ptr<T> GetComponent();

	template<typename T>
	std::shared_ptr<T> AddComponent();

	void OnAddTransform(std::shared_ptr<Transform> transform);
	void AddComponent(std::shared_ptr<Component> component);

	/// <summary>
	/// ������Ʈ���� OnCreate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnCreate();

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

template<typename T>
inline std::shared_ptr<T> Object::GetComponent()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		auto result = std::dynamic_pointer_cast<T>(*c);
		if (result != nullptr)
			return result;
	}
	return nullptr;
}

template<typename T>
inline std::shared_ptr<T> Object::AddComponent()
{
	auto component = std::make_shared<T>(shared_from_this());
	AddComponent(component);
	return component;
}
