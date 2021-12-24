#include "ChunkHandler2D.h"


ChunkHandler2D::ChunkHandler2D()
{
	parameters = etl::chunk_handler_parameters_default;
	pos = glm::vec3(0.0, 0.0, 0.0);
	allow_update = false;
	origin_has_changed = false;
	chunk_data_not_null = false;
}

ChunkHandler2D::ChunkHandler2D(struct etl::ChunkHandlerParameters _parameters)
{
	parameters = _parameters
	pos = glm::vec3(0.0, 0.0, 0.0);
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
void ChunkHandler2D::setStartChunk(std::string _chunk_id)
{

}

bool ChunkHandler2D::init()
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
			origin_chunk = openChunk(start_chunk_id);


			for (etl::Chunk2D chunk : origin_chunk_neighbors) {

			}
		}
	}
	catch (std::exception& e) {
		printf(e.what());
		return false;
	}
	return true;
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

}

bool ChunkHandler2D::posIsInOriginChunk()
{

}

etl::Chunk2D ChunkHandler2D::openChunk(unsigned int _chunk_id)
{

}
void ChunkHandler2D::closeChunk(unsigned int _chunk_id)
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
	for (std::tuple<unsigned int, int, int> neighbor : origin_chunk.neighbors) {
		origin_chunk_neighbors.push_back(openChunk(std::get<CHUNK2D_NEIGHBOR_ID>(neighbor)));
	}
}
			 
unsigned int ChunkHandler2D::getDefaultStartChunk()
{

}
bool ChunkHandler2D::checkChunks(std::vector<etl::Chunk2D> _chunks)
{
	for (etl::Chunk2D chunk : _chunks) {

	}
}