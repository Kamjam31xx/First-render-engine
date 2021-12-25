#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <json/json.hpp>

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

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

	bool initialized;
	bool allow_update; 
	bool origin_has_changed;
	bool chunk_data_not_null;

	std::string chunk_map_loc;
	nlohmann::json chunk_data;
	ChunkID start_chunk_id;

	std::tuple<ChunkID , ChunkIndex> origin_chunk;
	std::vector<std::tuple<ChunkID, ChunkIndex>> origin_chunk_neighbors;
	std::vector<std::tuple<ChunkID, ChunkIndex>> border_chunks;

	std::vector<etl::Chunk2D> open_chunks;
	std::vector<ChunkIndex> unclassified_chunks;

	void addChunk(etl::Chunk2D _chunk);
	void removeChunk(ChunkID _id);
	etl::Chunk2D fetchChunk(ChunkID _id);
	int indexOfChunk(ChunkID _id);
	void classifyChunks();
	void classifyChunk(etl::Chunk2D& _chunk_ref);

	bool testChunkDistance();
	
	bool posIsInOriginChunk();
	bool isVisible();
	void openAllChunksFromOrigin();

	etl::Chunk2D openChunk(ChunkID _id);
	void closeChunk(ChunkID _id);

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






		for (std::tuple<unsigned int, int, int> neighbor : origin_chunk.neighbors) {
		origin_chunk_neighbors.push_back(openChunk(std::get<CHUNK2D_NEIGHBOR_ID>(neighbor)));
	}
*/

