#include "PlyBuilder.h"

bool PlyBuilder::LoadPlyFile(string filename)
{
	ifstream inFile;
	string fileLocation = "..\\ply_files\\" + filename;

	inFile.open(fileLocation);

	if (!inFile)
	{
		printf("Failed to open File: %s\n", fileLocation);
		this->loaded = false;
		return this->isLoaded();
	}

	string oneLine;
	bool validFile = false;

	while (inFile)
	{
		//Take in and parse the line
		getline(inFile, oneLine, '\n');
		istringstream iss(oneLine);
		vector<string> tokens{ istream_iterator<string>{iss},
			istream_iterator<string>{} };

		//Checks if the file is a ply file
		if (!validFile)
		{
			validFile = this->validateFile(tokens, fileLocation);
			if (!validFile) 
			{
				this->loaded = false;
				return this->isLoaded();
			}
		}

		this->parseTokens(tokens);
	}

	inFile.close();

	this->loaded = (this->verifyFaces() && this->verifyVertices());	
	return this->isLoaded();
}

void PlyBuilder::parseTokens(vector<string> tokens)
{
	Face face;

	switch (tokens.size())
	{
	case 2:
		// Skip End Header
		if (!tokens[0].compare("end") && !tokens[1].compare("header"))
		{
			// printf("skipping end header\n");
		}
		break;
	case 3:
		this->parseCoordinates(tokens);
		break;
	case 4:
		this->parseFace(tokens);
		break;
	case 5:
		// printf("Skipping property list uint8 int32 vertex_indices\n");
		break;
	default:
		// printf("ERROR!!! TOKEN SIZE NOT ACCOUNTED FOR: %d\n", tokens.size());
		break;
	}
}

void PlyBuilder::parseCoordinates(vector<string> tokens)
{
	//Skip format ascii
	if (!tokens[0].compare("format") && !tokens[1].compare("ascii") && !tokens[2].compare("1.0"))
	{
		// printf("skipping over format ascii 1.0\n");
		return;
	}

	//Skip property floats
	if (!tokens[0].compare("property") && !tokens[1].compare("float32"))
	{
		// printf("skipping over property float32\n");
		return;
	}

	// if its an element decide if its total vertices or total polygons/faces
	// polygons stored as triangles
	if (!tokens[0].compare("element"))
	{
		if (!tokens[1].compare("vertex"))
		{
			this->totalVertices = atoi(tokens[2].c_str());
			// printf("the total number of vertices is: %s\n", tokens[2].c_str());
		}

		if (!tokens[1].compare("face"))
		{
			this->totalFaces = atoi(tokens[2].c_str());
			// printf("the total number of faces is: %s\n", tokens[2].c_str());
		}
		return;
	}

	float x, y, z;
	Vertex v;

	// if the tokens do not match then it must be a vertices
	x = atof(tokens[0].c_str());
	y = atof(tokens[1].c_str());
	z = atof(tokens[2].c_str());

	v = Vertex(point4(x, y, z, 1.0));
	this->vertices.push_back(v);
}

void PlyBuilder::parseFace(vector<string> tokens)
{
	Face face = Face(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));
	this->faces.push_back(face);
}

bool PlyBuilder::validateFile(vector<string> tokens, string fileLocation)
{
	bool size = tokens.size() == 1;
	bool plyDescriptor = (tokens[0][0] == 'p' || tokens[0][0] == 'P') && (tokens[0][1] == 'l' || tokens[0][1] == 'L') && (tokens[0][2] == 'y' || tokens[0][2] == 'Y');

	if (!size || !plyDescriptor)
	{
		printf("ERROR!!!! File %s is not a ply file\n", fileLocation);
		return false;
	}

	// printf("%s is a ply file will start loading\n", fileLocation);
	return true;
}

bool PlyBuilder::verifyVertices()
{
	vector<Vertex> vertices = this->vertices;

	if (this->totalVertices != vertices.size())
	{
		cout << "Error!!! The total number of vertices does not match the expected number of vertices" << endl;

		for (int index = 0; index < vertices.size(); ++index)
		{
			point4 vertex = vertices[index].GetPosition();
			cout << "x: " << vertex.x << " y: " << vertex.y << " z: " << vertex.z << endl;
		}

		return false;
	}

	return true;
}

bool PlyBuilder::verifyFaces()
{
	vector<Face> faces = this->faces;

	if (this->totalFaces != faces.size())
	{
		cout << "Error!!! The total number of faces does not match the expected number of faces" << endl;

		for (int index = 0; index < faces.size(); ++index)
		{
			Face face = faces[index];
			cout << "v1: " << face.v1 << " y: " << face.v2 << " z: " << face.v3 << endl;
		}

		return false;
	}

	return true;
}