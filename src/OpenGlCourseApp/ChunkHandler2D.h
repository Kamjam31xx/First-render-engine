#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <json/json.hpp>

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "ChunkHandlerParameters.h"
#include "Chunk2D.h"
#include "Camera.h"


class ChunkHandler2D
{
public:
	ChunkHandler2D();
	ChunkHandler2D(struct ChunkHandlerParameters _parameters);

	void setMapPath(std::string _file_path);
	std::string getMapPath();

	void setPos(glm::vec3 _pos);
	glm::vec3 getPos();

	void setStartChunk(std::string _chunk_id);
	std::string getDefaultChunk();

	GLboolean init();

	void update();
	void load();
	void clear();



private:
	glm::vec3 pos;

	GLint chunk_scale;
	GLint cull_bias;
	GLint lod_0_bias;
	GLint lod_1_bias;
	GLint lod_2_bias;
	GLint lod_3_bias;
	GLint bias_scale;

	GLboolean allow_update; 
	GLboolean origin_has_changed;

	std::string chunk_map_loc;
	nlohmann::json chunk_data;
	std::string start_chunk;

	Chunk2D origin_chunk;
	std::vector<Chunk2D> origin_chunk_neighrbors;
	std::vector<Chunk2D> open_chunks;
	std::vector<Chunk2D> boarder_chunks;
	std::vector<Chunk2D> adjacent_chunks;
	

	void openChunk();
	void closeChunk();

	void updateOpen();
	void updateBoarder();
	void updateAdjacent();
	void updateOriginNeighbors();

	void setParameters(struct ChunkHandlerParameters _parameters);

};

/* USE EXAMPLE :
	ChunkHandler2D map = ChunkHandler2D(params);
	map.setMapPath(file_path);
	map.setStartChunk(chunk_id);
	map.setPos(glm::vec3(0.0, 0.0, 0.0)); // center of the initial chunk

*/

