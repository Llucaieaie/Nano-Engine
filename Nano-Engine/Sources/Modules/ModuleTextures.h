#pragma once
#include "Module.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"

#include "DevIL/include/il.h"
#pragma comment (lib, "Nano-Engine/Externals/DevIL/libx86/DevIL.lib")

#include "backends/imgui_impl_opengl3.h"


#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();

	bool Start();

	bool CleanUp();

	bool TexFromImg(GLuint* imgData, GLuint width, GLuint height);
	bool LoadTextures(const char* path);
	void FreeTextures();

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint textureID = 0;
	GLuint textureWidth = 0;
	GLuint textureHeight = 0;
};