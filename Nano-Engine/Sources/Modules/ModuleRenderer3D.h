#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "Glew/include/glew.h"

//todo: REMOVE this before 1st delivery!!
#include "GLMath/glmath.h"

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start() override;
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	CPlane Grid;
	
	//You won't need this after using Frustum
	mat4x4 ProjectionMatrix;

	GLuint VBO; //Vertex Buffer Object
	GLuint EBO;
	GLuint VAO;
};