#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "ModuleRenderer3D.h"

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();

	bool Start();

	bool CleanUp();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint textureID;
};