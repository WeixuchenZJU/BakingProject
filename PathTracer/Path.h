#pragma once
#include "hit.h"
#include <glm\glm.hpp>
#include <vector>
class Path
{
public:
	Path(int length);
	~Path();
	void AddHitToPath(Hit hit);
	std::vector<Hit> GetPath();
	void PrintPath();
	void SetValidPath() {
		this->m_IsValid = true;
	}
	int IsValid() {
		return m_IsValid;
	}
	//计算两个Hit之间的Geometryterm
	float GeometryTerm(Hit ps, Hit pt);
	glm::vec3 TransportTerm();
private:
	std::vector<Hit> path_vertices;//路径中会存储不包括像素点在内的N个顶点
	int m_IsValid;//标志该路径是否有效
	int m_maxlength;
};

