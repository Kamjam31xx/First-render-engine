#include "ChunkHandler2D.h"


ChunkHandler2D::ChunkHandler2D()
{
	parameters = etl::chunk_handler_parameters_default;
	view_pos = glm::vec3(0.0, 0.0, 0.0);
	initialized = false;
	allow_update = false;
	origin_has_changed = false;
	chunk_data_not_null = false;
	chunks = { 0,0,{},{},{},{} };
}

ChunkHandler2D::ChunkHandler2D(struct etl::ChunkHandlerParameters _parameters)
{
	parameters = _parameters;
	view_pos = glm::vec3(0.0, 0.0, 0.0);
	initialized = false;
	allow_update = false;
	origin_has_changed = false;
	chunk_data_not_null = false;
	chunks = { 0,0,{},{},{},{} };
}

void ChunkHandler2D::setMapPath(std::string _file_path)
{
	chunk_map_loc = _file_path;
}
std::string ChunkHandler2D::getMapPath()
{
	return chunk_map_loc;
}
void ChunkHandler2D::updateViewPosition(glm::vec3* _pos)
{
	glm::vec2 view_pos = glm::vec2(_pos->x, _pos->y);
	if (!isInOriginChunk(view_pos))
	{
		ChunkID id = findOrigin(&chunks.origin_neighbor);
		id = id == -1 ? findOrigin(&chunks.open) : id;
		if (id >= 0)
		{
			
		} 
		else if(parameters.cull_bias > distanceToOrigin(view_pos)){
			// test all possible chunks outside of cull_bias until found
		}
		else {
			// allow origin to stay until back on grid.
			// or break the engine;
		}
	}
}
void ChunkHandler2D::setOriginChunk(ChunkID _chunk_id)
{

}

bool ChunkHandler2D::init()
{
	if (initialized == false)
	{
		try {
			std::ifstream file;
			if (!chunk_map_loc.empty()) {
				file.open(chunk_map_loc);
				if (file.is_open()) {
					file >> chunk_data;
					chunk_data_not_null = true;
				}
				else {
					throw std::exception("Exception : unable to open file");
				}
			}
			else {
				throw std::exception("Exception : no file path");
			}
			if (chunk_data_not_null) {
				if (chunks.origin_id == NULL) {
					chunks.origin_id = getDefaultStartChunk();
				}

				openAllChunksFromOrigin();
			}
		}
		catch (std::exception& e) {
			printf(e.what());
			return false;
		}
	}
	else {
		return false;
	}

	return true;
}

void ChunkHandler2D::update()
{
	// check pos and update if needed
}

void ChunkHandler2D::load()
{
	// load all entities and push them into data
}

bool ChunkHandler2D::isInOriginChunk(glm::vec2 _position)
{
	if (_position.x <= 0.5 && _position.x >= -0.5 && _position.y <= 0.5 && _position.y >= -0.5)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int ChunkHandler2D::findOrigin(std::vector<etl::ChunkID_ChunkIndex>* _data)
{
	int id = -1;
	for (etl::ChunkID_ChunkIndex chunk : *_data)
	{
		glm::vec2 distance = view_pos - (glm::vec2)chunks.open[chunk.id].relative_position;
		id = isInOriginChunk(distance) ? chunk.id : -1;
	}
}
int ChunkHandler2D::findOrigin(std::vector<etl::Chunk2D>* _data)
{
	int id = -1;
	for (etl::Chunk2D chunk : *_data)
	{
		glm::vec2 distance = view_pos - (glm::vec2)chunk.relative_position;
		id = isInOriginChunk(distance) ? chunk.id : -1;
	}
}

void ChunkHandler2D::clear()
{
	// clear all chunks and unload entities from data
}

void ChunkHandler2D::addChunk(etl::Chunk2D _chunk)
{
	unsigned int index = chunks.open.size();
	chunks.unclassified.push_back(index);
	chunks.open.push_back(_chunk);
}
void ChunkHandler2D::removeChunk(ChunkID _id)
{

}
int ChunkHandler2D::indexOfChunk(ChunkID _id)
{
	for (unsigned int i = 0; i < chunks.open.size(); i++)
	{
		if (chunks.open[i].id == _id)
		{
			return i;
		}
	}

	return -1;
}
void ChunkHandler2D::classifyChunks()
{
	for (ChunkIndex index : chunks.unclassified)
	{

	}
}

void ChunkHandler2D::classifyChunk(etl::Chunk2D& _chunk_ref)
{

}
float ChunkHandler2D::distanceToOrigin(ChunkPos _position)
{
	return abs(sqrt((_position.x * _position.x) + (_position.y * _position.y)));
}
float ChunkHandler2D::distanceToOrigin(glm::vec2 _position)
{
	return abs(sqrt((_position.x * _position.x) + (_position.y * _position.y)));
}
bool ChunkHandler2D::withinCullDistance(ChunkPos _position)
{
	if (distanceToOrigin(_position) * parameters.chunk_scale >= parameters.cull_bias)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ChunkHandler2D::setOriginChunkNeighbors()
{
	etl::Chunk2D* origin = &chunks.open[chunks.origin_index];
	chunks.origin_neighbor.clear();
	for (etl::ChunkID_ChunkPos neighbor : origin->neighbors)
	{
		unsigned int neighbor_index = indexOfChunk(neighbor.id);
		if (neighbor_index >= 0)
		{
			chunks.origin_neighbor.push_back(etl::ChunkID_ChunkIndex{ neighbor.id, ChunkIndex(neighbor_index) });
		}
		else
		{
			// neighbor index not found - shouldnt happen
		}
		
	}
}
void ChunkHandler2D::openAllChunksFromOrigin()
{
	// origin chunk must be set
	// clear all vectors and push origin chunk into the open vector
	chunks.origin_neighbor.clear();
	chunks.border.clear();
	chunks.open.clear();
	chunks.origin_index = 0;
	chunks.open.push_back(fetchChunk(chunks.origin_id));

	// push origin data into arrays
	std::vector<ChunkID> opened_ids;
	const unsigned int CHUNK_POINTER = 0;
	const unsigned int CHUNK_POSITION = 1;

	std::vector <etl::ChunkPtr_ChunkPos> expanding;
	expanding.push_back(etl::ChunkPtr_ChunkPos{ &chunks.open[chunks.origin_id] , ChunkPos(0,0)});
	
	// for each opened chunk -> expand it via its neighbors
	while (expanding.empty() == false)
	{
		// for each neighbor -> open it if not already opened & its distance is below the culling distance
		etl::ChunkPtr_ChunkPos current = expanding.back();
		expanding.pop_back();

		unsigned int opened_neighbors = 0;
		ChunkID expanding_id = chunks.open.size();
		bool origin_neighbor = false;
		for (etl::ChunkID_ChunkPos neighbor : current.ptr->neighbors)
		{
			ChunkID id = neighbor.id;

			// check if current has origin as a neighbor
			origin_neighbor = id == chunks.origin_id ? true : false;
			
			// check if chunk is already opened
			bool is_opened = false;
			for (ChunkID opened : opened_ids)
			{
				if (id == opened)
				{
					is_opened = true;
					break;
				}
			}
			if (is_opened) {
				continue;
			}

			// check if chunk is within view
			ChunkPos neighbor_pos = current.pos + neighbor.pos;
			if (!withinCullDistance(neighbor_pos))
			{
				continue;
			}


			// chunk is not opened & chunk is within view
			opened_neighbors++;
			unsigned int index = chunks.open.size();
			chunks.open.push_back(fetchChunk(id));
			expanding.push_back(etl::ChunkPtr_ChunkPos{ &chunks.open[index], neighbor_pos });
		}
		opened_ids.push_back( current.ptr->id );

		unsigned int neighbor_count = current.ptr->neighbors.size();
		int current_index = indexOfChunk(current.ptr->id);
		if (opened_neighbors < neighbor_count || neighbor_count < CHUNK2D_MAX_NEIGHBOR_COUNT)
		{
			// border chunks have less than 8 open neighbors
			// a chunk has to be able to expand to be a border chunk
			// so a neighbors.size() must be greater than count
			if (current_index != -1)
			{
				chunks.border.push_back(etl::ChunkID_ChunkIndex{ current.ptr->id, ChunkIndex(current_index) });
			}
		}
		
		if (origin_neighbor == true && current_index != -1)
		{
			chunks.origin_neighbor.push_back(etl::ChunkID_ChunkIndex{ current.ptr->id, ChunkIndex(current_index) });
		}
	}
}

void ChunkHandler2D::loadChunk(ChunkID _id)
{

}
void ChunkHandler2D::unloadChunk(ChunkID _chunk_id)
{

}
etl::Chunk2D ChunkHandler2D::fetchChunk(ChunkID _id)
{
	// get chunk from chunk_data
}

/*
void ChunkHandler2D::updateOpen()
{

}

void ChunkHandler2D::updateBoarder()
{

}

void ChunkHandler2D::updateAdjacent()
{

}

void ChunkHandler2D::updateOriginNeighbors()
{

}
*/
			 
unsigned int ChunkHandler2D::getDefaultStartChunk()
{

}
