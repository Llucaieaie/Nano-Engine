#pragma once

#ifndef MODULE_GEOMETRY
#define MODULE_GEOMETRY

#include "Module.h"
#include "Globals.h"
#include "Glew/include/glew.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include "glmath.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include <vector>

#define VERTEX_ARGUMENTS 3

struct Mesh
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	vec3 GetVectorFromIndex(float* startValue);

	void Render();
	void ShowNormals();
};


class ModuleGeometry : public Module
{
public:

	ModuleGeometry(Application* app, bool start_enabled = true);
	~ModuleGeometry();

	bool Init() override;
	bool Start() override;
	bool CleanUp() override;
	void LoadFile(const char* file_path);
	void ImportMesh(aiMesh* aiMesh);
	void BufferMesh(Mesh* mesh);
	void RenderScene();

private:

public:

	std::vector<Mesh*> meshVector;
};

#endif