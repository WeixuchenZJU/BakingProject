#pragma once
#include <glm/glm.hpp>
#include <vector>
class Scene;
#define box_max(a,b) (a>b?a:b)
#define box_min(a,b) (a>b?b:a)
struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	//// tangent
	//glm::vec3 Tangent;
	//// bitangent
	//glm::vec3 Bitangent;
};
struct ColorVertex {
	// position
	glm::vec3 Position;
	// color
	glm::vec3 Color;
};
struct TriangleFace {
	int v0_id;
	int v1_id;
	int v2_id;
};
class ModelFileLoader
{
public:
	ModelFileLoader();
	~ModelFileLoader();
	void OBJLoader(const char* OBJ_FILE,Scene* scene);
	void OBJColorLoader(const char* OBJ_FILE, std::vector<ColorVertex> &vertices);
	void COBJLoader(const char* OBJ_FILE, std::vector<ColorVertex> &vertices);
};

