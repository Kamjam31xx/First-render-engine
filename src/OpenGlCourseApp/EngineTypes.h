#pragma once
#include "glad/glad.h"
#include <glm.hpp>

#include <vector>
#include <tuple>
#include <string>

#include "GroundTile.h"

using ChunkID = unsigned int;
using ChunkPos = glm::ivec2;
using ChunkIndex = unsigned int;
using Flag = bool;

namespace etl {

	struct Entity
	{
		std::vector<std::string> key;
		std::vector<std::string> value;

		/*
			https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html

			https://www.youtube.com/watch?v=F_tuEyQ0Qjc

			https://www.geeksforgeeks.org/sparse-set/

			gross one
			http://gameprogrammingpatterns.com/component.html

			https://skypjack.github.io/2019-02-14-ecs-baf-part-1/
		*/
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
		ChunkID id;
		std::vector<std::tuple<ChunkID, ChunkPos>> neighbors;
		Flag loaded;
		std::vector<Entity*> entities;
		GroundTile ground_tile;
		ChunkPos relative_position;
	};

}

