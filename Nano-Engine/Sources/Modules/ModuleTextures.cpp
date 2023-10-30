#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"

ModuleTextures::ModuleTextures(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleTextures::~ModuleTextures()
{
}

bool ModuleTextures::Start()
{
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


	glClearColor(0.f, 0.f, 0.f, 1.f);

	ilInit();

	return true;
}



bool ModuleTextures::CleanUp()
{
	return true;
}

bool ModuleTextures::TexFromImg(GLuint* imgData, GLuint width, GLuint height)
{
	FreeTextures();

	textureWidth = width;
	textureHeight = height;

	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Invert the texture
	GLuint* invertedImgData = new GLuint[width * height];
	for (GLuint i = 0; i < height; i++) {
		for (GLuint j = 0; j < width; j++) {
			invertedImgData[i * width + j] = imgData[(height - 1 - i) * width + j];
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, invertedImgData);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	delete[] invertedImgData;

	return true;
}

bool ModuleTextures::LoadTextures(const char* texPath)
{
	bool isLoaded = false;

	ILuint imgID = 0;

	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage(texPath);

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			TexFromImg((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
			isLoaded = true;
		}

		ilDeleteImages(1, &imgID);

		if (!isLoaded)
		{
			LOG("Error loading textures %s\n", texPath);
		}
	}
	return isLoaded;
}

void ModuleTextures::FreeTextures()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	textureWidth = 0;
	textureHeight = 0;
}