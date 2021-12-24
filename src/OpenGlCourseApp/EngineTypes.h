#pragma once
#include "glad/glad.h"

#include <vector>
#include <tuple>
#include <string>

#include "GroundTile.h"

namespace etl {

	struct Entity
	{
		std::vector<std::string> key;
		std::vector<std::string> value;
	};

	struct Lod
	{
	public:
		unsigned int n0;
		unsigned int n1;
		unsigned int n2;
		unsigned int n3;
	};

	struct ChunkHandlerParameters
	{
	public:
		float chunk_scale;
		float cull_bias;
		Lod lod;
		float bias_scale;
	} chunk_handler_parameters_default;

	struct Chunk2D
	{
	public:
		unsigned int id;
		std::vector<std::tuple<unsigned int, int, int>> neighbors;
		std::vector<Entity*> entities;
		GroundTile ground_tile;
	};

}

