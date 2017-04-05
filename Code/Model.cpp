#include "Model.h"
Model::Model() :m_vertexNumber(0), m_indexNumber(0)
{}

Model::Model(string path, unsigned int id) : m_filePath(path), m_ID(id), m_vertexNumber(0), m_indexNumber(0)
{}

void Model::LoadModel()
{
	FILE * p= fopen("D:/MediaPlay_v2/Asset/Man.obj", "r");
	if (!p)
	{
		printf("Reading file %s failed\n", m_filePath.c_str());
		return;
	}

	string vertexDetector = "#Vertex",
			indexDetector = "#Face";

	while (!feof(p))
	{
		string head;
		fscanf(p, "%s\n", &head[0],head.size());
		//printf("%d %s\n", strcmp(head.c_str(),vertexDetector.c_str()), head.c_str());

		if (!strcmp(head.c_str(), "v"))
		{
			
		}

		if (!strcmp(head.c_str(), vertexDetector.c_str()))
		{
			fscanf(p, "%*s %d", &m_vertexNumber);
			continue;
		}

		if (!strcmp(head.c_str(), indexDetector.c_str()))
		{
			fscanf(p, "%*s %d", &m_indexNumber);
			continue;
		}
	}
}