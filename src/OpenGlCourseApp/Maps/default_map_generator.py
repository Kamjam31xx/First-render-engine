#	python script for generating a default map of type Chunk2D
#	This script is for testing purposes
#	all functionality will be re-introduced in c++ in the engine
#	in order to fully support save/edit/load functionality

name = ""
type = ""
scale = 1
default_chunk_id = 0

#	starting on the top-left corner, generate an (n by n) map of connected nodes
TAB_SIZE = 4
G_TAB = 0
NEIGHBOR_ID_INDEX = 0
NEIGHBOR_X_INDEX = 1
NEIGHBOR_Y_INDEX = 1

def tab( _n) :

	count = (_n + G_TAB) * TAB_SIZE
	string = ""
	for i in range(_number) :
		spaces += " "

	return string


def qoute(_string) : 
	
	return "\"" + _string + "\""

def qouteID(_id) : 
	
	return "\"cid_" + _id + "\""

def neighborString(_neighbor) :

	_nid = _neighbor[NEIGHBOR_ID_INDEX]
	_nx = _neighbor[NEIGHBOR_X_INDEX]
	_ny = _neighbor[NEIGHBOR_Y_INDEX]

	return "{ " + qoute("id") + " : " + _nid + ", " + qoute("x") + " : " + _nx + ", " + qoute("y") + " : " + _ny + " } \n"

def getChunkString(_id, _name, _neighbors, _entities, _ground_tile) :
 
	l = 0;

	chunk = tab(l) + qouteID(_id) + " : {\n"
	l += 1

	chunk += tab(l) + "\"name\" : " + name + ",\n"
	
	chunk += tab(l) + "\"neighbors\" : \n"
	l += 1

	chunk += tab(l) + "[\n"
	for neighbor in _neighbors :
		chunk += tab(l) + neighborString(neighbor)
	chunk += tab(l) + "],\n"
	l -= 1

	chunk += tab(l) + qoute("entities") + " : [],\n"
	chunk += tab(l) + qoute("ground_tile") + " : [],\n"

	return chunk;