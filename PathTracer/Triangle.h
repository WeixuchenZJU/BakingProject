#pragma once
#include <glm/glm.hpp>
#include "Material.h"
#include "hit.h"
#include "ray.h"
struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 TexCoord;
};
class Triangle
{
public:
	Triangle() {}
	Triangle(Vertex v0, Vertex v1, Vertex v2);
	
	void SetMatIndex(int index) {
		this->m_matindex = index;
	}
	void SetMaterial(Material* mat) {
		this->m_mat = mat;
	}
	bool intersect(const Ray &r, Hit &h, float tmin);
	~Triangle();
	float area() {
		return glm::length(glm::cross(m_v1.pos - m_v0.pos, m_v2.pos - m_v0.pos))*0.5f;
	}
private:
	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;
	glm::vec3 m_normal;
	Material* m_mat;
	int m_matindex;

};

