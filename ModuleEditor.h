#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

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
	void ShowConsole();


	bool isInputWindow = false;
	bool isConsoleWindow = false;

	std::vector<float> mFPSLog;
	std::vector<std::string>* alignText;

	void pushText(const char* text);
	void ItemTooltip(const char* text);
};