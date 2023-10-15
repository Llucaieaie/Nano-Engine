#include "ModuleFileSystem.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"

#include "PhysFS/include/physfs.h"

#pragma comment (lib, "PhysFS/libx86/physfs.lib")

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleFileSystem::~ModuleFileSystem()
{
}

bool ModuleFileSystem::Init()
{

	return true;
}

bool ModuleFileSystem::Start()
{

	return true;
}

bool ModuleFileSystem::CleanUp()
{

	return true;
}