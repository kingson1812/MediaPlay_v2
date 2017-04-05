#pragma once

#include "OpenGL.h"
#include "Vertex.h"
#include <vector>

#include <string>

using namespace std;

class Model
{
public:
	unsigned int m_indexNumber, m_vertexNumber,
				 m_ID;
	string m_filePath;

	Model();
	Model(string path, unsigned int id);
	~Model();

	void LoadModel();

private:
	int m_vboID, m_iboID;
	vector<Vertex> *m_vertexArray;
	unsigned int* m_indexArray;
};

