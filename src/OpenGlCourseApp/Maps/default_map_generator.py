#	python script for generating a default map of type Chunk2D
#	This script is for testing purposes
#	all functionality will be re-introduced in c++ in the engine
#	in order to fully support save/edit/load functionality

name = ""
type = ""
scale = 1
default_chunk_id = 0
width = 512
height = 512

#	starting on the top-left corner, generate an (n by n) map of connected nodes
TAB_SIZE = 4
G_TAB = 0

class Neighbor :

	def __init__(_id, _x, _y) :
		
		self.id = _id
		self.x = _x
		self.y = _y

class Entity :

	def __init__(_name, _x, _y, _z, _components) :

		self.name = _name
		self.x = _x
		self.y = _y
		self.z = _z
		self.components = _components

class GroundTile :

	def __init___(_vertices, _indices) :
		
		self.vertices = _vertices
		self.indices = _indices

class Chunk2D :

	def __init__(_id):

		self.id = _id
		self.neighbors = [];
		self.entities = [];
		self.ground_tiles = [];

def tab( _n) :

	count = (_n + G_TAB) * TAB_SIZE
	string = ""
	for i in range(count) :
		string += " "

	return string


def qoute(_string) : 
	
	return "\"" + _string + "\""

def qouteID(_id) : 
	
	return "\"cid_" + _id + "\""

def neighborToString(_neighbor) :

	return "{ " + qoute("id") + " : " + _neighbor.id + ", " + qoute("x") + " : " + _neighbor.x + ", " + qoute("y") + " : " + _neighbor.y + " }"

def getChunkString(_chunk) :
 
	l = 0

	chunk_str = tab(l) + qouteID(_chunk.id) + " :\n{\n"

	l += 1

	chunk_str += tab(l) + "\"name\" : " + _chunk.name + ",\n"
	
	chunk_str += tab(l) + "\"neighbors\" :\n"

	l += 1

	chunk_str += tab(l) + "[\n"

	l += 1

	for neighbor in _chunk.neighbors :
		chunk_str += tab(l) + neighborToString(neighbor) + "\n"

	l -= 1

	chunk_str += tab(l) + "],\n"

	l -= 1

	chunk_str += tab(l) + qoute("entities") + " : [],\n"
	chunk_str += tab(l) + qoute("ground_tile") + " : [],\n"

	l -= 1

	chunk_str += tab(l) + "}\n"

	return chunk;

def getHeader(_keys, _values, _type) :

	l = 0

	header_str = tab(l) + qoute("header") + " :\n{\n"

	l += 1

	for i in range(len(_keys)) :

		value_str = qoute(_value[i]) if _type == "string" else str(value)
		header_str += tab(l) + qoute(_key[i]) + " : " + value_str
		header_str += ",\n" if i == len(_keys) - 1 else "\n"

	l -= 1

	header_str += tab(l) + "}\n"

	return header_str









