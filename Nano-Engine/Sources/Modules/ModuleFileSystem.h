#pragma once

#include "Module.h"
#include<vector>
#include<string>
#include"Globals.h"


class ModuleFileSystem : public Module
{

public:
	ModuleFileSystem(Application* app, bool start_enabled = true);
	virtual ~ModuleFileSystem();

	bool Init() override;
	bool Start() override;

	bool CleanUp() override;

public:

};