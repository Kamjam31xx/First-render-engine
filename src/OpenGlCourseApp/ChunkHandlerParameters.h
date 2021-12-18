#pragma once
#include "glad/glad.h"

struct ChunkHandlerParameters
{
public:
	GLint chunk_scale;
	GLint cull_bias;
	GLint lod_0_bias;
	GLint lod_1_bias;
	GLint lod_2_bias;
	GLint lod_3_bias;
	GLint bias_scale;
} chunk_handler_parameters_default;