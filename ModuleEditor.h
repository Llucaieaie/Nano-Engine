#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	void DrawEditor();
	//update_status PreUpdate(float dt);
	bool CleanUp();

	void AddFPS(const float aFPS);

};