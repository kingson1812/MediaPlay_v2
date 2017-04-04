#include "ContextManager.h"

void ContextManager::LoadModel(const string& filepath, Vertex *& vertex)
{
	FILE * p;
	p = fopen("D:/MediaPlay_v2/Asset/Dragon.ply", "r");
	if (!p)
	{
		printf("Reading file %s failed\n", filepath.c_str());
		return;
	}

	while (!feof(p))
	{
		string head;
		fscanf(p, "%s", &head);
		if (!head.compare("vertex"))
		{
			fscanf(p, "%u", &vertex->m_vertexNumber);
		}

		if (!head.compare("end_header"))
		{
			//float line[8]; 
			//fscanf(p, "%f %f %f %f %f %f %f %f", &line);
		}
	}
	

}