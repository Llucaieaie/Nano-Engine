#include "Mesh.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleGeometry.h"


ComponentMesh::ComponentMesh() : Component(nullptr)
{

}

ComponentMesh::ComponentMesh(GameObject* owner) : Component(owner)
{
	this->owner = owner;
	mesh = nullptr;
}

ComponentMesh::~ComponentMesh()
{
	mesh = nullptr;
}


void ComponentMesh::Inspector()
{
	if (ImGui::TreeNode("Mesh"))
	{
		ImGui::LabelText("##%f", "Vertex count:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_vertex);
		
		ImGui::LabelText("##%f", "Index count:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_index);

		ImGui::Checkbox("Show Normals", &App->geometry->showNormals);

		ImGui::TreePop();
		//if (ImGui::BeginTable("split", 3))
		//{
		//	ImGui::TableNextColumn(); ImGui::Checkbox("No titlebar", &App->geometry->showNormals);
		//}
	}
}