#pragma once
#include "Globals.h"
#include "Component.h"
#include "imgui.h"

class GameObject;
class Component;
struct Mesh;

class ComponentMesh : public Component
{
public:

	ComponentMesh();
	ComponentMesh(GameObject* owner);
	~ComponentMesh();

	Mesh* mesh;

	void Inspector();
};