#pragma once
#include <glad/glad.h>
#include "Mesh.h"
class ScreenQuad
{
public:

	ScreenQuad();
	void Init();

	void Render();

	GLuint GetVAO();
	GLuint GetVBO();

	~ScreenQuad();

private:

	GLuint VAO, VBO;

};

