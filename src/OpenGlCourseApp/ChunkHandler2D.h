#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <json/json.hpp>

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "Common.h"
#include "EngineTypes.h"
#include "Camera.h"


class ChunkHandler2D
{
public:
	ChunkHandler2D();
	ChunkHandler2D(struct etl::ChunkHandlerParameters _parameters);

	void setMapPath(std::string _file_path);
	std::string getMapPath();

	void setPos(glm::vec3 _pos);
	glm::vec3 getPos();

	void setStartChunk(std::string _chunk_id);

	bool init();

	void update();
	void load();
	void clear();



private:
	glm::vec3 pos;

	struct etl::ChunkHandlerParameters parameters;

	bool allow_update; 
	bool origin_has_changed;
	bool chunk_data_not_null;

	std::string chunk_map_loc;
	nlohmann::json chunk_data;
	unsigned int start_chunk_id;

	etl::Chunk2D origin_chunk;
	std::vector<etl::Chunk2D> origin_chunk_neighbors;
	std::vector<etl::Chunk2D> intermediate_chunks;
	std::vector<etl::Chunk2D> boarder_chunks;
	std::vector<etl::Chunk2D> adjacent_chunks;
	
	bool posIsInOriginChunk();

	etl::Chunk2D openChunk(unsigned int _chunk_id);
	void closeChunk(unsigned int _chunk_id);

	void updateOpen();
	void updateBoarder();
	void updateAdjacent();
	void updateOriginNeighbors();

	unsigned int getDefaultStartChunk();
	bool checkChunks(std::vector<etl::Chunk2D> _chunks);

};

/* USE EXAMPLE :
	ChunkHandler2D map = ChunkHandler2D(params);
	map.setMapPath(file_path);
	map.setStartChunk(chunk_id);
	map.setPos(glm::vec3(0.0, 0.0, 0.0)); // center of the initial chunk

*/

