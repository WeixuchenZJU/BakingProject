#pragma once
#include "Scene.h"
class OutputTriData
{
public:
	OutputTriData(const char* root,Scene *scene);
	~OutputTriData();
	glm::vec3 RandomSampleonTri(Vertex v0, Vertex v1, Vertex v2);
	glm::vec3 GetLightSignal(glm::vec3 sp);
};

