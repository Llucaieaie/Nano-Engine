#include "GameObject.h"

GameObject::GameObject()
{
	objectName = "GameObject";

	objectTransform = new Transform(this);
	components.push_back(objectTransform);
}

GameObject::GameObject(GameObject* parent)
{
	objectName = "GameObject";
	this->objectParent = parent;
	if (parent != nullptr)
		parent->children.push_back(this);

	objectTransform = new Transform(this);
	components.push_back(objectTransform);
}

GameObject::~GameObject()
{
	objectName = "";
	objectParent = nullptr;

	objectTransform = nullptr;

	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();
}

void GameObject::CreateComponent(ComponentType type)
{
	Component* newComponent = new Component(this);

	newComponent->type = type;
	newComponent->active = true;

	components.push_back(newComponent);

	delete newComponent;
}

GameObject* GameObject::GetParent()
{
	return objectParent;
}

void GameObject::InspectorWindow()
{
	if (ImGui::CollapsingHeader("Inspector"))
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Inspector();
		}
	}
	ImGui::End();
}