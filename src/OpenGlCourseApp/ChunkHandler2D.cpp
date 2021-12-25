#include "ChunkHandler2D.h"


ChunkHandler2D::ChunkHandler2D()
{
	parameters = etl::chunk_handler_parameters_default;
	pos = glm::vec3(0.0, 0.0, 0.0);
	initialized = false;
	allow_update = false;
	origin_has_changed = false;
	chunk_data_not_null = false;
}

ChunkHandler2D::ChunkHandler2D(struct etl::ChunkHandlerParameters _parameters)
{
	parameters = _parameters;
	pos = glm::vec3(0.0, 0.0, 0.0);
	initialized = false;
	allow_update = false;
	origin_has_changed = false;
	chunk_data_not_null = false;
}

void ChunkHandler2D::setMapPath(std::string _file_path)
{
	chunk_map_loc = _file_path;
}
std::string ChunkHandler2D::getMapPath()
{
	return chunk_map_loc;
}
void ChunkHandler2D::setPos(glm::vec3 _pos)
{

}
glm::vec3 ChunkHandler2D::getPos()
{

}
void ChunkHandler2D::setStartChunk(ChunkID _chunk_id)
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
				if (start_chunk_id == NULL) {
					start_chunk_id = getDefaultStartChunk();
				}
				origin_chunk = std::tuple<ChunkID, ChunkIndex>(start_chunk_id, ChunkIndex(0));
				open_chunks.push_back(openChunk(start_chunk_id));

				openAllChunksFromOrigin();
				//updateOriginNeighbors();

			}
		}
		catch (std::exception& e) {
			printf(e.what());
			return false;
		}
		return true;
	}
	else {
		return false;
	}

}

void ChunkHandler2D::update()
{
	updateOpen();
	updateBoarder();
	updateAdjacent();
	updateOriginNeighbors();
}

void ChunkHandler2D::load()
{
	
}

void ChunkHandler2D::clear()
{
	// clear all chunks
}

void ChunkHandler2D::addChunk(etl::Chunk2D _chunk)
{
	unsigned int index = open_chunks.size();
	unclassified_chunks.push_back(index);
	open_chunks.push_back(_chunk);
}
void ChunkHandler2D::removeChunk(ChunkID _id)
{

}
int ChunkHandler2D::indexOfChunk(ChunkID _id)
{
	for (unsigned int i = 0; i < open_chunks.size(); i++)
	{
		if (open_chunks[i].id == _id)
		{
			return i;
		}
	}

	return -1;
}
void ChunkHandler2D::classifyChunks()
{
	for (ChunkIndex index : unclassified_chunks)
	{

	}
}
void ChunkHandler2D::classifyChunk(etl::Chunk2D& _chunk_ref)
{

}
bool ChunkHandler2D::testChunkDistance()
{

}

bool ChunkHandler2D::posIsInOriginChunk()
{

}
void ChunkHandler2D::openAllChunksFromOrigin()
{
	// push origin data into arrays
	std::vector<ChunkID> opened_ids;
	std::vector <std::tuple<etl::Chunk2D* , ChunkPos>> expanding;
	expanding.push_back( std::tuple<etl::Chunk2D*, ChunkPos>( &open_chunks[std::get<1>(origin_chunk)] , ChunkPos(0,0)) );
	
	// for each opened chunk -> expand it via its neighbors
	while (expanding.empty() == false)
	{
		// for each neighbor -> open it if not already opened & its distance is below the culling distance
		std::tuple<etl::Chunk2D*, ChunkPos> current = expanding.back();
		expanding.pop_back();

		unsigned int count = 0;
		ChunkID expanding_id = open_chunks.size();
		bool origin_neighbor = false;
		for (std::tuple<ChunkID, ChunkPos> neighbor : std::get<0>(current)->neighbors)
		{
			ChunkID id = std::get<0>(neighbor);

			// check if current has origin as a neighbor
			if (id == std::get<0>(origin_chunk))
			{
				// current has the origin chunk as a neighbor
				origin_neighbor = true;
			}
			
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
			ChunkPos pos = std::get<1>(current) + std::get<1>(neighbor);
			float distance = abs(sqrt((pos.x * pos.x) + (pos.y * pos.y)));
			if (distance * parameters.chunk_scale >= parameters.cull_bias)
			{
				continue;
			}

			// chunk is not opened & chunk is within view
			count++;
			unsigned int index = open_chunks.size();
			open_chunks.push_back(fetchChunk(id));
			expanding.push_back(std::tuple<etl::Chunk2D*, ChunkPos>(&open_chunks[index], pos));
		}
		opened_ids.push_back( (*std::get<0>(current)).id );
		if (count < std::get<0>(current)->neighbors.size())
		{
			// border chunks have less than 8 open neighbors
			// a chunk has to be able to expand to be a border chunk
			// so a neighbors.size() must be greater than count
			int current_index = indexOfChunk(std::get<0>(current)->id);
			if (current_index != -1)
			{
				border_chunks.push_back(std::tuple<ChunkID, ChunkIndex>(std::get<0>(current)->id, ChunkIndex(current_index));
			}
			else
			{
				// there shouldnt be an else
			}
		}
		if (origin_neighbor == true)
		{
			int current_index = indexOfChunk(std::get<0>(current)->id);
			if (current_index != -1)
			{
				origin_chunk_neighbors.push_back(std::tuple<ChunkID, ChunkIndex>(std::get<0>(current)->id, ChunkIndex(current_index));
			}
		}
	}
}

etl::Chunk2D ChunkHandler2D::openChunk(ChunkID _id)
{

}
void ChunkHandler2D::closeChunk(ChunkID _chunk_id)
{

}
etl::Chunk2D ChunkHandler2D::fetchChunk(ChunkID _id)
{

}

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
			 
unsigned int ChunkHandler2D::getDefaultStartChunk()
{

}
bool ChunkHandler2D::checkChunks(std::vector<etl::Chunk2D> _chunks)
{
	for (etl::Chunk2D chunk : _chunks) {

	}
}