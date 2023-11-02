#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "GLMath/glmath.h"
#include "imgui.h"
//#include "MathGeoLib/include/Math/float3x3.h"
//#include "MathGeoLib/include/Math/float4x4.h"
//#include "MathGeoLib/include/Math/Quat.h"

class GameObject;
class Component;

class Transform : public Component
{
public:

	Transform();
	Transform(GameObject* owner);
	~Transform();

	mat4x4 glTransform, glTransformT;
	mat4x4 lTransform;

	vec3 position, scale, rotation;

	void SetTransformMatrix(vec3 _position, vec3 _rotation, vec3 _scale);
	void Inspector();
};