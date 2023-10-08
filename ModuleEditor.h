#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>


class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	void DrawEditor();
	bool CleanUp();

	void AddFPS(const float aFPS);

	void ShowAboutInfo();
	void ShowInputInfo();

	bool isInputWindow;

	std::vector<float> mFPSLog;
};

static void HelpMarker(const char* desc);
