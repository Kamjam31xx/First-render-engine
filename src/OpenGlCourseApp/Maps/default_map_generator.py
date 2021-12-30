#	python script for generating a default map of type Chunk2D
#	This script is for testing purposes
#	all functionality will be re-introduced in c++ in the engine
#	in order to fully support save/edit/load functionality

name = ""
type = ""
scale = 1
default_chunk_id = 0
sky = ""
width = 512
height = 512

#	starting on the top-left corner, generate an (n by n) map of connected nodes
TAB_SIZE = 4
G_TAB = 0
STRING_TYPE = "string"
INTEGER_TYPE = "integer"

class Header :

	def __init__(_keys, _values, _types) :

		self.keys = _keys
		self.values = _values
		self.types = _types

	def addVariable(_key, _value, _type) :

		self.keys.append(_key)
		self.values.append(_value)
		self.types.append(_type)

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

class Dependancy :

	def __init__(_path_str, _name_str, _type_str, _package_str) :

		self.path = _path_str
		self.name = _name_str
		self.type = _type_str
		self.core = _package_str

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

def getChunksString(_chunks) :

	l = 0

	chunks_string = tab(l) + "\"chunks\" :\n"
	chunks_string += tab(l) + "{\n"

	l += 1

	for chunk in chunks :

		chunks_string += tab(l) + getChunkString(chunk);

	l -= 1

	chunks_string += "}\n"

def getHeaderString(_header) :

	keys = _header.keys
	values = _header.values
	type = _header.types

	l = 0

	header_str = tab(l) + qoute("header") + " :\n{\n"

	l += 1

	for i in range(len(keys)) :

		value_str = qoute(values[i]) if types[i] == STRING_TYPE else str(values[i])
		header_str += tab(l) + qoute(keys[i]) + " : " + value_str
		header_str += ",\n" if i == len(_keys) - 1 else "\n"

	l -= 1

	header_str += tab(l) + "}\n"

	return header_str

def getDependancies(_chunks, _header) :

	# NOT WRITTEN YET

	entitities;
	ground_tiles; 
	
	dependancies = [];

	return dependancies;

def getDepandanciesString(_dependancies) :

	l = 0

	dependancies_str = tab(l) + qoute("dependancies") + " :\n{\n"

	l += 1
	count = 0
	for d in _dependancies :

		dependancies_str += tab(l) + "\"d_" + str(count) + "\"" + "{\n" 
		l += 1
		dependancies_str += tab(l) + qoute("path") + " : " + qoute(d.path) + ",\n"
		dependancies_str += tab(l) + qoute("name") + " : " + qoute(d.name) + ",\n"
		dependancies_str += tab(l) + qoute("type") + " : " + qoute(d.type) + ",\n"
		dependancies_str += tab(l) + qoute("package") + " : " + qoute(d.package) + "\n"
		l -= 1
		dependancies_str += tab(l) + "}\n"
	l -= 1

	dependancies_str += tab(l) + "}\n"

	return dependancies_str

def generateDefaultMap() :

	map_str = "{\n"

	# ---------- HEADER STRING
	header = Header();
	header.addVariable("map_name", "test_map", STRING_TYPE)
	header.addVariable("type", "Chunk2D", STRING_TYPE)
	header.addVariable("scale", 1, INTEGER_TYPE)
	header.addVariable("default_chunk_id", 0, INTEGER_TYPE)
	header.addVariable("number_of_chunks", (width * height), INTEGER_TYPE)
	header.addVariable("sky", "NONE", STRING_TYPE)
	map_header_str = getHeaderString(header)

	# ---------- CHUNKS STRING
	chunk_id_matrix = [[-1 for y in range(width)] for x in range(height)] 
	x, y, y_lim = 0
	for i in range(width * height) :

		chunk_id_matrix[x][y] = i

		if(y == 0 and x == 0) : # first id
			x += 1

		elif(i == width * height - 2) : # id before last id
			x += 1

		elif(y == 0) : # move down-left
			y += 1
			x -= 1

		elif(x == 0) : # move up-right to top, then over 1
			x = y + 1
			y = 0 + y_lim
			
	chunks = []
	coords = [(1,0), (0,1), (1,1), (-1,0), (0,-1), (-1,-1), (-1,1), (1,-1)]
	for x in range(width) :

		for y in range(height) :

			temp_chunk = Chunk2D()
			temp_chunk.id = chunk_id_matrix[x][y]

			for coord in coords : # loops 8 times through possible neighbors

				if( 0 <= x + coord[0] < width and 0 <= y + coord[1]) :

					temp_chunk.neighbors.append(Neighbor(chunk_id_matrix[x + coord[0]][y + coord[1]] ,coord[0], coord[1]))

			chunks.append(temp_chunk)
	
	map_chunks_str = getChunksString(chunks)

	# ---------- DEPENDANCIES STRING
	map_dependancies_str = getDependanciesString( getDependancies(chunks) )

	map_str += map_header_str
	map_str += map_chunks_str
	map_str += map_dependancies_str

	map_str += "}\n"

default_map = generateDefaultMap()



	

