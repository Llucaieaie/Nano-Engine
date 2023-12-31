#ifndef MODULE_GEOMETRY
#define MODULE_GEOMETRY

#include "Module.h"
#include "Globals.h"

#include "Glew/include/glew.h"

//#include "glmath.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#pragma comment (lib, "Nano-Engine/Externals/Assimp/libx86/assimp.lib")
#pragma comment (lib, "Nano-Engine/Externals/Glew/libx86/glew32.lib")

#include <vector>

#define VERTEX_ARGUMENTS 5

class GameObject;

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

	GLuint texture_height;
	GLuint texture_width;

	float3 GetVectorFromIndex(float* startValue);

	GameObject* owner;

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
	void ImportMesh(aiMesh* aiMesh, GameObject* object);
	void BufferMesh(Mesh* mesh);
	void RenderScene();

	bool showNormals = true;
private:

public:

	std::vector<Mesh*> meshVector;
};

#endif