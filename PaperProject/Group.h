#pragma once
#include "Shader.h"
#include <vector>
#include "ModelFileLoader.h"
#include "Material.h"
class Group
{
public:
	Group();
	~Group();
	void Draw(Shader* shader);
	void SetMTLIndex(int index) {
		MTL_Index = index;
	}
	int GetMTLIndex() {
		return MTL_Index;
	}
	void AddVertex(Vertex v) {
		vertices.push_back(v);
	}
	void Set(std::vector<Material> material_list);
	std::vector<Vertex>& GetVertices() { return vertices; }
private:
	GLuint VBO, VAO;
	unsigned int map_diffuse;
	std::vector<Vertex> vertices;
	int MTL_Index;//²ÄÖÊË÷Òý
};

