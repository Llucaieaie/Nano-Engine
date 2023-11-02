#pragma once
#include "Globals.h"
#include "Component.h"
#include "Transform.h"

#include "imgui.h"

#include <vector>
#include <string>

enum class ComponentType;
class Component;
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void CreateComponent(ComponentType type);
	void InspectorWindow();

	GameObject* GetParent();

	std::string objectName;
	GameObject* objectParent;
	Transform* objectTransform;

	std::vector<Component*> components;
	std::vector<GameObject*> children;
};