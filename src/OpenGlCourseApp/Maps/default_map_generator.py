#	python script for generating a default map of type Chunk2D
#	This script is for testing purposes
#	all functionality will be re-introduced in c++ in the engine
#	in order to fully support save/edit/load functionality

#name = ""
#type = ""
#scale = 1
#default_chunk_id = 0
#sky = ""
width = 3
height = 3

#	starting on the top-left corner, generate an (n by n) map of connected nodes
TAB_SIZE = 4
G_TAB = 0
STRING_TYPE = "string"
INTEGER_TYPE = "integer"


class Header :

	def __init__(self, keys, values, types) :

		self.keys = keys
		self.values = values
		self.types = types

	def addVariable(self, key, value, value_type) :

		self.keys.append(key)
		self.values.append(value)
		self.types.append(value_type)


class Neighbor :

	def __init__(self, id, x, y) :
		
		self.id = id
		self.x = x
		self.y = y


class Entity :

	def __init__(self, name, x, y, z, components) :

		self.name = name
		self.x = x
		self.y = y
		self.z = z
		self.components = components


class GroundTile :

	def __init___(self, vertices, indices) :
		
		self.vertices = vertices
		self.indices = indices


class Chunk2D :

	def __init__(self, id):

		self.id = id
		self.neighbors = [];
		self.entities = [];
		self.ground_tiles = [];


class Dependancy :

	def __init__(self, path_str, name_str, type_str, package_str) :

		self.path = path_str
		self.name = name_str
		self.d_type = type_str
		self.package = package_str


def tab( _n) :

	global G_TAB
	global TAB_SIZE
	count = (_n + G_TAB) * TAB_SIZE
	string = ""
	for i in range(count) :
		string += " "

	return string


def qoute(_string) : 
	
	return f"\"{_string}\""

def qouteID(_id) : 
	
	return f"\"cid_{_id}\""

def neighborToString(_neighbor) :

	return f"{{{qoute('id')}: {_neighbor.id}, {qoute('x')}: {_neighbor.x}, {qoute('y')}: {_neighbor.y} }}"

def getChunkString(_chunk) :
 
	l = 0

	chunk_str = f"{tab(l) + qouteID(_chunk.id)}:\n{tab(l)}{{\n"

	l += 1

	chunk_str += f"{tab(l)}\"id\": {_chunk.id},\n"
	
	chunk_str += f"{tab(l)}\"neighbors\" :\n"

	chunk_str += f"{tab(l)}[\n"

	l += 1

	neighbor_strings = []
	for i in range(len(_chunk.neighbors)) :

		if i == len(_chunk.neighbors) - 1 : 

			neighbor_strings.append(f"{tab(l) + neighborToString(_chunk.neighbors[i])}\n")

		else : 

			neighbor_strings.append(f"{tab(l) + neighborToString(_chunk.neighbors[i])},\n")
		


	neighbors_string = "".join(neighbor_strings)
	chunk_str += neighbors_string

	l -= 1

	chunk_str += f"{tab(l)}],\n"

	chunk_str += f"{tab(l) + qoute('entities')}: [],\n"
	chunk_str += f"{tab(l) + qoute('ground_tile')}: [],\n"

	l -= 1

	chunk_str += f"{tab(l)}}}\n"

	return chunk_str;

def getChunksString(_chunks) :

	global G_TAB

	chunks_string = f"{tab(0)}\"chunks\" :\n"
	chunks_string += f"{tab(0)}{{\n"
	G_TAB += 1

	i = 0
	chunk_strings = []
	for chunk in _chunks :

		chunk_strings.append(f"{getChunkString(chunk)}\n")

	chunks_strings = "".join(chunk_strings)
	chunks_string += chunks_strings

	G_TAB -= 1
	chunks_string += f"{tab(0)}}}\n"

	return chunks_string

def getHeaderString(_header) :

	keys = _header.keys
	values = _header.values
	types = _header.types

	l = 0

	header_str = f"{tab(l) + qoute('header')}:\n{tab(l)}{{\n"

	l += 1

	for i in range(len(keys)) :

		value_str = qoute(values[i]) if types[i] == STRING_TYPE else str(values[i])
		header_str += f"{tab(l) + qoute(keys[i])}: {value_str}"
		header_str += "\n" if i == len(keys) - 1 else ",\n"

	l -= 1

	header_str += f"{tab(l)}}}\n"

	return header_str

def getDependancies(_chunks, _header) :

	# NOT WRITTEN YET

	entities = [];
	ground_tiles = []; 
	
	dependancies = [];

	return dependancies;

def getDepandanciesString(_dependancies) :

	l = 0

	dependancies_str = f"{tab(l) + qoute('dependancies')}:\n{tab(l)}{{\n"

	l += 1
	count = 0
	for d in _dependancies :

		dependancies_str += f"{tab(l)}\"d_{str(count)}\"{{\n" 
		l += 1
		dependancies_str += f"{tab(l) + qoute('path')}: {qoute(d.path)},\n"
		dependancies_str += f"{tab(l) + qoute('name')}: {qoute(d.name)},\n"
		dependancies_str += f"{tab(l) + qoute('type')}: {qoute(d.d_type)},\n"
		dependancies_str += f"{tab(l) + qoute('package')}: {qoute(d.package)}\n"
		l -= 1
		dependancies_str += f"{tab(l)}}}\n"
	l -= 1

	dependancies_str += f"{tab(l)}}}\n"

	return dependancies_str

def generateDefaultMap() :

	global G_TAB
	map_str = f"{{\n"
	G_TAB += 1

	# ---------- HEADER STRING

	header = Header([],[],[]);
	header.addVariable("map_name", "test_map", STRING_TYPE)
	header.addVariable("type", "Chunk2D", STRING_TYPE)
	header.addVariable("scale", 1, INTEGER_TYPE)
	header.addVariable("default_chunk_id", 0, INTEGER_TYPE)
	header.addVariable("number_of_chunks", (width * height), INTEGER_TYPE)
	header.addVariable("sky", "NONE", STRING_TYPE)
	map_header_str = getHeaderString(header)


	# ---------- CHUNKS STRING

	chunk_id_matrix = [[-1 for y in range(width)] for x in range(height)] 
	x = 0
	y = 0
	y_lim = 1

	for i in range(width * height - 1) :

		chunk_id_matrix[x][y] = i

		if(y == 0 and x == 0) : # first id

			x += 1

		elif(i == width * height - 2) : # id before last id

			x += 1
			chunk_id_matrix[x][y] = i + 1
			break

		elif(y == 0) : # move down-left

			y += 1
			x -= 1

		elif(x == 0 and y + 1 < width) : # move up-right to top, then over 1

			x = y + 1 
			y = 0 # + y_lim

		elif(x == 0) :

			x = y
			y = y_lim
			y_lim += 1

		elif(x != 0 and y + 1 == width) :

			x = y
			y = y_lim
			y_lim += 1
		
		else :
			x -= 1
			y += 1
	
	#for row in chunk_id_matrix :
	#	print(row)
			
	chunks = []
	coords = [(1,0), (0,1), (1,1), (-1,0), (0,-1), (-1,-1), (-1,1), (1,-1)]

	for x in range(width) :

		for y in range(height) :

			#print(x+y)
			temp_chunk = Chunk2D(chunk_id_matrix[x][y])
			c_id = chunk_id_matrix[x][y]

			for coord in coords : # loops 8 times through possible neighbors

				if( 0 <= x + coord[0] < width and 0 <= y + coord[1] < height) :

					n = Neighbor(chunk_id_matrix[x + coord[0]][y + coord[1]] ,coord[0], coord[1])
					temp_chunk.neighbors.append(n)

			chunks.append(temp_chunk)

	#print("LENGTH OF CHUNKS _________________________ " + str(len(chunks)))
	#print(width * height)
	map_chunks_str = getChunksString(chunks)


	# ---------- DEPENDANCIES STRING

	map_dependancies_str = getDepandanciesString( getDependancies(chunks, header) )

	map_str += map_header_str
	map_str += map_chunks_str
	map_str += map_dependancies_str

	G_TAB -= 1
	map_str += f"}}\n"

	return map_str

default_map = generateDefaultMap()
print(default_map)


	

