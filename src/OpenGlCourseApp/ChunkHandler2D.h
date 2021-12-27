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

	void updateViewPosition(glm::vec3* _pos);

	void setOriginChunk(ChunkID _chunk_id);

	bool init();

	void update();
	void load();
	void clear();



private:
	glm::vec2 view_pos;

	struct etl::ChunkHandlerParameters parameters;

	bool initialized;
	bool allow_update; 
	bool origin_has_changed;
	bool chunk_data_not_null;

	std::string chunk_map_loc;
	nlohmann::json chunk_data;

	struct chunk_data
	{
		ChunkID origin_id;
		ChunkIndex origin_index;
		std::vector<etl::ChunkID_ChunkIndex> origin_neighbor;
		std::vector<etl::ChunkID_ChunkIndex> border;

		std::vector<etl::Chunk2D> open;
		std::vector<ChunkIndex> unclassified;
	} chunks;


	bool isInOriginChunk(glm::vec2 _position);
	int findOrigin(std::vector<etl::ChunkID_ChunkIndex>* _data);
	int findOrigin(std::vector<etl::Chunk2D>* _data);

	void addChunk(etl::Chunk2D _chunk);
	void removeChunk(ChunkID _id);
	etl::Chunk2D fetchChunk(ChunkID _id);
	int indexOfChunk(ChunkID _id);
	void classifyChunks();
	void classifyChunk(etl::Chunk2D& _chunk_ref);

	float distanceToOrigin(ChunkPos _position);
	float distanceToOrigin(glm::vec2 _position);
	bool withinCullDistance(ChunkPos _position);
	void setOriginChunkNeighbors();
	void openAllChunksFromOrigin();

	void loadChunk(ChunkID _id);
	void unloadChunk(ChunkID _id);

	unsigned int getDefaultStartChunk();


};
