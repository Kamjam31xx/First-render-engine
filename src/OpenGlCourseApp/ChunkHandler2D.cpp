#include "ChunkHandler2D.h"


ChunkHandler2D::ChunkHandler2D()
{
	struct ChunkHandlerParameters parameters = chunk_handler_parameters_default;
	setParameters(parameters);
	pos = glm::vec3(0.0, 0.0, 0.0);
	allow_update = false;
	origin_has_changed = false;
}

ChunkHandler2D::ChunkHandler2D(struct ChunkHandlerParameters _parameters)
{
	setParameters(_parameters);
	pos = glm::vec3(0.0, 0.0, 0.0);
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
GLboolean ChunkHandler2D::init()
{
	try {
		std::ifstream file;
		file.open(chunk_map_loc);
		file >> chunk_data;

		if()

	}
	catch (std::exception e) {
		printf("Exeption : ChunkHandler2D initialization failed ");
		return GLboolean(false);
	}
	return GLboolean(true);
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

void ChunkHandler2D::openChunk()
{

}
void ChunkHandler2D::closeChunk()
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

void ChunkHandler2D::setParameters(struct ChunkHandlerParameters _parameters)
{
	chunk_scale = _parameters.chunk_scale;
	cull_bias = _parameters.cull_bias;
	lod_0_bias = _parameters.lod_0_bias;
	lod_1_bias = _parameters.lod_1_bias;
	lod_2_bias = _parameters.lod_2_bias;
	lod_3_bias = _parameters.lod_3_bias;
	bias_scale = _parameters.bias_scale;
}				 