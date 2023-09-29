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
	bool CleanUp();

	void AddFPS(const float aFPS);

};