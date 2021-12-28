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
	std::ifstream file;

	bool initialized;
	bool allow_update;
	bool origin_has_changed;
	bool json_data_not_null;


	std::string chunk_map_loc;
	nlohmann::json json_data;
	std::vector<std::string> chunk_file_depancies;
	struct etl::ChunkHandlerParameters parameters;
	struct chunk_file_header
	{
		std::string map_name;
		std::string type; // "2d relational"
		uint64_t chunk_scale;
		std::string default_chunk_id;
	} file_header;
	
	nlohmann::basic_json<> json_chunks;
	struct chunks_data
	{
		ChunkID origin_id;
		ChunkIndex origin_index;
		std::vector<etl::ChunkID_ChunkIndex> origin_neighbor;
		std::vector<etl::ChunkID_ChunkIndex> border;

		std::vector<etl::Chunk2D> open;
		std::vector<ChunkIndex> unclassified;
	} chunks;

	// process helpers -> struct chunk_data chunks
	int indexOfChunk(ChunkID _id);
	bool isOpen(std::vector<ChunkID>* _opened_ids, ChunkID _id);
	bool isInOriginChunk(glm::vec2 _position);
	float distanceToOrigin(ChunkPos _position);
	float distanceToOrigin(glm::vec2 _position);
	bool withinCullDistance(ChunkPos _position);

	// process -> struct chunk_data chunks
	void setOriginChunkNeighbors();
	void openAllChunksFromOrigin();
	int findOrigin(std::vector<etl::ChunkID_ChunkIndex>* _data);
	int findOrigin(std::vector<etl::Chunk2D>* _data);
	void classifyChunks();
	void classifyChunk(etl::Chunk2D& _chunk_ref);

	// add to -> struct chunk_data chunks
	void putInBorder(ChunkID _id, ChunkIndex _index);
	void putInOriginNeighbor(ChunkID _id, ChunkIndex _index);
	void putInOpen(etl::Chunk2D _chunk);

	// remove from -> struct chunk_data chunks
	void removeFromBorder(ChunkID _id);
	void removeFromOriginNeighbor(ChunkID _id);
	void removeFromOpen(ChunkID _id);

	// json <----> chunk_data 
	void initJSON();
	void readChunkFileHeader();
	ChunkID getDefaultStartChunkID();
	etl::Chunk2D getChunkFromFile(ChunkID _id);
	void removeChunk(ChunkID);
	void loadChunkData();
	void unloadChunkBody();

	void loadChunk(ChunkID _id);
	void unloadChunk(ChunkID _id);


};
