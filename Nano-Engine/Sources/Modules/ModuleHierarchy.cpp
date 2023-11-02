#include "Globals.h"
#include "Application.h"
#include "ModuleHierarchy.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "GameObject.h"

#include "ModuleRenderer3D.h"
#include "Glew/include/glew.h"
#include "Primitive.h"

ModuleHierarchy::ModuleHierarchy(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleHierarchy::~ModuleHierarchy()
{}

//-----------------------------------------------------------------
bool ModuleHierarchy::Start()
{
	//LOG("Setting up the hierarchy");
	bool ret = true;

	root = new GameObject();
	root->objectName = "Scene";

	return ret;
}

// -----------------------------------------------------------------
bool ModuleHierarchy::CleanUp()
{
	LOG("Cleaning Hierarchy");
	delete root;
	return true;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
update_status ModuleHierarchy::PostUpdate(float dt)
{


	return UPDATE_CONTINUE;
}

void ModuleHierarchy::DrawHierarchy()
{
	if (ImGui::Begin("Project")) {
		GameObjectTree(root);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Create Object")) {
				GameObject* parent = objectSelected;
				App->scene->createObj(parent);

				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
	//ImGui::End();
}

void ModuleHierarchy::GameObjectTree(GameObject* obj)
{
	ImGuiTreeNodeFlags flag_TNode = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

	if (obj->children.size() == 0)
		flag_TNode |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	if (obj == objectSelected)
		flag_TNode |= ImGuiTreeNodeFlags_Selected;

	bool gameObjectTree = ImGui::TreeNodeEx(obj, flag_TNode, obj->objectName.c_str());

	if (gameObjectTree)
	{
		if (!obj->children.empty()) {
			for (unsigned int i = 0; i < obj->children.size(); i++)
			{
				GameObjectTree(obj->children[i]);
			}
			ImGui::TreePop();
		}
	}

	if (obj->objectParent != nullptr) {

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", obj, sizeof(GameObject*));

			ImGui::Text("Changing...");
			ImGui::EndDragDropSource();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left))
		{
			SetGameObject(obj);
			if (objectSelected != obj) {
				SetGameObject(objectSelected);
			}
		}
	}

}

void ModuleHierarchy::SetGameObject(GameObject* obj)
{
	objectSelected = obj;
}