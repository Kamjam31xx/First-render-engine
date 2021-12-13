#pragma once
#include <glad/glad.h>
#include "ShadowMap.h"
class OmniShadowMap : public ShadowMap {
public:
	OmniShadowMap();

	bool Init(GLuint width, GLuint height);

	void Write();

	void Read(GLenum textureUnit);

	~OmniShadowMap();

private:

};

