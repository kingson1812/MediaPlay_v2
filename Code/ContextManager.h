#pragma once
#include <string>
#include "Vertex.h"

using namespace std;

class ContextManager
{
public:
	void LoadModel(const string& filePath, Vertex*& vertex);
};